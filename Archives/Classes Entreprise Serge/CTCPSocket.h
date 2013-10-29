/**
 *****************************************************************************
 *	\file		
 *				MECHTRONIX SYSTEMS INC.
 *
 *	\brief		Class for encapsulating a standard tcp socket
 *
 *	<HR>
 *	\version	1.0
 *	\author		Thom Allen
 *	\date		12/08/2004
 *
 *				- Initial Creation
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
#ifndef	_CTCPSOCKET_INCLUDED
#define	_CTCPSOCKET_INCLUDED

// ///////////////////////////////////////////////////////////////////////////
// Includes
//
// ///////////////////////////////////////////////////////////////////////////

/* Local Includes				*/
#include "CTCPConstants.h"

/* System Includes				*/
#include <vector>
using namespace std;

#if	defined(__GNUC__)
	#include <sys/socket.h>
#elif defined(__BORLANDC__)
	#include <winsock2.h>
#elif defined(_MSC_VER)
	#include <winsock2.h>
#endif

// ///////////////////////////////////////////////////////////////////////////
// Symbol Definitions
//
// ///////////////////////////////////////////////////////////////////////////

//Client/server:
#define	CTCP_OK				0		///< Success!
#define	CTCP_WINSOCK		-1		///< Winsock not available
#define	CTCP_SOCKET			-2		///< Unable to create a local socket
#define	CTCP_INITIALIZED	-8		///< Already Initialized (as Client or Server)
//Client:
#define	CTCP_CONNECT		-3		///< Unable to connect to server
#define CTCP_HOSTNAME		-4		///< Unable to resolve host name
//Server:
#define CTCP_BIND       	-5		///< Unable to bind to local port
#define CTCP_LISTEN     	-6		///< Unable to start listening for connections
#define CTCP_ACCEPT     	-7		///< Unable to accept new connections
#define CTCP_INVALIDCLIENT	-8		///< Invalid client		

// ///////////////////////////////////////////////////////////////////////////
// Type Definitions
//
// ///////////////////////////////////////////////////////////////////////////

// STL Type Definitions
typedef vector<SOCKET> CTCPSocketList;

// ///////////////////////////////////////////////////////////////////////////
// Class Definitions
//
// ///////////////////////////////////////////////////////////////////////////

class CSnapShot;
/**
 * \brief
 * Class encapsulating a standard TCP socket.
 *
 * Typical Usage of this class to connect to a server is:
 * \code
 * CTCPSocket cConnectionToSomeServer;
 * ...
 * cConnectionToSomeServer.ConnectToServer("192.168.1.1", 1234);
 * cConnectionToSomeServer.SetNonBlocking(false);
 * ...
 * cConnectionToSomeServer.Write(szSomeData, nDataSize);
 * ...
 * int nReadSize = cConnectionToSomeServer.Read(szSomeData, nDataSize);
 * ...
 * cConnectionToSomeServer.Terminate();
 * \endcode
 * \p
 * Typical Usage of this as a server is:
 * \code
 * CTCPSocket cServer;
 * ...
 * cServer.StartServer(1234);
 * ...
 * // In some Thread (since this is always blocking)
 * int nClientIndex = cServer.WaitForConnection();
 * ...
 * cServer.Write(nClientIndex, szSomeData, nDataSize);
 * ...
 * cServer.Read(nClientIndex, szSomeData, nDataSize);
 * ...
 * cServer.TerminateAll();		// Disconnects every client
 * cServer.Terminate();			// Disconnects the server
 * \endcode
 *
 * Code Sample:
 * \code
 *	#include "CTCPSocket.h"
 *	#include <process.h>
 *	#include <stdio.h>
 *
 *	// Global objects!
 *	CTCPSocket client1;
 *	CTCPSocket client2;
 *	CTCPSocket server;
 *
 *	unsigned __stdcall ServerThread(void* pArguments)
 *	{
 *		int clientindex = server.WaitForConnection();
 *
 *		printf("Connected Client %d\n", clientindex);
 *
 *		char szData[1024];
 *		while(server.Read(clientindex, szData, 1024) > 0)
 *		{
 *			printf("Received data from Client %d\n%s\n", clientindex, szData);
 *		}
 *
 *		printf("Connection closed for client %d\n", clientindex);
 *
 *		_endthreadex( 0 );
 *		return 0;
 *	}
 *
 *	int _tmain(int argc, _TCHAR* argv[])
 *	{
 *		// Starts the server
 *		printf("Starting the server..,\n");
 *		server.StartServer(1234);
 *
 *		// Create the server thread.
 *		HANDLE hThread1 = (HANDLE)_beginthreadex(NULL, NULL, &ServerThread, NULL, NULL, NULL);
 *		HANDLE hThread2 = (HANDLE)_beginthreadex(NULL, NULL, &ServerThread, NULL, NULL, NULL);
 *
 *		// Makes sure the threads are created... this should be wait for single objects...
 *		Sleep(1000);
 *
 *		// Clients can connect to the server...
 *		client1.ConnectToServer("localhost", 1234);
 *		client2.ConnectToServer("127.0.0.1", 1234);
 *
 *		for (int i = 0; i < 10; i++)
 *		{
 *			client1.Write("Hello!", 7);
 *			Sleep(30);
 *			client2.Write("World!", 7);
 *			Sleep(60);
 *		}
 *
 *		server.TerminateAll();
 *		client1.Terminate();
 *		client2.Terminate();
 *
 *		Sleep(1000);
 *		return 0;
 *	}
 *
 * \endcode
 * \remarks
 * This class is thread safe.
 */
class CTCPSocket
{
public:
	// Constructor/Destructor
	CTCPSocket();
	~CTCPSocket();

	// Initialization
	int 	ConnectToServer(const char * const szHostName, unsigned short nPort, bool bNonBlocking = false, int nTimeout = 0);
	int 	ConnectToServerBlocking(const char * const szHostName, unsigned short nPort, int nTimeout = 0);
	int 	ConnectToServerNonBlocking(const char * const szHostName, unsigned short nPort);
	int		StartServer(unsigned short nPort);
	int 	WaitForConnection(bool bNonBlocking = false, int nTimeout = 0);
	int		CleanClientsList();
	void 	Terminate();
	void 	TerminateClient(int nClientIndex);
	void 	TerminateAll();
		
	// Under QNX such that SIGPIPE is not sent on closed connections...
	void	SetIgnoreSIGPIPE();
		
	// Communication Functions
	int		Read(void * pData, size_t nDataSize);
	int		Read(int nClientIndex, void * pData, size_t nDataSize);
	int		Write(void * pData, size_t nDataSize);
	int		Write(int nClientIndex, void * pData, size_t nDataSize);

	// Accessors
	int		GetClientsCount();
	void	SetNonBlocking(bool bNonBlocking);
	void	SetNonBlocking(int nClientIndex, bool bNonBlocking);
	void	SetBlocking(bool bBlocking);
	void	SetBlocking(int nClientIndex, bool bBlocking);
	int		GetLastError();

private:
	bool			m_bInitialized;				///< Object Initialized? (As server or client)
	SOCKET			m_sLocalSocket;				///< Local Socket (listening for connections, or sending to a server)
	CTCPSocketList	m_slClientSockets;			///< List of clients connected to the server
	static int		m_nClassObjectsCount;		///< Number of UDP Objects created
	static bool		m_bWinsockLoaded;			///< Winsock loaded for this class?

	friend class CSnapShot;
};
#endif
