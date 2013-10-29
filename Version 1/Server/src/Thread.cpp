/** \file Thread.cpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#include "Thread.hpp"

Thread::Thread() {
	this->end = false;
}

void Thread::start() {
	printf("Thread::start() - Création du thread\n");
	int rc = pthread_create(&this->thread, NULL, CThread::fonction_thread, (void*)this);
	if (rc)
	{
		printf("Thread::start() - ERREUR de création du thread; Code d'erreur = %d\n",rc);
	}
	printf("Thread::start() - Thread créé\n");
}

void Thread::waitForEnd() {
	pthread_join(this->thread, NULL);
}

void* Thread::pthread_function() {
	Thread* pThread = (Thread*)arg;
	pThread->run();

	return NULL;
}
