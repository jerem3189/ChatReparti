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

<<<<<<< HEAD
int NetworkUDP::getIp_static() {
    =======
    string NetworkUDP::getIp_static() {

        char hostname[128];
        struct hostent *host;
        >>>>>>> e1cf4ab071c09a28fc46c394490a9782c53f58b8

        char hostname[128];
        struct hostent *host;

        gethostname(hostname, sizeof hostname);


        <<<<<<< HEAD
        host = gethostbyname(hostname);

        std::string ss(inet_ntoa(*(struct in_addr*)host->h_addr));
        cout << ss << "\n" << endl;

        return 0;
    }

    int NetworkUDP::getIp_interface() {

        struct ifaddrs * ifAddrStruct=NULL;
        =======
            std::string ss(inet_ntoa(*(struct in_addr*)host->h_addr));

        return ss;
    }

    string NetworkUDP::getIp_interface(string interface) {

        struct ifaddrs * ifAddrStruct=NULL;
        >>>>>>> e1cf4ab071c09a28fc46c394490a9782c53f58b8
        struct ifaddrs * ifa=NULL;
        void * tmpAddrPtr=NULL;
        std::string etc = interface;
        const char* eth=etc.c_str();
        std::string ss2;

        getifaddrs(&ifAddrStruct);

        for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
            if (ifa ->ifa_addr->sa_family==AF_INET && strcmp(ifa->ifa_name,eth)==0 ) {
                tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
                char addressBuffer[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
                std::string ss(addressBuffer);
                <<<<<<< HEAD
                cout << ss << "\n" << endl;

                =======
                    ss2 = ss;
                >>>>>>> e1cf4ab071c09a28fc46c394490a9782c53f58b8
            }
        }
        if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
        return ss2;
    }
