/* 
 * File:   Group.hpp
 * Author: darkey
 *
 * Created on 6 janvier 2014, 09:27
 */

#ifndef GROUP_HPP
#define	GROUP_HPP

#include "Client.hpp"

#include <vector>

class Group {
public:
    Group();
    Group(const Group& orig);
    virtual ~Group();
    Client master();
    vector<Client> getClients();
    int getNumber();
    int setNumber(int number);
private:
    int number;
    vector<Client> clients;
};

#endif	/* GROUP_HPP */

