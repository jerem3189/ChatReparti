/* 
 * File:   topology.hpp
 * Author: darkey
 *
 * Created on 6 janvier 2014, 09:29
 */

#ifndef TOPOLOGY_HPP
#define	TOPOLOGY_HPP
#include <string>
using namespace std;

class Topology {
public:
    Topology();
    Topology(const topology& orig);
    virtual ~topology();
    int createGroup(string name);
    int rebuildChain();
    int nbGroups();
    int addClientToGroup(string name);
    int removeClient(string name);
private:

};

#endif	/* TOPOLOGY_HPP */

