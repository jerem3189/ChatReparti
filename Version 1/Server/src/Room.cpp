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

int Room::addClient(Client client) {
    
    //clients.insert(clients.end(),it,client);
    return 1;
}

int Room::delClient(Client client) {
    std::vector<int>::iterator it;

  // iterator pour trouver l'element correspondant au client
//  it = find (clients.begin(), clients.end(), client);
    //clients.erase(it);
    //Fuck it 
}

string Room::getName() {
    return roomName;

}

void Room::setName(string newName) {
    roomName=newName;
}
/*
vector<Client> Room::getClients() {
    //return clients&;
    
}*/

void Room::setClients(vector<Client> newClients) {
    //clients = newClients;
}

