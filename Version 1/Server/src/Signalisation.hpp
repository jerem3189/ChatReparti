/** \file Signalisation.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_SIGNALISATION_H)
#define _SIGNALISATION_H

#include "Thread.hpp"

class Signalisation : public Thread {
public:
	int sendKeepAlive();
	int runkeep();
private:
	int time();
};

#endif  //_SIGNALISATION_H
