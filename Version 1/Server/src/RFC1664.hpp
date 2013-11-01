//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Projet Chat
//  @ File Name : RFC1664.h
//  @ Date : 28/10/2013
//  @ Author :
//
//

using namespace std;
#if !defined(_RFC1664_HPP)
#define _RFC1664_HPP





#include <sstream>


#include <string>
#include <vector>
#include "Room.hpp"
#include "MessagesTypesRFC1664.hpp"

class RFC1664 {
public:
    template<typename T>
    std::string to_string( const T & Value )
    {
        std::ostringstream oss;
        oss << Value;
        return oss.str();
    }
    MessagesTypesRFC1664 type(string msg);
    string createMsgRoomQuit(string clientName,string roomName);
    string createMsgRoomJoin(string clientName,string roomName);
    string createMsgBookListRqst(string clientName);
    string createMsgBookListResp(string clientName,string ip,string port,int roomNb,vector<Room*> rooms);
    string createMsgDeco(string clientName);
    string createMsgCon(string clientName, string addressIp);
    string createMsgCom(string senderName,string receiverName,string message, string roomName);
    string createMsgKeepAlive(string clientName);
};

#endif  //_RFC1664_HPP
