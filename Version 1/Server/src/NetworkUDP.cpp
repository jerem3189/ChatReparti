/** \file SendingUDP.cpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#include "NetworkUDP.hpp"

int NetworkUDP::sendDatagrams(SOCKET sock, char *data, size_t len, SOCKADDR *address) {
	socklen_t addr_size = sizeof address;

    return sendto(sock, data, len, 0, address, addr_size);
}

int NetworkUDP::receiveDatagrams(SOCKET sock, char *data, size_t maxLen, SOCKADDR *address) {
	socklen_t addr_size = sizeof address;

    return recvfrom(sock, data, maxLen, 0, address, &addr_size);
}
