/** \file Thread.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_THREAD_H)
#define _THREAD_H


class Thread {
public:
	void start();
	void stop();
	void waitForEnd();
	virtual void run() = 0;
protected:
	pthread_t thread;
	bool end;
	static void* pthread_function();
};

#endif  //_THREAD_H
