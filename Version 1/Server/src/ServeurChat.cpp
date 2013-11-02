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
    NetworkUDP udp;
    RFC1664 rfc;
    Book botin;
    Client john;
    cout << listenSocket.create("0.0.0.0", DEFAULT_PORT);
    cout << listenSocket.binding();

    while (1) {
        cout << "Main() -> Attente d'un nouveau message" << endl;
        memset(message, 0, sizeof message); //vide le message

        udp.receiveDatagrams(listenSocket.getSocket(), message, sizeof message, listenSocket.getSockaddr());

        cout << "Main() -> Message reçu : " << message << endl;
        cout << "Main() -> Type du message reçu : " << rfc.type(message) << endl;

        cout << "Main() -> Message reçu : " << message << endl;
        string testString(message);
        string champ1(rfc.fieldFromMesg(testString,1,'§'));
        string champ2(rfc.fieldFromMesg(testString,2,'§'));
        string champ3(rfc.fieldFromMesg(testString,3,'§'));
        string champ4(rfc.fieldFromMesg(testString,4,'§'));
        string champ5(rfc.fieldFromMesg(testString,5,'§'));
        cout <<"decoupage : \n"<<champ1<<endl<<champ2<<endl<<champ3<<endl<<champ4<<endl<<champ5<<endl;
        
        
        //string champ5(rfc.RecupererChampMessage(message,5,"§"));
        vector<string> vstr;


        switch (rfc.type(message)) {
        case MSG_CON:
            cout <<"Debug :"<<champ2<<" s'est connecté au serveur"<<endl;

            botin.addNewClient(champ2,champ3,"1338",vstr);
            //rfc.createMsgBookListResp(champ2,champ3,"1338");
            break;

        case MSG_DECO:
            cout <<"Debug :"<<champ2<<" s'est déconnecté du serveur"<<endl;
            botin.removeClient(champ2);
            break;

        case MSG_COM:
            cout <<"Debug :"<<champ2<<" à envoyé un message à redispatcher"<<endl;
            //botin.getClients();
                        
            //cout<<udp.sendDatagrams(listenSocket.getSocket(), message, sizeof message, listenSocket.getSockaddr());
            break;
        case MSG_LIVE:
            cout <<"Debug :"<<champ2<<" signale qu'il est encore actif"<<endl;
            botin.findClient(champ2)->setLastalive(time(0));
            
            cout << botin.findClient(champ2)->getLastalive()<<endl;
            break;
        case MSG_ROOM_JOIN:
            botin.addRoom(champ3);
            botin.addClientToRoom(champ2,champ3);
            cout <<"Debug :"<<champ2<<" à rejoint le salon "<<champ3<<endl;
            //rfc.createMsgBookListResp()
            //udp.sendDatagrams();
            break;

        case MSG_ROOM_QUIT:
            botin.removeClientFromRoom(champ2,champ3);
            cout <<"Debug :"<<champ2<<" à quitté le salon "<<champ3<<endl;
            //rfc.createMsgBookListResp();
            //udp.sendDatagrams();
            break;

        case MSG_BOOK_LIST_RQST:
            cout <<"Debug :"<<champ2<<"à demandé l'annuaire"<<endl;
            //rfc.createMsgBookListResp();
            //udp.sendDatagrams();
            break;


        default :

            break;


        }

        /* TRAITEMENT DU MESSAGE
        if (sendto(listenSocket, message, sizeof message,0,(SOCKADDR *) &clientAddress,clientAddressSize) == -1)
        {
                perror("send failed :");
                close(listenSocket);
                exit(0);
        }*/

        cout << "Main() -> Traitement du message" << endl;
        cout << "Main() -> Traitement du terminé" << endl;
    }

    return 1337;
}

