/*
 * 
 * 
 * 
 */
 
#ifndef	_CUDPSOCKET_INCLUDED
#define	_CUDPSOCKET_INCLUDED

// ////////////////////////////
// Includes
//
// ////////////////////////////

/* System Includes */
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <iostream>
	using namespace std;

// ///////////////////////
// Symbol Definitions
//
// //////////////////////

#define	CUDP_OK					0			///< Return type for the different functions of the class
#define	CUDP_WINSOCK			-1			///< Return type for the different functions of the class
#define	CUDP_SOCKET				-2			///< Return type for the different functions of the class
#define	CUDP_BIND				-3			///< Return type for the different functions of the class
#define BAD_SOCKET  (SOCKET)(~0)
#define CUDP_FULL_FRAME_SIZE	65535		///< Full UDP Frame, including headers (for the setBuff functions)
#define CUDP_MAX_FRAME_SIZE		65504		///< Maximum usable size of a UDP frame (larger frames will not work)

typedef int SOCKET;

class Socket
{
public:
	// Constructor/Destructor
	Socket();
	~Socket();

	// Initialization
    int		open(unsigned short nPort = 0);
    void	terminate();
	//typedef SOCKET;
	// Communication functions
	//int		Read(void * pData, size_t nDataSize);
	//int		Write(void * pData, size_t nDataSize);

	// Configuration
    bool	setPort(unsigned short nPortNumber);
    bool	setAddress(const char * szAddress);
//	bool	SetWriteAddress(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4);
//    bool	setSendBuffer(size_t nBufferSize);
//    bool	setRecvBuffer(size_t nBufferSize);
    SOCKET	getSocket();
	int getPort();
    bool getAddressIp();
    sockaddr_in getAddress();

private:

    bool		initialized;				///< Socket "connection" initialized?
    SOCKET		sock;					///< Socket for communication
//	sockaddr_in	m_sReadAddress;				///< Address to read from
    sockaddr_in	address;			///< Address to write to
	bool end;
    bool		init;
};

#endif

