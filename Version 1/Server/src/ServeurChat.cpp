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

SOCKADDR_IN addr_in;

int main(int argc, char** argv) {
    Socket listenSocket;
    RFC1664 rfc;
    Book book;

    listenSocket.create("NULL", DEFAULT_PORT);
    listenSocket.binding();

    while (1) {
        cout << "Main() -> Attente d'un nouveau message" << endl;

        memset(message, 0, sizeof message); //vide le message

        NetworkUDP::receiveDatagrams(listenSocket.getSocket(), message, sizeof message, (SOCKADDR*)&addr_in, listenSocket.getAddrinfo());

        cout << "Main() -> Message reçu : " << message << endl;
        cout << "Main() -> Type du message reçu : " << rfc.type(message) << endl;

        string testString(message);
        string champ1(rfc.fieldFromMesg(testString, 1, "§"));
        string champ2(rfc.fieldFromMesg(testString, 2, "§"));
        string champ3(rfc.fieldFromMesg(testString, 3, "§"));
        string champ4(rfc.fieldFromMesg(testString, 4, "§"));
        string champ5(rfc.fieldFromMesg(testString, 5, "§"));

        cout << "Main() -> decoupage : [" << champ1 << "] [" << champ2 << "] [" << champ3 << "] [" << champ4 << "] [" << champ5 << "]" << endl;

        string send;
        string ack;
        vector<Client>::iterator itClient;
        vector<Room*>::iterator itRoomPtr;
        vector<Room*> roomList;
        Client *client;



        switch (rfc.type(message)) {
        case MSG_CON:
            cout << "Main() -> " << champ2 << " s'est connecté au serveur" << endl;
            if(book.addNewClient(champ2, &addr_in)==CLIENT_ADD_OK) {
                cout << "Main() ->" << champ2 << " a été ajouté à l'annuaire" << endl;
                cout << "Main() -> Size : " << book.getClientRooms(champ2).size() << endl;

                ack = rfc.createMsgAck("Connexion réussie");
                send = rfc.createMsgBookListResp(champ2, champ3, "1337", book.getClientRooms(champ2).size(), book.getClientRooms(champ2));

                roomList = book.getClientRooms(champ2);

                cout << "Main() -> le client est dans " << roomList.size() << " room(s) " << endl;

                for (itClient = book.getClients().begin(); itClient != book.getClients().end(); ++itClient) {
                    roomList = book.getClientRooms(itClient->getName());
                    send = rfc.createMsgBookListResp(itClient->getName(), "127.0.0.1", "1337", roomList.size(), roomList);
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), (SOCKADDR*)book.findClient(champ2)->getSockAddr(), listenSocket.getAddrinfo());
                }

                send = rfc.createMsgBookListResp(champ2, champ3, "1337", roomList.size(), roomList);
                cout << "Main() -> Message a renvoyer : [" << send << "]" << endl;

                for (itClient = book.getClients().begin(); itClient != book.getClients().end(); ++itClient) {
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), (SOCKADDR*)itClient->getSockAddr(), listenSocket.getAddrinfo());
                    cout << "Main() -> Message envoyé à " << itClient->getName() << endl;
                }
            } else
                cout << "Main() -> " << champ2 << " n'a pas pu etre ajouté à l'annuaire" << endl;

            break;

        case MSG_DECO:
            cout << "Main() -> Debug :" << champ2 << " s'est déconnecté du serveur" << endl;
            book.removeClient(champ2);
            break;

        case MSG_COM:
            cout << "Debug :" << champ2 << " à envoyé un message à redispatcher" << endl;

            for (itClient = book.getClients().begin(); itClient != book.getClients().end(); ++itClient) {
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), (SOCKADDR*)itClient->getSockAddr(), listenSocket.getAddrinfo());
            }

            break;
        case MSG_LIVE:
            cout << "Main() -> Debug :" << champ2 << " signale qu'il est encore actif" << endl;
            book.findClient(champ2)->setLastalive(time(0));
            cout << book.findClient(champ2)->getLastalive() << endl;
            break;
        case MSG_ROOM_JOIN:
            book.addClientToRoom(champ2, champ3);
            cout << "Main() -> Debug :" << champ2 << " a rejoint le salon " << champ3 << endl;

            ack = rfc.createMsgAck("Room joined");
            roomList = book.getClientRooms(champ2);
            send = rfc.createMsgBookListResp(champ2, champ3, "1338", roomList.size(), roomList);

            client = book.findClient(champ2);

            NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)client->getSockAddr(), listenSocket.getAddrinfo());

            for (itClient = book.getClients().begin(); itClient != book.getClients().end(); ++itClient) {
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), (SOCKADDR*)itClient->getSockAddr(), listenSocket.getAddrinfo());
            }

            break;

        case MSG_ROOM_QUIT:
            book.removeClientFromRoom(champ2, champ3);
            cout << "Main() -> Debug :" << champ2 << " à quitté le salon " << champ3 << endl;
            send = rfc.createMsgBookListResp(champ2, champ3, "1338", book.getClientRooms(champ2).size(), book.getClientRooms(champ2));

            //for (it = botin.getClients().begin(); it != botin.getClients().end(); ++it) {
            //cout << udp.sendDatagrams(it->getSocket()->getSocket(), (char*) send.c_str(), sizeof send.c_str(), it->getSocket()->getSockaddr(), it->getSocket()->getAddrinfo());
            //}
            break;

        case MSG_ROOM_CREATE:
            book.addRoom(champ3);

            ack = rfc.createMsgAck("Room créée");

            client = book.findClient(champ2);

            NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)client->getSockAddr(), listenSocket.getAddrinfo());

            break;

        case MSG_BOOK_LIST_RQST:
            cout << "Main() -> Debug :" << champ2 << "a demandé l'annuaire" << endl;

            for (itClient = book.getClients().begin(); itClient != book.getClients().end(); ++itClient) {
                roomList = book.getClientRooms(itClient->getName());
                send = rfc.createMsgBookListResp(itClient->getName(), "127.0.0.1", "1337", roomList.size(), roomList);
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), (SOCKADDR*)book.findClient(champ2)->getSockAddr(), listenSocket.getAddrinfo());
            }

            break;


        default:

            break;


        }
        cout << "Main() -> Traitement du message terminé" << endl;
    }

    return 1337;
}

