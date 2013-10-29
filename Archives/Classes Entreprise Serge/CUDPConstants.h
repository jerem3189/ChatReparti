/**
 *****************************************************************************
 *	\file		
 *				MECHTRONIX SYSTEMS INC.
 *
 *	\brief		Standard Macro's and Defines used to create
 *				sockets for QNX and Windows
 *
 *	<HR>
 *	\version	1.0
 *	\author		Chris Nasr
 *	\date		01/24/2003
 *
 *				- Initial Creation
 *
 *	<HR>
 *	\version	1.1
 *	\author		Antoine Atallah
 *	\date		03/24/2006
 *
 *				- Added macros for Winsock 2.2
 *
 *	<HR>
 *****************************************************************************/
#ifndef	__MECHTRONIX_SOCKET_CONSTANTS
#define	__MECHTRONIX_SOCKET_CONSTANTS

#if	defined(__QNX__)
	#define	SOCKET			int
	#define	WS_DATA(x)		int x
	#define	WINSOCK(x)		0													// Used only in Windows to startup winsock 1.1
	#define	WINSOCK2(x)		0													// Used only in Windows to startup winsock 2.2
	#define WINSOCKCLEAN(x)	0
	#define	BAD_SOCKET		-1													// An invalid socket error
	#define	SOCKET_ERROR	-1
	#define	WOULDBLOCK		EWOULDBLOCK
	#define	TIMEDOUT		EWOULDBLOCK
	#define	SOCK_ERR		errno
	#define	SD_RECEIVE		0
	#define	SD_SEND			1
	#define	SD_BOTH			2
	#define ioctlsocket		ioctl
	#define	closesocket		close
#elif defined(__BORLANDC__)
	#define	WS_DATA(x)		WSADATA	x
	#define	WINSOCK(x)		WSAStartup(MAKEWORD(1,1), &x)
	#define	WINSOCK2(x)		WSAStartup(MAKEWORD(2,2), &x)
	#define	BAD_SOCKET		INVALID_SOCKET
	#define	WOULDBLOCK		WSAEWOULDBLOCK
	#define	errno			WSAGetLastError()
#elif defined(_MSC_VER)
	#define	WS_DATA(x)		WSADATA	x
	#define	WINSOCK(x)		WSAStartup(MAKEWORD(1,1), &x)
	#define	WINSOCK2(x)		WSAStartup(MAKEWORD(2,2), &x)
	#define WINSOCKCLEAN(x)	WSACleanup()
	#define	BAD_SOCKET		INVALID_SOCKET
	#define	WOULDBLOCK		WSAEWOULDBLOCK
	#define TIMEDOUT		WSAETIMEDOUT
	#define	SOCK_ERR		WSAGetLastError()

	#if (defined(_WIN32_WCE)&&(_WIN32_WCE < 410))
		#define	SD_RECEIVE		0
		#define	SD_SEND			1
		#define	SD_BOTH			2
	#endif
#endif

#endif
