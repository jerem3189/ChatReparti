/** \file SendingUDP.cpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#include "NetworkUDP.hpp"

int NetworkUDP::sendDatagrams(SOCKET sock, char *data, size_t len, SOCKADDR *address) {
    socklen_t addr_size = sizeof *address;

    return sendto(sock, data, len, 0, address, addr_size);
}

int NetworkUDP::receiveDatagrams(SOCKET sock, char *data, size_t maxLen, SOCKADDR *address) {
    socklen_t addr_size = sizeof *address;

    return recvfrom(sock, data, maxLen, 0, address, &addr_size);
}

int NetworkUDP::getIp_static() {

    char hostname[128];
    struct hostent *host;

    gethostname(hostname, sizeof hostname);


    host = gethostbyname(hostname);

    std::string ss(inet_ntoa(*(struct in_addr*)host->h_addr));
    cout << ss << "\n" << endl;

    return 0;
}

int NetworkUDP::getIp_interface() {

    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
    std::string etc = "eth1";
    const char* eth=etc.c_str();

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa ->ifa_addr->sa_family==AF_INET && strcmp(ifa->ifa_name,eth)==0 ) {
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            std::string ss(addressBuffer);
            cout << ss << "\n" << endl;

        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return 0;
}
