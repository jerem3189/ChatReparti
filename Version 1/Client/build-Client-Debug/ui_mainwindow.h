/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Connexion_au_serveur;
    QAction *actionErger;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *button_keep_alive;
    QTabWidget *QTabWidget_onglets;
    QWidget *QTabWidget_GlobalRoom;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit;
    QLabel *label_pseudo;
    QLineEdit *lineEdit;
    QPushButton *button_connect;
    QListView *listView;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(782, 661);
        action_Connexion_au_serveur = new QAction(MainWindow);
        action_Connexion_au_serveur->setObjectName(QStringLiteral("action_Connexion_au_serveur"));
        actionErger = new QAction(MainWindow);
        actionErger->setObjectName(QStringLiteral("actionErger"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        button_keep_alive = new QPushButton(centralWidget);
        button_keep_alive->setObjectName(QStringLiteral("button_keep_alive"));

        gridLayout->addWidget(button_keep_alive, 3, 1, 1, 1);

        QTabWidget_onglets = new QTabWidget(centralWidget);
        QTabWidget_onglets->setObjectName(QStringLiteral("QTabWidget_onglets"));
        QTabWidget_onglets->setTabPosition(QTabWidget::South);
        QTabWidget_onglets->setTabShape(QTabWidget::Rounded);
        QTabWidget_GlobalRoom = new QWidget();
        QTabWidget_GlobalRoom->setObjectName(QStringLiteral("QTabWidget_GlobalRoom"));
        verticalLayout_2 = new QVBoxLayout(QTabWidget_GlobalRoom);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        textEdit = new QTextEdit(QTabWidget_GlobalRoom);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout_2->addWidget(textEdit);

        QTabWidget_onglets->addTab(QTabWidget_GlobalRoom, QString());

        gridLayout->addWidget(QTabWidget_onglets, 0, 0, 1, 2);

        label_pseudo = new QLabel(centralWidget);
        label_pseudo->setObjectName(QStringLiteral("label_pseudo"));

        gridLayout->addWidget(label_pseudo, 1, 0, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        button_connect = new QPushButton(centralWidget);
        button_connect->setObjectName(QStringLiteral("button_connect"));

        gridLayout->addWidget(button_connect, 2, 1, 1, 1);

        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy);

        gridLayout->addWidget(listView, 0, 3, 4, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 782, 25));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Connexion_au_serveur);

        retranslateUi(MainWindow);

        QTabWidget_onglets->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_Connexion_au_serveur->setText(QApplication::translate("MainWindow", "&Connexion au serveur", 0));
        actionErger->setText(QApplication::translate("MainWindow", "erger", 0));
        button_keep_alive->setText(QApplication::translate("MainWindow", "Lancer KeepAlive", 0));
        QTabWidget_onglets->setTabText(QTabWidget_onglets->indexOf(QTabWidget_GlobalRoom), QApplication::translate("MainWindow", "Global Room", 0));
        label_pseudo->setText(QApplication::translate("MainWindow", "Pseudo", 0));
        button_connect->setText(QApplication::translate("MainWindow", "Connect", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
