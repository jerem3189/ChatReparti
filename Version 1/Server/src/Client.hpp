/* 
 * File:   Client.hpp
 * Author: Arnaud
 *
 * Created on 28 octobre 2013, 18:56
 */


#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <string>

class Socket;

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
    void setLastalive(time_t lastalive);
    time_t getLastalive() const;
private:
	string name;
        time_t lastalive;
    Socket *socket;
	
};

#endif	/* CLIENT_HPP */

