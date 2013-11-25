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
        cout << "Main() -> Nombre de client dans l'annuaire : " << book.getClients().size() << endl;
        cout << "Main() -> Attente d'un nouveau message" << endl;

        memset(message, 0, sizeof message); //vide le message

        //reception d'un nouveau message
        NetworkUDP::receiveDatagrams(listenSocket.getSocket(), message, sizeof message, (SOCKADDR*)&addr_in, listenSocket.getAddrinfo());

        cout << "Main() -> Message reçu : " << message << endl;
        cout << "Main() -> Type du message reçu : " << rfc.type(message) << endl;

        //decoupage du message en champs en fonction du délimiteur
        string testString(message);
        string champ1(rfc.fieldFromMesg(testString, 1, "§"));
        string champ2(rfc.fieldFromMesg(testString, 2, "§"));
        string champ3(rfc.fieldFromMesg(testString, 3, "§"));
        string champ4(rfc.fieldFromMesg(testString, 4, "§"));
        string champ5(rfc.fieldFromMesg(testString, 5, "§"));

        cout << "Main() -> decoupage : [" << champ1 << "] [" << champ2 << "] [" << champ3 << "] [" << champ4 << "] [" << champ5 << "]" << endl;

        //variables pour le switch
        string send;
        string ack;

        vector<Client>::iterator itClient;
        vector<Room*> roomList;
        Client *client = NULL;
        BOOK_ERROR_ENUM bookErrorEnum;

        int i = 0;



        switch (rfc.type(message)) {
            //si message de connection reçu
        case MSG_CON:
            cout << "Main() - Switch(MSG_CON) -> " << champ2 << " s'est connecté au serveur" << endl;

            if(book.addNewClient(champ2, champ3, champ4, &addr_in)==CLIENT_ADD_OK) {
                cout << "Main() - Switch(MSG_CON) -> " << champ2 << " a été ajouté à l'annuaire" << endl;

                //send = rfc.createMsgBookListResp(champ2, champ3, champ4, book.getClientRooms(champ2).size(), book.getClientRooms(champ2));
                //creation d'un ack pour le peer connecté
                ack = rfc.createMsgAck(MSG_ACK_CONNEXION_SUCCESS);
                //envoi de l'aquitement
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)book.findClient(champ2)->getSockAddr(), listenSocket.getAddrinfo());

                //renvoit la liste de client connectés au nouveau client
                for (i=0; i<book.getClients().size(); i++)
                {
                    roomList = book.getClientRooms(book.getClients().at(i).getName());
                    send = rfc.createMsgBookListResp(book.getClients().at(i).getName(), "127.0.0.1", "1337", roomList.size(), roomList);
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), (SOCKADDR*)book.findClient(champ2)->getSockAddr(), listenSocket.getAddrinfo());
                }

                cout << "Main() - Switch(MSG_CON) -> Message a renvoyer à tous les clients : [" << send << "]" << endl;
                //creation d'un message d'annuaire le concernant
                send = rfc.createMsgBookListResp(champ2, champ3, champ4, book.getClientRooms(champ2).size(), book.getClientRooms(champ2));

                //envoi les information du nouveau client à tout les autres clients (sauf lui meme))
                for (i=0; i<book.getClients().size(); i++)
                {
                    if (book.getClients().at(i).getName() != champ2)
                    {
                        NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), (SOCKADDR*)book.getClients().at(i).getSockAddr(), listenSocket.getAddrinfo());
                        cout << "Main() - Switch(MSG_CON) -> Message envoyé à " << book.getClients().at(i).getName() << endl;
                    }
                }

            } else
            {   //sinon si le client n'a pas pu etre ajouté à l'annuaire renvoi un ACK d'erreur
                cout << "Main() - Switch(MSG_CON) -> " << champ2 << " n'a pas pu etre ajouté à l'annuaire" << endl;
                ack = rfc.createMsgAck(MSG_ACK_CONNEXION_FAILED);
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)&addr_in, listenSocket.getAddrinfo());
            }

            break;
            //si message de déconnexion reçu
        case MSG_DECO:
            cout << "Main() - Switch(MSG_DECO) -> " << champ2 << " s'est déconnecté du serveur" << endl;
            //recherche le client
            client = book.findClient(champ2);

            if (client != NULL)
            {   //si il existe on le supprime

                bookErrorEnum = book.removeClient(champ2);
                cout << "BOOK ERROR NUM " << bookErrorEnum << endl;
                //si une erreur survient lors de la suppression on l'envoie
                if (bookErrorEnum == CLIENT_DEL_NOK)
                {
                    cout << "NOK NOK NOK" << endl;
                    ack = rfc.createMsgAck(MSG_ACK_REMOVE_CLIENT_FAILED);
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)book.findClient(champ2)->getSockAddr(), listenSocket.getAddrinfo());
                }
                else
                {   //sinon on envoie une confirmation de suppression
                    cout << "OK OK OK" << endl;
                    ack = rfc.createMsgAck(MSG_ACK_REMOVE_CLIENT_SUCCESS);
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)&addr_in, listenSocket.getAddrinfo());
                }
            }
            else
            {   //si le client n'existe pas on envoie une erreur de client inconnu
                cout << "BIZU TA ENVOYE CA" <<endl;
                ack = rfc.createMsgAck(MSG_ACK_UNKNOWN_CLIENT);
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)&addr_in, listenSocket.getAddrinfo());
            }

            break;
            //si message de communication reçu
        case MSG_COM:
            cout << "Main() - Switch(MSG_COM) -> " << champ2 << " à envoyé un message à redispatcher" << endl;
            //on cherche l'emetteur dans l'annuaire
            client = book.findClient(champ2);

            //si l'emmetteur est valide on l'envoi au salon general
            if (client != NULL)
            {
                for (i=0; i<book.getClients().size(); i++)
                {
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), message, strlen(message), (SOCKADDR*)book.getClients().at(i).getSockAddr(), listenSocket.getAddrinfo());
                }
            }

            break;
            //si reception d'un message de keep alive
        case MSG_LIVE:
            cout << "Main() - Switch(MSG_LIVE) -> " << champ2 << " signale qu'il est encore actif" << endl;
            //recherche du client
            client = book.findClient(champ2);
            //si le client existe on met a jour sa date du dernier keep alive
            if (client != NULL)
            {
                client->setLastalive(time(0));
            }
            else
            {   //sinon on envoi un ack pour signaller qu'il n'est pas connu du server
                ack = rfc.createMsgAck(MSG_ACK_UNKNOWN_CLIENT);
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)&addr_in, listenSocket.getAddrinfo());
            }

            break;

            // si message de connexion à un salon reçu
        case MSG_ROOM_JOIN:
            //on essaye d'ajouter le clien au salon
            bookErrorEnum = book.addClientToRoom(champ2, champ3);

            if (bookErrorEnum == CLIENT_ADD_TO_ROOM_OK)
            {   //si le client à bien été ajouté au salon
                cout << "Main() - Switch(MSG_ROOM_JOIN) -> " << champ2 << " a rejoint le salon " << champ3 << endl;

                client = book.findClient(champ2);
                roomList = book.getClientRooms(champ2);

                ack = rfc.createMsgAck(MSG_ACK_ADD_CLIENT_TO_ROOM_SUCCESS);
                ack += champ3;
                ack += "§";

                send = rfc.createMsgBookListResp(champ2, champ3, "1337", roomList.size(), roomList);
                //on envoie une confirmation au client
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)client->getSockAddr(), listenSocket.getAddrinfo());
                //et on envoie un message d'annuaire a tout les clients pour leur signaler que celui ci a rejoint un salon
                for (i=0; i<book.getClients().size(); i++) {
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), (SOCKADDR*)book.getClients().at(i).getSockAddr(), listenSocket.getAddrinfo());
                }
            }
            else {
                client = book.findClient(champ2);
                //si le client existe
                if (client != NULL)
                {   //on lui renvoi un message d'erreur lui indiquant qu'il n'a pas pu rejoindre le salon
                    ack = rfc.createMsgAck(MSG_ACK_ADD_CLIENT_TO_ROOM_FAILED);
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)client->getSockAddr(), listenSocket.getAddrinfo());
                }
                else
                {   //si il n'existe pas on lui signifie
                    ack = rfc.createMsgAck(MSG_ACK_UNKNOWN_CLIENT);
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)&addr_in, listenSocket.getAddrinfo());
                }
            }

            break;
            //si message pour quitter un salon reçu
        case MSG_ROOM_QUIT:
            client = book.findClient(champ2);

            //si le client existe
            if (client != NULL)
            {
                bookErrorEnum = book.removeClientFromRoom(champ2, champ3);
                if (bookErrorEnum == REMOVE_CLIENT_FROM_ROOM_OK)
                {   //si il a bien été retiré du salon on lui envoi une confirmation
                    cout << "Main() - Switch(MSG_ROOM_QUIT) -> " << champ2 << " à quitté le salon " << champ3 << endl;
                    ack = rfc.createMsgAck(MSG_ACK_REMOVE_CLIENT_TO_ROOM_SUCCESS);
                    send = rfc.createMsgBookListResp(champ2, champ3, "1337", book.getClientRooms(champ2).size(), book.getClientRooms(champ2));
                }
                else {//sinon on lui signifie que sa requete a echoué
                    ack = rfc.createMsgAck(MSG_ACK_REMOVE_CLIENT_TO_ROOM_FAILED);
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)client->getSockAddr(), listenSocket.getAddrinfo());
                }
            }
            else
            {   //si il n'existe pas on lui signifie
                ack = rfc.createMsgAck(MSG_ACK_UNKNOWN_CLIENT);
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)&addr_in, listenSocket.getAddrinfo());
            }

            break;
            //si reception d'un message de creation de salon
        case MSG_ROOM_CREATE:
            client = book.findClient(champ2);
            //si le client existe
            if (client != NULL)
            {   //on cree le salon et renvoie une confirmation
                book.addRoom(champ3);
                ack = rfc.createMsgAck(MSG_ACK_ROOM_CREATE_SUCCESS);
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)client->getSockAddr(), listenSocket.getAddrinfo());
            }
            else
            {   //sinon on lui signifie qu'il est inconnu
                ack = rfc.createMsgAck(MSG_ACK_UNKNOWN_CLIENT);
                NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)ack.c_str(), strlen(ack.c_str()), (SOCKADDR*)&addr_in, listenSocket.getAddrinfo());
            }

            break;
            //si reception d'une requete d'annuaire
        case MSG_BOOK_LIST_RQST:
            cout << "Main() - Switch(MSG_BOOK_LIST_RQST) -> " << champ2 << "a demandé l'annuaire" << endl;

            client = book.findClient(champ2);
            //si le client existe
            if (client != NULL)
            {
                for (i=0; i<book.getClients().size(); i++)
                {   //on lui renvoi la liste des clients présent dans l'annuaire
                    roomList = book.getClientRooms(book.getClients().at(i).getName());
                    send = rfc.createMsgBookListResp(book.getClients().at(i).getName(), "127.0.0.1", "1337", roomList.size(), roomList);
                    NetworkUDP::sendDatagrams(listenSocket.getSocket(), (char*)send.c_str(), strlen(send.c_str()), (SOCKADDR*)client->getSockAddr(), listenSocket.getAddrinfo());
                }
            }

            break;


        default:

            break;


        }
        cout << "Main() -> Traitement du message terminé" << endl;
    }

    return 1337;
}

