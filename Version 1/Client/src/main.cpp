#include "mainwindow.hpp"
#include <QApplication>

#include "../../Server/src/NetworkUDP.hpp"
#include "../../Server/src/Signalisation.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Signalisation keepalive;


    
    return a.exec();
}
