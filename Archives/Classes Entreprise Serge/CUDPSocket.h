/**
 *****************************************************************************
 *	\file		
 *				MECHTRONIX SYSTEMS INC.
 *
 *	\brief		Class for encapsulating a standard udp socket
 *
 *	<HR>
 *	\version	1.0
 *	\author		Chris Nasr
 *	\date		03/10/2003
 *
 *				- Initial Creation
 *
 *	<HR>
 *	\version	1.1
 *	\author		Antoine Atallah
 *	\date		03/26/2006
 *
 *				- Added macros for Winsock 2.2
 *				- Fixed Winsock library leak
 *
 *	<HR>
 *	\version	1.2
 *	\author		Antoine Atallah
 *	\date		03/29/2006
 *
 *				- Added constants for datagram sizes
 *
 *	<HR>
 *	\version	2.0
 *	\author		Antoine Atallah
 *	\date		08/04/2006
 *
 *				- Changed style to include into MSI Software Library
 *				- Added documentation
 *				- Modified behavior of many functions as well as their name
 *
 *	<HR>
 *****************************************************************************/
#ifndef	_CUDPSOCKET_INCLUDED
#define	_CUDPSOCKET_INCLUDED

// ///////////////////////////////////////////////////////////////////////////
// Includes
//
// ///////////////////////////////////////////////////////////////////////////

/* System Includes				*/
#if	defined(__GNUC__)
	#include <sys/socket.h>
	#include <netinet/in.h>
#elif defined(__WATCOMC__)
	#include <sys/socket.h>
#elif defined(__BORLANDC__)
	#include <winsock2.h>
#elif defined(_MSC_VER)
	#include <winsock2.h>
#endif
/* Local Includes				*/
#include "CUDPConstants.h"

// ///////////////////////////////////////////////////////////////////////////
// Symbol Definitions
//
// ///////////////////////////////////////////////////////////////////////////

#define	CUDP_OK					0			///< Return type for the different functions of the class
#define	CUDP_WINSOCK			-1			///< Return type for the different functions of the class
#define	CUDP_SOCKET				-2			///< Return type for the different functions of the class
#define	CUDP_BIND				-3			///< Return type for the different functions of the class

#define CUDP_FULL_FRAME_SIZE	65535		///< Full UDP Frame, including headers (for the setBuff functions)
#define CUDP_MAX_FRAME_SIZE		65504		///< Maximum usable size of a UDP frame (larger frames will not work)

class CSnapShot;
/**
 * \brief
 * Class encapsulating a standard UDP socket.
 *
 * \remarks
 * This class is thread safe.
 */
class CUDPSocket
{
public:
	// Constructor/Destructor
	CUDPSocket();
	~CUDPSocket();

	// Initialization
	int		Open(unsigned short nPort = 0, bool bNonBlocking = false, int nTimeout = 0);
	int		OpenBlocking(unsigned short nPort = 0, int nTimeout = 0);
	int		OpenNonBlocking(unsigned short nPort = 0);
	void	Terminate();

	// Communication functions
	int		Read(void * pData, size_t nDataSize);
	int		Reply(void * pData, size_t nDataSize);
	int		Write(void * pData, size_t nDataSize);

	// Configuration
	void	SetWritePort(unsigned short nPortNumber);
	bool	SetWriteAddress(const char * szAddress);
	bool	SetWriteAddress(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4);
	bool	SetSendBuffer(size_t nBufferSize);
	bool	SetRecvBuffer(size_t nBufferSize);
	void	SetNonBlocking(bool bNonBlocking);
	void	SetBlocking(bool bBlocking);
	char *	GetReplyAddress(char * szBuffer, int nBufferSize);
	int		GetLastError();
	SOCKET	GetSocket();

private:
	bool		m_bInitialized;				///< Socket "connection" initialized?
	SOCKET		m_sSocket;					///< Socket for communication
	sockaddr_in	m_sReadAddress;				///< Address to read from
	sockaddr_in	m_sWriteAddress;			///< Address to write to

	static int	m_nClassObjectsCount;		///< Number of UDP Objects created
	static bool	m_bWinsockLoaded;			///< Winsock loaded for this class?

	friend class CSnapShot;
};

#endif
