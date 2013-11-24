#include <iostream>
#include "../../src/Room.hpp"
#include "../../src/Book.hpp"

#include <vector>



int main()
{
	
	vector<string> roomList;
	roomList.push_back("zizi");
	roomList.push_back("zozo");
	roomList.push_back("zuzu");
	
	Book book = Book();
	book.addRoom("zozo");
	book.addRoom("zizi");
	
	
	vector<Room> rooms;
	rooms = book.getRooms();
	
	cout << "Taille roooms : " << rooms.size() << endl;
	
	vector<Room>::iterator it;
		
		bool result = false;
		for(it = rooms.begin(); it != rooms.end(); ++it)
		{
			cout << " room : " << (*it).getName() << endl;
		}
	
	
	book.addNewClient("jeremy", roomList);
	
	vector<Client> clients;
	clients = book.getClients();
	
	cout << "nb clients = " << clients.size() << endl;
	
	if (book.findClient("herbert") != NULL) cout << "herbert trouvé !" << endl; else cout << "herbert pas trouvé" << endl;
	if (book.findClient("jeremy") != NULL) cout << "jérémy trouvé !" << endl; else cout << "jérémy pas trouvé" << endl;
	
	return 0;
}
