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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Connexion_au_serveur;
    QAction *actionErger;
    QAction *action_Lancer_le_KeepAlive;
    QAction *action_Cr_er_un_nouveau_salon;
    QAction *action_Joindre_un_salon;
    QAction *actionAjouter;
    QAction *actionAjouter_Ligne;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label_pseudo;
    QLabel *label;
    QLineEdit *lineEdit;
    QListWidget *listWidget;
    QPushButton *pushButton;
    QTabWidget *QTabWidget_onglets;
    QWidget *QTabWidget_GlobalRoom;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Salons;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 640);
        action_Connexion_au_serveur = new QAction(MainWindow);
        action_Connexion_au_serveur->setObjectName(QStringLiteral("action_Connexion_au_serveur"));
        actionErger = new QAction(MainWindow);
        actionErger->setObjectName(QStringLiteral("actionErger"));
        action_Lancer_le_KeepAlive = new QAction(MainWindow);
        action_Lancer_le_KeepAlive->setObjectName(QStringLiteral("action_Lancer_le_KeepAlive"));
        action_Cr_er_un_nouveau_salon = new QAction(MainWindow);
        action_Cr_er_un_nouveau_salon->setObjectName(QStringLiteral("action_Cr_er_un_nouveau_salon"));
        action_Cr_er_un_nouveau_salon->setEnabled(false);
        action_Joindre_un_salon = new QAction(MainWindow);
        action_Joindre_un_salon->setObjectName(QStringLiteral("action_Joindre_un_salon"));
        action_Joindre_un_salon->setEnabled(false);
        actionAjouter = new QAction(MainWindow);
        actionAjouter->setObjectName(QStringLiteral("actionAjouter"));
        actionAjouter_Ligne = new QAction(MainWindow);
        actionAjouter_Ligne->setObjectName(QStringLiteral("actionAjouter_Ligne"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_pseudo = new QLabel(centralWidget);
        label_pseudo->setObjectName(QStringLiteral("label_pseudo"));
        label_pseudo->setEnabled(false);

        gridLayout->addWidget(label_pseudo, 2, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFrameShape(QFrame::StyledPanel);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 4, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setMaxLength(3000);
        lineEdit->setFrame(true);

        gridLayout->addWidget(lineEdit, 2, 1, 1, 1);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        listWidget->setMaximumSize(QSize(160, 16777215));

        gridLayout->addWidget(listWidget, 1, 4, 2, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setMaximumSize(QSize(40, 25));
        pushButton->setAutoDefault(true);
        pushButton->setDefault(true);
        pushButton->setFlat(true);

        gridLayout->addWidget(pushButton, 2, 2, 1, 1);

        QTabWidget_onglets = new QTabWidget(centralWidget);
        QTabWidget_onglets->setObjectName(QStringLiteral("QTabWidget_onglets"));
        QTabWidget_onglets->setTabPosition(QTabWidget::North);
        QTabWidget_onglets->setTabShape(QTabWidget::Rounded);
        QTabWidget_GlobalRoom = new QWidget();
        QTabWidget_GlobalRoom->setObjectName(QStringLiteral("QTabWidget_GlobalRoom"));
        verticalLayout_2 = new QVBoxLayout(QTabWidget_GlobalRoom);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        textEdit = new QTextEdit(QTabWidget_GlobalRoom);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_2->addWidget(textEdit);

        QTabWidget_onglets->addTab(QTabWidget_GlobalRoom, QString());

        gridLayout->addWidget(QTabWidget_onglets, 0, 0, 2, 3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 20));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Salons = new QMenu(menuBar);
        menu_Salons->setObjectName(QStringLiteral("menu_Salons"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Salons->menuAction());
        menu_File->addAction(action_Connexion_au_serveur);
        menu_File->addSeparator();
        menu_File->addAction(action_Lancer_le_KeepAlive);
        menu_Salons->addAction(action_Cr_er_un_nouveau_salon);
        menu_Salons->addAction(action_Joindre_un_salon);

        retranslateUi(MainWindow);

        QTabWidget_onglets->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_Connexion_au_serveur->setText(QApplication::translate("MainWindow", "&Connexion au serveur", 0));
        actionErger->setText(QApplication::translate("MainWindow", "erger", 0));
        action_Lancer_le_KeepAlive->setText(QApplication::translate("MainWindow", "&Lancer le KeepAlive", 0));
        action_Cr_er_un_nouveau_salon->setText(QApplication::translate("MainWindow", "Cr\303\251er un &nouveau salon", 0));
        action_Joindre_un_salon->setText(QApplication::translate("MainWindow", "&Joindre un salon", 0));
        actionAjouter->setText(QApplication::translate("MainWindow", "Ajouter", 0));
        actionAjouter_Ligne->setText(QApplication::translate("MainWindow", "Ajouter Ligne", 0));
        label_pseudo->setText(QApplication::translate("MainWindow", "Pseudo", 0));
        label->setText(QApplication::translate("MainWindow", "Liste des clients", 0));
        pushButton->setText(QApplication::translate("MainWindow", "send", 0));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans';\"><br /></p></body></html>", 0));
        QTabWidget_onglets->setTabText(QTabWidget_onglets->indexOf(QTabWidget_GlobalRoom), QApplication::translate("MainWindow", "Onglet de la room globale", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&Menu", 0));
        menu_Salons->setTitle(QApplication::translate("MainWindow", "&Salons", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
