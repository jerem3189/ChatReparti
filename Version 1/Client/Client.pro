#-------------------------------------------------
#
# Project created by QtCreator 2013-10-31T11:33:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    ../Server/src/Book.cpp \
    ../Server/src/Socket.cpp \
    ../Server/src/NetworkUDP.cpp \
    ../Server/src/Room.cpp \
    ../Server/src/Thread.cpp \
    ../Server/src/Client.cpp \
    ../Server/src/RFC1664.cpp \
    ../Server/src/Signalisation.cpp

HEADERS  += src/mainwindow.hpp \
    ../Server/src/Book.hpp \
    ../Server/src/Socket.hpp \
    ../Server/src/NetworkUDP.hpp \
    ../Server/src/Room.hpp \
    ../Server/src/Thread.hpp \
    ../Server/src/Client.hpp \
    ../Server/src/RFC1664.hpp \
    ../Server/src/Signalisation.hpp

FORMS    += src/mainwindow.ui
