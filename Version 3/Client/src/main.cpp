#include "mainwindow.hpp"
#include <QApplication>

#include "Listening.hpp"
#include "ComClients.hpp"
#include "../../Server/src/Book.hpp"


int main(int argc, char *argv[])
{
    QString port = "1338";

    if (argc > 1)
        port = QString(argv[1]);

    QApplication a(argc, argv);
    MainWindow w(port);
    w.show();

    Book *book = new Book();
    w.setBook(book);

    Listening *listen = new Listening(&w, w.getSocket(), book);
    listen->start();

    ComClients *comClients = new ComClients(&w, w.getSocketClients(), book);
    comClients->start();

    return a.exec();
}
