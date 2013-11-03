#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class Socket;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_action_Connexion_au_serveur_triggered();

    void on_action_Lancer_le_KeepAlive_triggered();

    void on_pushButton_clicked();

    void on_action_Cr_er_un_nouveau_salon_triggered();

private:
    Ui::MainWindow *ui;
    Socket *socket;
};

#endif // MAINWINDOW_HPP
