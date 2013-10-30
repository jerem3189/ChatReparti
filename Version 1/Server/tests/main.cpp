#include <iostream>
#include "Room.hpp"
#include "Book.hpp"

#include <vector>



int main()
{
	
	vector<string> roomList;
	roomList.push_back("zizi");
	roomList.push_back("zozo");
	roomList.push_back("zuzu");
	
	Book book = Book();
	book.addRoom("zozo");
	book.addRoom("ziiz");
	
	
	vector<Room> rooms;
	rooms = book.getRooms();
	
	cout << "Taille roooms : " << rooms.size() << endl;
	
	vector<Room>::iterator it;
		
		bool result = false;
		for(it = rooms.begin(); it != rooms.end(); ++it)
		{
			cout << " room : " << (*it).getName() << endl;
		}
	
	
	book.addNewClient("jérémy", roomList);
	
	
	
	return 0;
}
