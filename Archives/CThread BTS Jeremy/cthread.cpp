#include "cthread.h"
#include <iostream>

CThread::CThread() {
	this->fin = false;
}

void* CThread::fonction_thread(void* arg) {
	CThread* pCThread = (CThread*)arg;
	pCThread->run();

	return NULL;
}

void CThread::start() {
	printf("CThread::start() - Création du thread\n");
	int rc = pthread_create(&this->thread, NULL, CThread::fonction_thread, (void*)this);
	if (rc)
	{
		printf("CThread::start() - ERREUR de création du thread; Code d'erreur = %d\n",rc);
	}
	printf("CThread::start() - Thread créé\n");
}

void CThread::attendreFin() { 
	pthread_join(this->thread, NULL);
}
