/* 
 * File:   Client.hpp
 * Author: Arnaud
 *
 * Created on 28 octobre 2013, 18:56
 */


#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <string>

using namespace std;
class Client {
public:
    Client();
    Client(const Client& orig);
    virtual ~Client();
    string getName();
    void setName(string newName);
    bool isMaster();
    void setMaster(bool type);
private:

};

#endif	/* CLIENT_HPP */

