#include "mainwindow.hpp"
#include <QApplication>

#include "../../Server/src/NetworkUDP.hpp"
#include "../../Server/src/Socket.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
