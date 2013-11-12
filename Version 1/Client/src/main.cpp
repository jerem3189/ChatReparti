#include "mainwindow.hpp"
#include <QApplication>
#include "Listening.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Listening *listen = new Listening(&w, w.getSocket());
    listen->start();
    
    return a.exec();
}
