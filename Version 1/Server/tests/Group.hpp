/*
* prout file
*
*
*
*
*/

#if !defined(_GROUP_H)
#define _GROUP_H

#include "Client.hpp"
#include <iostream>
#include <vector>

class Group {
public:
	Client master();
	vector<Client> getClients();
	int getNumero();
	int setNumero(int numero);
private:
	vector<Client> clients;
	int numero;
};

#endif  //_GROUP_H
