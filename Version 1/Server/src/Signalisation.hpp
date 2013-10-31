/** \file Signalisation.hpp
 * Description brève du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_SIGNALISATION_H)
#define _SIGNALISATION_H

#include "Thread.hpp"
#include "NetworkUDP.hpp"

class Signalisation : public Thread {
public:
	int sendKeepAlive();
	void run();
private:
	int time();
};

#endif  //_SIGNALISATION_H
