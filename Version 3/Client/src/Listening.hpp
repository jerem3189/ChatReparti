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
class Book;
class Signalisation;
class QObject;

class Listening : public QObject, public Thread {
    Q_OBJECT

public:
    Listening(MainWindow *mainWindow, Socket *socket, Book *book);
    void run();

private:
    Socket *listenSocket;
    MainWindow *mainWindow;
    char message[4096];
    NetworkUDP *udp;
    RFC1664 *rfc;
    Book *book;
    Signalisation *keepalive;

signals:
    void statusBarChanged(QString);
};

#endif  //_LISTENING_H
