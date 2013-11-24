/** \file Signalisation.hpp
 * Description brève du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_SIGNALISATION_H)
#define _SIGNALISATION_H

#define KEEP_ALIVE_TIMEOUT 5 // en secondes

#include "Thread.hpp"
#include <string>

using namespace std;

class Socket;

class Signalisation : public Thread {
public:
    Signalisation(string clientName, Socket *socket);
    int sendKeepAlive();
    void run();
private:
    Socket *socket;
    string clientName;
};

#endif  //_SIGNALISATION_H
