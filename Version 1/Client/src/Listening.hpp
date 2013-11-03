/** \file Signalisation.hpp
 * Description brève du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_LISTENING_H)
#define _LISTENING_H

#include "../../Server/src/Thread.hpp"
#include <string>
#include "mainwindow.hpp"

#define DEFAULT_PORT "1338"


using namespace std;

class Socket;
class NetworkUDP;
class RFC1664;

class Listening : public Thread {
public:
    Listening(MainWindow *mainWindow);
    void run();
private:
    Socket *listenSocket;
    QMainWindow *mainWindow;
    char message[4096];
    NetworkUDP *udp;
    RFC1664 *rfc;
};

#endif  //_LISTENING_H
