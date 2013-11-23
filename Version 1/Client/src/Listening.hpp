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

class Listening : public Thread {
public:
    Listening(MainWindow *mainWindow, Socket *socket, Book *book);
    void run();
private slots:
    void on_pushButton_clicked();

    void on_actionD_connexion_triggered();

    void on_action_Lancer_le_KeepAlive_triggered();

private:
    Socket *listenSocket;
    MainWindow *mainWindow;
    char message[4096];
    NetworkUDP *udp;
    RFC1664 *rfc;
    Book *book;
};

#endif  //_LISTENING_H
