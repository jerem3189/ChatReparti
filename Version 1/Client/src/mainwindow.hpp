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
    void on_button_keep_alive_clicked();
    void on_button_connect_clicked();

private:
    Ui::MainWindow *ui;
    Socket *socket;
};

#endif // MAINWINDOW_HPP
