/*
* prout file
*
*
*
*
*/
using namespace std;
#include "Room.hpp"
#include "Client.hpp"
#include <vector>


 string roomName;
 vector<Client> clients;

int Room::addClient(Client *client) {
    cout << "ajout du client " << client->getName() << " dans la room " << this->getName() << endl;
    return 1;
}

int Room::delClient(Client *client) {
   
   return 0;
}

string Room::getName() {
    return name;

}

void Room::setName(string newName) {
    roomName=newName;
}
/*
vector<Client> Room::getClients() {
    //return clients&;
    
}*/

void Room::setClients(vector<Client*> newClients) {
    //clients = newClients;
}

