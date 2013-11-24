#include "mainwindow.hpp"
#include <QApplication>

#include "Listening.hpp"
#include "../../Server/src/Book.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Book *book = new Book();
    w.setBook(book);

    Listening *listen = new Listening(&w, w.getSocket(), book);
    listen->start();
    
    return a.exec();
}
