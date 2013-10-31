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

#include <string>

#include "MessagesTypesRFC1664.hpp"

class RFC1664 {
public:
	MessagesTypesRFC1664 type(string msg);
	string createMsgRoomQuit(string clientName,string roomName);
	string createMsgRoomJoin(string clientName,string roomName);
	string createMsgBookListRqst(string clientName);
	string createMsgBookListResp(string clientName);
	string createMsgDeco(string clientName);
	string createMsgCon(string clientName);
	string createMsgCom(string senderName,string receiverName,string message, string roomName);
        string createMsgKeepAlive(string clientName);
};

#endif  //_RFC1664_HPP
