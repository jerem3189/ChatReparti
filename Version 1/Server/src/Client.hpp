/* 
 * File:   Client.hpp
 * Author: Arnaud
 *
 * Created on 28 octobre 2013, 18:56
 */


#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <string>

class Client {
public:
    Client();
    Client(string name);
    virtual ~Client();
    string getName();
    void setName(string newName);
    bool isMaster();
    void setMaster(bool type);

    int addNetworkHints(string addressIp, string port);
    
    bool operator==(Client & client);
private:
	string name;
	
};

#endif	/* CLIENT_HPP */

