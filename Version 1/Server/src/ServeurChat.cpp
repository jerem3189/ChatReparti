/*
 * File:   ServeurChat.cpp
 * Author: darkey
 *
 * Created on 29 octobre 2013, 13:27
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

#include "ErrorCodes.hpp"
#include "Socket.hpp"
#include "NetworkUDP.hpp"
#include "RFC1664.hpp"
#include "MessagesTypesRFC1664.hpp"
#include "Book.hpp"



#define MAX_MSG 1024
#define DEFAULT_PORT "1337"

char message[4096];

int main(int argc, char** argv) {
    Socket listenSocket;
    RFC1664 rfc;
    Book botin;

    listenSocket.create("NULL", DEFAULT_PORT);
    listenSocket.binding();

    while (1) {
        cout << "Main() -> Attente d'un nouveau message" << endl;
        memset(message, 0, sizeof message); //vide le message

        SOCKADDR_IN addr_in;

        NetworkUDP::receiveDatagrams(listenSocket.getSocket(), message, sizeof message, (SOCKADDR*)&addr_in, listenSocket.getAddrinfo());


       // cout << "pointeur1 : " << &addr_in << endl;

        cout << "Main() -> Message reçu : " << message << endl;
        cout << "Main() -> Type du message reçu : " << rfc.type(message) << endl;

        cout << "Main() -> Message reçu : " << message << endl;
        string testString(message);
        string champ1(rfc.fieldFromMesg(testString, 1, "§"));
        string champ2(rfc.fieldFromMesg(testString, 2, "§"));
        string champ3(rfc.fieldFromMesg(testString, 3, "§"));
        string champ4(rfc.fieldFromMesg(testString, 4, "§"));
        string champ5(rfc.fieldFromMesg(testString, 5, "§"));

        cout << "Main() -> decoupage : [" << champ1 << "] [" << champ2 << "] [" << champ3 << "] [" << champ4 << "] [" << champ5 << endl;

        string send;
        vector<Client>::iterator it;
        vector<Room*> roomList;



        switch (rfc.type(message)) {
        case MSG_CON:
            cout << "Main() -> " << champ2 << " s'est connecté au serveur" << endl;
                if(botin.addNewClient(champ2, &addr_in)==CLIENT_ADD_OK) {

                cout << "Main() -> " << champ2 << " a été ajouté à l'annuaire" << endl;

                roomList = botin.getClientRooms(champ2);

                cout << "Main() -> le client est dans " << roomList.size() << " room " << endl;

                send = rfc.createMsgBookListResp(champ2, champ3, "1337", roomList.size(), roomList);

                cout << "Main() -> Message a renvoyer : [" << send << "]" << endl;

                for (it = botin.getClients().begin(); it != botin.getClients().end(); ++it) {
                   // cout << "pointeur2 : " << it->getSockAddr() << endl;
                    //udp.sendDatagrams(it->getSocket()->getSocket(), (char*) send.c_str(), sizeof send.c_str(), it->getSocket()->getSockaddr(), it->getSocket()->getAddrinfo());
                    //sendto(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), 0, (SOCKADDR*)it->getSockAddr(), listenSocket.getAddrinfo()->ai_addrlen);
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), (SOCKADDR*)it->getSockAddr(), listenSocket.getAddrinfo());
                }

            } else
                cout << "Main() -> Debug :" << champ2 << " n'a pas pu etre ajouté à l'annuaire" << endl;

            break;

        case MSG_DECO:
            cout << "Main() -> Debug :" << champ2 << " s'est déconnecté du serveur" << endl;
            botin.removeClient(champ2);
            break;

        case MSG_COM:
            cout << "Debug :" << champ2 << " à envoyé un message à redispatcher" << endl;
            //for (it = botin.getClients().begin(); it != botin.getClients().end(); ++it) {
            //    cout << udp.sendDatagrams(it->getSocket()->getSocket(), message, sizeof message, it->getSocket()->getSockaddr(), it->getSocket()->getAddrinfo());
            //}
            break;
        case MSG_LIVE:
            cout << "Main() -> Debug :" << champ2 << " signale qu'il est encore actif" << endl;
            botin.findClient(champ2)->setLastalive(time(0));
            cout << botin.findClient(champ2)->getLastalive() << endl;
            break;
        case MSG_ROOM_JOIN:
            botin.addClientToRoom(champ2, champ3);
            cout << "Main() -> Debug :" << champ2 << " à rejoint le salon " << champ3 << endl;

            roomList = botin.getClientRooms(champ2);

            send = rfc.createMsgBookListResp(champ2, champ3, "1338", roomList.size(), roomList);

            for (it = botin.getClients().begin(); it != botin.getClients().end(); ++it) {
               // cout << "pointeur2 : " << it->getSockAddr() << endl;
                //udp.sendDatagrams(it->getSocket()->getSocket(), (char*) send.c_str(), sizeof send.c_str(), it->getSocket()->getSockaddr(), it->getSocket()->getAddrinfo());
                sendto(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), 0, (SOCKADDR*)it->getSockAddr(), listenSocket.getAddrinfo()->ai_addrlen);
            }

            break;

        case MSG_ROOM_QUIT:
            botin.removeClientFromRoom(champ2, champ3);
            cout << "Main() -> Debug :" << champ2 << " à quitté le salon " << champ3 << endl;
            send = rfc.createMsgBookListResp(champ2, champ3, "1338", botin.getClientRooms(champ2).size(), botin.getClientRooms(champ2));

            //for (it = botin.getClients().begin(); it != botin.getClients().end(); ++it) {
                //cout << udp.sendDatagrams(it->getSocket()->getSocket(), (char*) send.c_str(), sizeof send.c_str(), it->getSocket()->getSockaddr(), it->getSocket()->getAddrinfo());
            //}
            break;

        case MSG_ROOM_CREATE:
            botin.addRoom(champ3);
            break;

        case MSG_BOOK_LIST_RQST:
            cout << "Main() -> Debug :" << champ2 << "à demandé l'annuaire" << endl;
            send = rfc.createMsgBookListResp(champ2, champ3, "1338", botin.getClientRooms(champ2).size(), botin.getClientRooms(champ2));


            //cout << udp.sendDatagrams(botin.findClient(champ2)->getSocket()->getSocket(), (char*) send.c_str(), sizeof send.c_str(), botin.findClient(champ2)->getSocket()->getSockaddr(), botin.findClient(champ2)->getSocket()->getAddrinfo());

            break;


        default:

            break;


        }
        cout << "Main() -> Traitement du message terminé" << endl;
    }

    return 1337;
}

