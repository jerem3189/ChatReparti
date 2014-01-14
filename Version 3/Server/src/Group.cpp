/* 
 * File:   Group.cpp
 * Author: arnaud
 * 
 * Created on 6 janvier 2014, 09:27
 */

#include "Group.hpp"

Group::Group() {
}

Group::Group(const Group& orig) {
}

Group::~Group() {
}

Client Group::master(){
    
}


vector<Client> Group::getClients() {
    return this->clients;
}

int Group::getNumber() {
    return this->numberOfClients;
}

int Group::setNumber(int num) {
    this->numberOfClients = num;
}
