/****************************************************************************
*****************************************************************************
* 
*							MECHTRONIX SYSTEMS INC.
*
*	FILENAME:		CUDP.cpp
*
*	PROJECT:		Generic
*
*	DESCRIPTION:	Class for encapsulating a standard udp socket
*
*	AUTHOR: 		Chris Nasr
*
*	DATE CREATED:	03/10/2003	(mm/dd/yyyy)
*
*	LAST REVISION:	03/10/2003
*
*	REVISION
*	HISTORY:		03/10/2003 -> initial creation - cn
*					03/26/2006 -> fixed Winsock library leak - aa
*					03/29/2006 -> Added constants for datagram sizes - aa
*
*****************************************************************************
****************************************************************************/
//#include "stdafx.h"
/* system includes	*/
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* class header		*/
#include "cudp.h"
#ifndef	__WATCOMC__
namespace _MSI	{
	#define	CAST(x, y)	static_cast<x>(y)
#else
	#define	CAST(x, y)	(x)(y)
#endif

// Number of objects created, for Winsock Initialization / Uninitialization
int CUDP::m_count = 0;
bool CUDP::m_winsockloaded = false;

/****************************************************************************
*
*  Name 		Construtor(s)
*
*  Declaration	CUDP(...)
*
*  Parameters	n/a
*
*  Description	initialises the object
*
*  Returns		n/a
*
****************************************************************************/
CUDP::CUDP()
{
	// If there are no object created yet... initialize Winsock
	if (m_count == 0)
	{
		// Create a variable called wsaData which will contain the
		// initialization information
		WS_DATA(wsaData);

		// Initializes a winsock DLL
		if (WINSOCK2(wsaData) != 0)
		{
			m_winsockloaded = false;
		}
		else
		{
			m_winsockloaded = true;
		}
	}

	m_count ++;

	m_writeaddr.sin_family	= AF_INET;
	m_writeaddr.sin_port	= ntohs(0);

	m_init					= false;
}

CUDP::CUDP(u_short port, bool nonblock, int timeout)
{
	m_writeaddr.sin_family	= AF_INET;
	m_writeaddr.sin_port	= ntohs(0);

	init(port, nonblock, timeout);
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
CUDP::~CUDP()
{
	terminate();

	// One less loaded object...
	m_count --;

	// No more objects... clean the winsock sutff
	#if defined(_MSC_VER)
	if (m_count == 0)
	{
		WSACleanup();
	}
	#endif
}

/****************************************************************************
*
*  Name 		Opens socket
*
*  Declaration	open(u_short, bool)
*
*  Parameters	u_short	port		Socket port
*				bool	block		Socket blocks
*				int		timeout		Socket timeout
*
*  Description	creates socket
*
*  Returns		int: CUDP_OK on success
*
****************************************************************************/
int CUDP::open(u_short port, bool nonblock, int timeout)
{
	char	c_opt_on	= 1;
	u_long	l_opt_on	= 1;
	sockaddr_in	name;

	// Removed by Antoine, shouldn't be there
	//WS_DATA(wsaData);
	//
	//if(WINSOCK(wsaData) != 0)
	//	return (m_init = false, CUDP_WINSOCK);

	if (!m_winsockloaded)
	{
		return (m_init = false, CUDP_WINSOCK);
	}

	if((m_sock = socket(AF_INET, SOCK_DGRAM, 0)) == BAD_SOCKET)
		return (m_init = false, CUDP_SOCKET);

	setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, &c_opt_on, sizeof(char));

	if(nonblock)
		ioctlsocket(m_sock, FIONBIO, &l_opt_on);
	else if(timeout > 0)
	{
#if	defined(__GNUC__)
		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = timeout * 1000;
		setsockopt(m_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));
#else
		setsockopt(m_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
#endif
	}

	name.sin_family			= AF_INET;
	name.sin_port			= ntohs(port);
	name.sin_addr.s_addr	= INADDR_ANY;

	if(bind(m_sock, (sockaddr *)&name, sizeof(name)) == BAD_SOCKET)
		return (m_init = false, CUDP_BIND);

	m_init	= true;
	return CUDP_OK;
}

int CUDP::init(u_short port, bool nonblock, int timeout)
{
	return open(port, nonblock, timeout);
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
int CUDP::read(void *data, size_t len)
{
	int	addr_size	= sizeof(m_readaddr);

	return recvfrom(m_sock, CAST(char *, data), (int)len, 0, (sockaddr *)&m_readaddr, &addr_size);
}

/****************************************************************************
*
*  Name 		Get Read Address
*
*  Declaration	sockaddr get_read_addr()
*
*  Parameters	none
*
*  Description	get address when read data came from
*
*  Returns		current read address
*
****************************************************************************/
sockaddr_in CUDP::get_read_addr()
{
	return m_readaddr;
}

/****************************************************************************
*
*  Name 		Reply
*
*  Declaration	reply(void *, size_t)
*
*  Parameters	void	*data			Data to read into
*				size_t	len				Max length of data to read
*
*  Description	writes data to a socket with address of last read
*
*  Returns		int: length of data read, -1 on error
*
****************************************************************************/
int CUDP::reply(void *data, size_t len)
{
	int	addr_size	= sizeof(m_readaddr);

	return sendto(m_sock, CAST(char *, data), (int)len, 0, (sockaddr *)&m_readaddr, addr_size);
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
int CUDP::write(void *data, size_t len)
{
	int	addr_size	= sizeof(m_writeaddr);

	return sendto(m_sock, CAST(char *, data), (int)len, 0, (sockaddr *)&m_writeaddr, addr_size);
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
void CUDP::nonblock(bool nonblock)
{
	u_long	opt = CAST(long, nonblock);

	ioctlsocket(m_sock, FIONBIO, &opt);
}

/****************************************************************************
*
*  Name 		Set Write Port
*
*  Declaration	setWPort(u_short)
*
*  Parameters	u_short	port		Port number
*
*  Description	changes address used for writing
*
*  Returns		bool: true on success
*
****************************************************************************/
bool CUDP::setWPort(u_short port)
{
	m_writeaddr.sin_port	= ntohs(port);

	return true;
}

/****************************************************************************
*
*  Name 		Set Write IP Address
*
*  Declaration	setWAddr(char *)
*
*  Parameters	char	*name
*
*  Description	changes ip address used for writing
*
*  Returns		bool
*
****************************************************************************/
bool CUDP::setWAddr(const char *name)
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
			memcpy(&(m_writeaddr.sin_addr), hp->h_addr, hp->h_length);
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

		memcpy(&(m_writeaddr.sin_addr), addr, 4);

		free(local);

		return true;
	}
}

/****************************************************************************
*
*  Name 		Set Send Buffer
*
*  Declaration	setSendBuff(size_t)
*
*  Parameters	size_t	len					Length of the buffer
*
*  Description	Sets the sockets send buffer size
*
*  Returns		bool
*
****************************************************************************/
bool CUDP::setSendBuff(size_t len)
{
	int	nLen	= (int)len;

	setsockopt(m_sock, SOL_SOCKET, SO_SNDBUF, (const char*)&nLen, sizeof(int));

	return true;
}

/****************************************************************************
*
*  Name 		Set Receive Buffer
*
*  Declaration	setRecvBuff(size_t)
*
*  Parameters	size_t	len					Length of the buffer
*
*  Description	Sets the sockets receive buffer size
*
*  Returns		bool
*
****************************************************************************/
bool CUDP::setRecvBuff(size_t len)
{
	int	nLen	= (int)len;

	setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, (const char*)&nLen, sizeof(int));

	return true;
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
void CUDP::terminate()
{
	shutdown(m_sock, SD_BOTH);
	closesocket(m_sock);
}

#ifndef	__WATCOMC__
}
#endif

