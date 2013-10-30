/** \file Thread.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_THREAD_H)
#define _THREAD_H

#include <pthread.h>

class Thread {
public:
  	Thread();
	virtual ~Thread() {;}
	void start();
	inline void stop();
	void waitForEnd();
	virtual void run() = 0;
protected:
	pthread_t thread;
	bool end;
	static void* pthread_function(void*);
};

#endif  //_THREAD_H
