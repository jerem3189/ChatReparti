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
    Group(Client c);
    virtual ~Group();
    Client master();
    vector<Client> getClients();
    int getNumberOfClients();
    int setNumberOfClients(int number);
private:
    int numberOfClients;
    vector<Client> clients;
};

#endif	/* GROUP_HPP */

