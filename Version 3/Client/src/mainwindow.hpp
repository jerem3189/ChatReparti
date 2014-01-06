#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class Socket;
class Signalisation;
class Book;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QString listenPortClient, QWidget *parent = 0);
    Socket *getSocket();
    Ui::MainWindow *getUi() { return this->ui; }
    bool getConnected();
    void setConnected(bool connected);
    void addMessageToStatusBar(QString msg);
    ~MainWindow();
    
    Signalisation *getSig() const;
    void setSig(Signalisation *value);
    void setBook(Book *botin);

    Socket *getSocketClients() const;
    void setSocketClients(Socket *value);

private slots:

    void on_action_Connexion_au_serveur_triggered();

    void on_action_Lancer_le_KeepAlive_triggered();

    void on_pushButton_clicked();

    void on_action_Cr_er_un_nouveau_salon_triggered();

    void on_action_Joindre_un_salon_triggered();

    void on_actionD_connexion_triggered();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Socket *socket;
    Socket *socketClients;
    bool connected;
    Signalisation *sig;
    Book *book;
    QString listenPortClient;
};

#endif // MAINWINDOW_HPP
