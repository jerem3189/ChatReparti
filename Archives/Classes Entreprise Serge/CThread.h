/**
 *****************************************************************************
 *	\file		
 *				MECHTRONIX SYSTEMS INC.
 *
 *	\brief		Thread Unix/Windows abstraction
 *
 *	<HR>
 *	\version	1.0
 *	\author		Antoine Atallah
 *	\date		October 18 2006
 *
 *				- Initial Creation
 *
 *	<HR>
 *****************************************************************************/
#ifndef __CTHREAD_INCLUDED
#define __CTHREAD_INCLUDED

// ////////////////////////////////////////////////////////////////////////////
// Includes
//
// ////////////////////////////////////////////////////////////////////////////

/*	System Includes			*/
#ifdef _MSC_VER
	#include <windows.h>
	#include <process.h>
#endif

#ifdef __GNUC__
	#include <unistd.h>
	#include <pthread.h>
	#include <sched.h>
	#include <sys/neutrino.h>
#endif

// ////////////////////////////////////////////////////////////////////////////
// Definitions
//
// ////////////////////////////////////////////////////////////////////////////

/* Defines			*/
#ifdef _MSC_VER
	#define threadrt_t	unsigned
	#define pthread_t	HANDLE
	#define THREAD		__stdcall
	#define CTHREAD_PRIORITY_MINIMUM	THREAD_BASE_PRIORITY_MIN
	#define CTHRAD_PRIORITY_NORMAL		THREAD_PRIORITY_NORMAL
	#define CTHRAD_PRIORITY_HIGHEST		THREAD_PRIORITY_HIGHEST
#endif

#ifdef __GNUC__
	#define threadrt_t	void *
	#define THREAD
	#define CTHREAD_PRIORITY_MINIMUM	sched_get_priority_min(SCHED_RR)
	#define CTHRAD_PRIORITY_NORMAL		(sched_get_priority_max(SCHED_RR) - sched_get_priority_min(SCHED_RR)) / 2
	#define CTHRAD_PRIORITY_HIGHEST		sched_get_priority_max(SCHED_RR)
#endif

/* Typedefs			*/
#ifdef _MSC_VER
	typedef threadrt_t (__stdcall * ThreadFunction)(void *);
#endif

#ifdef __GNUC__
	typedef threadrt_t (* ThreadFunction)(void *);
#endif
	
// ////////////////////////////////////////////////////////////////////////////
// Class Definition
//
// ////////////////////////////////////////////////////////////////////////////

class CSnapShot;
/**
 * \brief
 * Class defining a Thread object valid under both Windows and QNX.
 * 
 * Under Windows, this class uses the _beginthreadex extended thread API, under
 * QNX, it uses the POSIX thread standard.
 *
 * Sample class usage:
 * \code
 * 
 * // User-defined thread function
 * threadrt_t UserThread(void * pParam)
 * {
 *     // Indefinitely prints a message
 *     while(true)
 *     {
 *         printf("I am a thread!\n");
 *         CThread::Sleep(100);
 *     }
 *     
 *     return NULL;
 * }
 *
 * // Main program entry point
 * void main()
 * {
 *     // Create the thread object
 *     CThread cThread;
 * 
 *     // Set the function to start as a thread
 *     cThread.SetThreadCallback(UserThread);
 *
 *     // Starts the thread
 *     cThread.Start(NULL);
 *
 *     // Sets the thread priority (optional)
 *     cThread.SetThreadPriority(CTHREAD_PRIORITY_MINIMUM);
 *
 *     // Wait for the thread to terminate (in this case, never)
 *     cThread.Join();
 * }
 *
 * \endcode
 * \n
 *
 * Starting a thread from a class
 * \code
 * 
 * threadrt_t ClassThreadFct(void * pParam);
 *
 * // Some sample class
 * class SomeClass
 * {
 * friend threadrt_t ClassThreadFct(void * pParam);
 * public:
 *     void StartClassThread();
 *     void StopClassThread();
 *
 * private:
 *     CThread m_cClassThread;
 *     bool m_bThreadMustTerminate;
 * };
 *
 * // User-defined thread function
 * threadrt_t ClassThreadFct(void * pParam)
 * {
 *     SomeClass * pThis = static_cast<SomeClass *>(pParam);
 *
 *     // Indefinitely prints a message
 *     while(!pThis->m_bThreadMustTerminate)
 *     {
 *         printf("I am a thread!\n");
 *         CThread::Sleep(100);
 *     }
 *     
 *     return CThread::Success;
 * }
 *
 * // Start the thread
 * void SomeClass::StartClassThread()
 * {
 *     // Set termination flag
 *     m_bThreadMustTerminate = false;
 * 
 *     // Set the function to start as a thread
 *     cThread.SetThreadCallback(ClassThreadFct);
 *
 *     // Starts the thread
 *     cThread.Start(this);
 * }
 *
 * // Stops the thread
 * void SomeClass::StopClassThread()
 * {
 *     // Set termination flag
 *     m_bThreadMustTerminate = true;
 *
 *     // Wait for the thread to terminate
 *     cThread.Join();
 * }
 *
 * \endcode
 *
 * \remarks
 * This class can only execute a static, or c-style function.
 *
 * \remarks
 * There is no explicit way to terminate a thread. The normal way is
 * to use some communication mechanism to terminate another thread.
 * See the example above.
 */
class CThread
{
public:
	// Initialization
	CThread(ThreadFunction pThreadFunction = NULL);
	~CThread();

	// Thread methods
	void SetThreadCallback(ThreadFunction pThreadFunction);
	bool Start(void * pParam);
	bool Join();
	void SetThreadPriority(int nPriority);
	static bool SetThreadAffinity(int nProcessorsMask);

	// Utility methods
	static void Sleep(unsigned long nMilliSeconds);
	static void USleep(unsigned long nMicroSeconts);

private:
	ThreadFunction		m_pThreadFunction;						///< Function to be called as a thread
	pthread_t			m_pThreadHandle;						///< Handle of the current thread
	bool				m_bThreadStarted;						///< True if the thread is running

	friend class CSnapShot;
};

#endif
