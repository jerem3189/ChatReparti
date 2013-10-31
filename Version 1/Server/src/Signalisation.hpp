/** \file Signalisation.hpp
 * Description brève du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_SIGNALISATION_H)
#define _SIGNALISATION_H

#define KEEP_ALIVE_TIMEOUT 5 // en secondes

#include "Thread.hpp"

class Socket;

class Signalisation : public Thread {
public:
    Signalisation();
    int sendKeepAlive();
    void run();
private:
    void sleep(int nbr_seconds);
    Socket *socket;
};

#endif  //_SIGNALISATION_H
