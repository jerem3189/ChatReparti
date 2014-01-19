/*
 * File:   Group.cpp
 * Author: arnaud
 *
 * Created on 6 janvier 2014, 09:27
 */

#include "Group.hpp"

Group::Group() {

}

/**
 * Constructeur d'un group vide avec un nouveau maitre
 * @param c le client à ajouter au groupe vide.
 */
Group::Group(Client c) {
    c.setMaster(true);
    this->numberOfClients=1;
    this->clients.push_back(c);


}



Group::~Group() {
}

//a sécuriser
/**
 * cherche dans la liste des clients du groupe le maitre
 * @return le client maitre du group
 */
Client Group::master() {
    for (int i=0; i<numberOfClients; i++)
    {
        if (getClients().at(i).isMaster())
            return getClients().at(i);
        ;

    }
}


vector<Client> Group::getClients() {
    return this->clients;
}

int Group::getNumberOfClients() {
    return this->numberOfClients;
}

int Group::setNumberOfClients(int num) {
    this->numberOfClients = num;
}
