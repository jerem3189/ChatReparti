/* 
 * File:   Client.hpp
 * Author: darkey
 *
 * Created on 28 octobre 2013, 18:56
 */

#ifndef CLIENT_HPP
#define	CLIENT_HPP

class Client {
public:
    Client();
    Client(const Client& orig);
    virtual ~Client();
    getName();
    setName(string newName);
private:

};

#endif	/* CLIENT_HPP */

