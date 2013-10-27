#ifndef CTHREAD_H
#define CTHREAD_H


/**
 * <b>Ce fichier contient la déclaration de la classe CThread.</b> Y est contenu 
 * toutes les méthodes de la classe.
 * @file cthread.h
 * @author Jérémy Vaquier
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/**
 * <b>Classe abstraite encapsulant les fonctionnalitées de pthread.</b>
 * Cette classe permet de créer facilement des objets threads en en faisant dériver des classes filles.
 * @class CThread
 */
 
class CThread {

	public:
  		CThread();
		virtual ~CThread() {;}
		
		void start(); ///< Permet de démarrer le thread
  		inline void stop();
  		
  		virtual void run() = 0; ///< Méthode virtuelle pure à implémenter afin de donner un corps au thread
		void attendreFin(); ///< Méthode Bloquante permettant d'attendre la fin de l'exécution du thread
		
	protected:
 		pthread_t thread; ///< Thread appartenant à pthread
		bool fin; ///< Booleen permettant de mettre un terme au thread
		static void* fonction_thread(void*); ///< Fonction pthread qui permettra de donner un corps au thread
};

inline void CThread::stop() {
	this->fin = true;
}

#endif // CTHREAD_H
