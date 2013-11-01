//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Projet Chat
//  @ File Name : RFC1664.cpp
//  @ Date : 28/10/2013
//  @ Author :
//
//


#include "RFC1664.hpp"
#include "MessagesTypesRFC1664.hpp"
#include "ErrorCodes.hpp"
#include <cstring>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

MessagesTypesRFC1664 RFC1664::type(string msg) {
    std::size_t found = msg.find("CON§", 0);
    if (found != string::npos) {
        //std::cout << "Debug : Connect received"<<endl;
        return MSG_CON;
    } else {
        found = msg.find("DECO§", 0);
        if (found != string::npos) {
            return MSG_DECO;
        } else {
            found = msg.find("ROOM_QUIT§", 0);
            if (found != string::npos) {
                return MSG_ROOM_QUIT;
            } else {
                found = msg.find("ROOM_JOIN§", 0);
                if (found != string::npos) {
                    return MSG_ROOM_JOIN;
                } else {
                    found = msg.find("BOOK_LIST_RQST§", 0);
                    if (found != string::npos) {
                        return MSG_BOOK_LIST_RQST;

                    } else {
                        found = msg.find("COM§", 0);
                        if (found != string::npos) {
                            return MSG_COM;

                        } else {
                            found = msg.find("KEEP_ALIVE§", 0);
                            if (found != string::npos) {
                                return MSG_LIVE;

                            } else {
                                return ERR_BAD_MESSAGE;
                            }
                        }


                    }
                }

            }

        }

    }


}

string RFC1664::createMsgRoomQuit(string clientName, string roomName) {
    string retour = "ROOM_QUIT§" + clientName + "§" + roomName;
    return retour;
}

string RFC1664::createMsgRoomJoin(string clientName, string roomName) {
    string retour = "ROOM_JOIN§" + clientName + "§" + roomName;
    return retour;

}

string RFC1664::createMsgBookListRqst(string clientName) {
    string retour = "BOOK_LIST_RQST§" + clientName;
    return retour;
}

string RFC1664::createMsgBookListResp(string clientName, string ip, string port, int roomNb, vector<Room*> rooms) {
    string sRoomNb = to_string(roomNb);
    string retour = "BOOK_LIST_RESP§" + clientName + "§" + ip + "§" + port + "§" + sRoomNb;

    vector<Room*>::iterator it;
    for (it = rooms.begin(); it != rooms.end(); ++it) {
        retour += "§";
        retour += (*it)->getName();
    }

    return retour;
}

string RFC1664::createMsgDeco(string clientName) {

    string retour = "DECO§" + clientName;
    return retour;

}

string RFC1664::createMsgCon(string clientName) {
    string retour = "CON§" + clientName;
    return retour;

}

string RFC1664::createMsgCom(string senderName, string receiverName, string message, string roomName) {
    string retour = "COM§" + senderName + "§" + receiverName + "§" + message + "§" + roomName;
    return retour;
}

string RFC1664::createMsgKeepAlive(string clientName) {
    string retour = "KEEP_ALIVE§" + clientName;
    return retour;
}

string RFC1664::fieldFromMesg(string msg, int fieldNb, char delim) {
    string retour;
    istringstream iss(msg);
    string mot;
    //char delim = '§';
    int i = 1;
    while (std::getline(iss, mot, delim) && (i < fieldNb)) {
        //cout << i << endl;
        i++;
        //cout << i << endl;
        //cout << mot << endl;
    }
    //cout << mot<<endl;
    mot.erase(mot.size() - 1, 1);
    retour = mot;
    
    return retour;
}


