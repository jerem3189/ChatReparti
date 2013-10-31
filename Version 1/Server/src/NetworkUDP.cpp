/** \file SendingUDP.cpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#include "SendingUDP.hpp"

int NetworkUDP::sendDatagrams(SOCKET sock, char *data, size_t len, sockaddr address) {
	socklen_t addr_size = sizeof address;

	return sendto(sock, data, sizeof data, 0, (sockaddr *)&address, addr_size);
}

int NetworkUDP::receiveDatagrams(SOCKET sock, char *data, size_t len, sockaddr address) {
	socklen_t addr_size = sizeof address;

	return recvfrom(sock, data, sizeof data, 0, &address, &addr_size);
}

void NetworkUDP::run() {

}
