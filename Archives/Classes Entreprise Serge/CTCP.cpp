/****************************************************************************
*****************************************************************************
* 
*							MECHTRONIX SYSTEMS INC.
*
*	FILENAME:		CTCP.cpp
*
*	PROJECT:		Generic
*
*	DESCRIPTION:	Class for encapsulating a standard tcp socket
*
*	AUTHOR: 		Thom Allen
*
*	DATE CREATED:	Dec 8, 2004
*
*****************************************************************************
****************************************************************************/

/* system includes	*/
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/* class header		*/
#include "ctcp.h"

#if	defined(__GNUC__)
	#define OPT_TYPE	int
#elif (defined(_MSC_VER)||defined(_WIN32_WCE))
	#define OPT_TYPE	BOOL
#elif defined(__WATCOMC__)
	#define OPT_TYP		int
#endif

#if defined (_WIN32_WCE)
    #define strdup _strdup
#endif



namespace _MSI
{

/****************************************************************************
*
*  Name 		Construtor(s)
*
*  Declaration	CTCP(...)
*
*  Parameters	n/a
*
*  Description	initialises the object
*
*  Returns		n/a
*
****************************************************************************/
CTCP::CTCP()
{
    this->m_bInit = false;
    this->m_bServer = false;

    this->m_bNonblock = false;
    this->m_nPort = 0;
    this->m_nTimeout = 0;
    this->m_sock = BAD_SOCKET;
    this->m_AcceptSocket = BAD_SOCKET;

}


/****************************************************************************
*
*  Name 		Destrutor
*
*  Declaration	~CUPD()
*
*  Parameters	n/a
*
*  Description	destroys the object
*
*  Returns		n/a
*
****************************************************************************/
CTCP::~CTCP()
{
    terminate();
}

/****************************************************************************
*
*  Name 		connect
*
*  Parameters	szHostName  :IN:    Host name or IP address (client)
*               port        :IN:    Port id
*               nonblock    :IN:    Is this a blocking socket?
*               timeout     :IN:    Timeout for blocking socket
*               bServer     :IN:    Is this a server or a client?
*
*  Description	creates socket and activates connections
*
*  Returns		int: CTCP_OK on success
*
****************************************************************************/
int CTCP::connect(char *szHostName, u_short port, bool nonblock, int timeout, bool bServer, u_short localport)
{
	OPT_TYPE c_opt_on	= 1;
	u_long	l_opt_on	= 1;
	
	WS_DATA(wsaData);
	
	if(WINSOCK(wsaData) != 0)
		return (this->m_bInit = false, CTCP_WINSOCK);

	if((this->m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == BAD_SOCKET)
		return (this->m_bInit = false, CTCP_SOCKET);

	setsockopt(this->m_sock, IPPROTO_TCP, TCP_NODELAY, (char *)&c_opt_on, sizeof(OPT_TYPE));

    this->m_nTimeout = timeout;
	this->m_bNonblock = nonblock;
	this->m_bServer = bServer;
	this->m_nPort = port;

	if (this->m_bServer)
    {
		this->m_serverservice.sin_family			= AF_INET;
	    this->m_serverservice.sin_port			= ntohs(m_nPort);
		this->m_serverservice.sin_addr.s_addr		= INADDR_ANY;

        //Set the socket so that it can re-use its own address:
	    setsockopt(m_sock, IPPROTO_TCP, SO_REUSEADDR, (char *)&c_opt_on, sizeof(OPT_TYPE));

	    //Associate the local address to the socket:
	    if(bind(m_sock, (sockaddr *)&m_serverservice, sizeof(m_serverservice)) == BAD_SOCKET)
	    {
		    int nErr = SOCK_ERR;
		    return CTCP_BIND;
	    }

	    //Places the socket in a state in which it is listening for an incoming connection:
	    if ( listen(m_sock, 1 ) == SOCKET_ERROR )
	    {
		    int nErr = SOCK_ERR;
		    return CTCP_LISTEN;
	    }
    }
    else
    {
        this->m_clientservice.sin_family			= AF_INET;
	    this->m_clientservice.sin_port			= ntohs(this->m_nPort);
        if (SetAddr(szHostName, &this->m_clientservice) == false)
        {
            return(CTCP_HOSTNAME);
        }

		if (localport != 0)
		{
			//Associate the local address to the socket:
			this->m_serverservice.sin_family			= AF_INET;
			this->m_serverservice.sin_port				= ntohs(localport);
			this->m_serverservice.sin_addr.s_addr		= INADDR_ANY;
			if(bind(this->m_sock, (sockaddr *)&m_serverservice, sizeof(m_serverservice)) == BAD_SOCKET)
			{
				int nErr = SOCK_ERR;
				return CTCP_BIND;
			}
		}

		//Set the socket so that it can re-use its own address:
		setsockopt(m_sock, IPPROTO_TCP, SO_REUSEADDR, (char *)&c_opt_on, sizeof(OPT_TYPE));

		if(::connect(this->m_sock, (sockaddr*) &this->m_clientservice, sizeof(this->m_clientservice)) == BAD_SOCKET)
		    return (this->m_bInit = false, CTCP_CONNECT);
		
		//Set the socket non-blocking after the connect, because if it is set before, it causes
		//connect to return with BAD_SOCKET - mfi 01/28/2005
		
		if(this->m_bNonblock)
			ioctlsocket(this->m_sock, FIONBIO, &l_opt_on);
		else if(timeout > 0)
		{
	#if	defined(__GNUC__)
			struct timeval tv;
			tv.tv_sec = 0;
			tv.tv_usec = timeout * 1000;
			setsockopt(this->m_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));
	#else
			setsockopt(this->m_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	#endif
		}

        this->m_bInit	= true;
        
    }
	
	return CTCP_OK;
}


/****************************************************************************
*
*  Name 		SetAddr
*
*  Declaration	open(u_short, bool)
*
*  Parameters	name:           IN: Host name or ip address (in 
&                                   xxx.xxx.xxx.xxx format)
*               clientservice:  IN: A pointer to a sockaddr_in used to store 
*                                   the address
*
*  Description	Sets server address in sockaddr_in structure (this function
*               is used by the client)
*
*  Returns		bool success or failure
*
****************************************************************************/
bool CTCP::SetAddr(const char *name, sockaddr_in* clientservice)
{
	hostent	*hp;
	char	*ptoken;
	char	*local;
	char	addr[4];

#if defined(__WATCOMC__)
	char*		hostname	= (char*)name;
#else
	const char*	hostname	= name;
#endif
	
	if(isalpha(name[0]))
	{
		if((hp = gethostbyname(hostname)) != NULL)
		{
			memcpy(&(clientservice->sin_addr), hp->h_addr, hp->h_length);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		local	= strdup(name);

		if((ptoken = strtok(local, ".")) == NULL)
			return false;

		addr[0]	= (unsigned char)atoi(ptoken);
		
		if((ptoken = strtok(NULL, ".")) == NULL)
			return false;

		addr[1]	= (unsigned char)atoi(ptoken);

		if((ptoken = strtok(NULL, ".")) == NULL)
			return false;

		addr[2]	= (unsigned char)atoi(ptoken);

		if((ptoken = strtok(NULL, ".")) == NULL)
			return false;

		addr[3]	= (unsigned char)atoi(ptoken);

		memcpy(&(clientservice->sin_addr), addr, 4);

		free(local);

		return true;
	}
}

/****************************************************************************
*
*  Name 		Read
*
*  Declaration	read(void *, size_t)
*
*  Parameters	void	*data			Data to read into
*				size_t	len				Max length of data to read
*
*  Description	reads data from socket
*
*  Returns		int: length of data read, -1 on error
*
****************************************************************************/
int CTCP::read(void *data, size_t len)
{
	int nRxLen = -1;
    
    if (this->m_bInit)
    {
        nRxLen = recv((this->m_bServer)?this->m_AcceptSocket:this->m_sock, static_cast<char *>(data), (int)len, 0);
        if (nRxLen == -1)
        {
            int nErr = SOCK_ERR;
            //WSAECONNRESET is the case seen, but the other are also possible - mfi
            if (nErr != EWOULDBLOCK) 
            {
                this->m_bInit = false;
            }
        }
        else if (nRxLen == 0)
        {
            this->m_bInit = false;
        }

    }
    return nRxLen;
}

/****************************************************************************
*
*  Name 		Write
*
*  Declaration	write(void *, size_t)
*
*  Parameters	void	*data			Data to write
*				size_t	len				Length of data to write
*
*  Description	writes data to a socket
*
*  Returns		int: length of data written, -1 on error
*
****************************************************************************/
int CTCP::write(void *data, size_t len)
{
    int nTxLen = -1;

    if (this->m_bInit)
    {
        nTxLen = send((this->m_bServer)?this->m_AcceptSocket:this->m_sock, static_cast<char *>(data), (int)len, 0);
        if (nTxLen == -1)
        {
            int nErr = SOCK_ERR;
            //WSAECONNRESET is the case seen, but the other are also possible - mfi
            if (nErr != EWOULDBLOCK) 
            {
                this->m_bInit = false;
            }
        }

    }

	return nTxLen;
}

/****************************************************************************
*
*  Name 		Block
*
*  Declaration	block(bool)
*
*  Parameters	bool	block		Enable blocking
*
*  Description	changes blocking option
*
*  Returns		void
*
****************************************************************************/
void CTCP::nonblock(bool nonblock)
{
	u_long	opt = static_cast<long>(nonblock);

	ioctlsocket(this->m_sock, FIONBIO, &opt);
}

/****************************************************************************
*
*  Name 		Close the socket
*
*  Declaration	terminate()
*
*  Parameters	none
*
*  Description	closes the socket
*
*  Returns		void
*
****************************************************************************/
void CTCP::terminate()
{
	shutdown(this->m_sock, SD_BOTH);
	closesocket(this->m_sock);
}


/****************************************************************************
*
*  Name 		TcpAccept
*
*  Parameters	none
*
*  Description	Accepts a connection on a socket
*
*  Returns		void
*
****************************************************************************/
int CTCP::TcpAccept()
{

	OPT_TYPE c_opt_on	= 1;
	u_long	l_opt_on	= 1;

	m_bInit = false;
	SOCKET AcceptSocket;

    if (!m_bInit)
    {
        //printf( "Waiting for a client to connect...\n" );

        AcceptSocket = BAD_SOCKET;

        while ( AcceptSocket == BAD_SOCKET ) 
        {
            //Accept the connection into a new socket:
			AcceptSocket = accept( m_sock, NULL, NULL );
        }

		m_AcceptSocket = AcceptSocket;
		
        //Set the non-blocking state of the new socket:
		if(m_bNonblock)
			ioctlsocket(m_AcceptSocket, FIONBIO, &l_opt_on);
		else if(m_nTimeout > 0)
		{
	#if	defined(__GNUC__)
			struct timeval tv;
			tv.tv_sec = 0;
			tv.tv_usec = m_nTimeout * 1000;
			setsockopt(m_AcceptSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));
	#else
			setsockopt(m_AcceptSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&m_nTimeout, sizeof(m_nTimeout));
	#endif
		}

		m_bInit = true;

        //printf( "Client Connected.\n");
    }
    else
    {
        return (CTCP_ACCEPT);
    }

    return 0;
}


};
