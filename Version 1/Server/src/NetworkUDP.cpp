/** \file NetworkUDP.cpp
 * Fichier regroupant les fonctions en rapport avec le réseaux
 * Envois, Réceptions, Récupération d'addresse IP
 */

#include "NetworkUDP.hpp"
/**
 * Fonction générique d'envoi de datagramme
 * @param sock socket
 * @param *data contenu du message
 * @param len taille du message
 * @param *address adresse du socket
 * @param *infos adresse destinataire
 * @return le nombre de bytes envoyés
 * @return -1 en cas d'echec
 */
int NetworkUDP::sendDatagrams(SOCKET sock, char *data, size_t len, SOCKADDR *address, ADDRINFO *infos) {
    int nbOctets = 0;
    nbOctets = sendto(sock, data, len, 0, address, infos->ai_addrlen);

    if (nbOctets  < len)
        return ERR_SEND;

    return SEND_OK;
}

/**
 * Fonction générique de réception de datagramme
 * @param sock socket d'écoute
 * @param *data contenu du message
 * @param len taille maximum du message
 * @param *address adresse du socket
 * @param *infos adresse destinateur
 * @return le nombre de bytes reçus
 * @return -1 en cas d'echec
 */
int NetworkUDP::receiveDatagrams(SOCKET sock, char *data, size_t maxLen, SOCKADDR *address, ADDRINFO *infos) {
    int nbOctets = 0;
    nbOctets = recvfrom(sock, data, maxLen, 0, address, &(infos->ai_addrlen));

    if (nbOctets  < 0)
        return ERR_RECV;

    return RECV_OK;
}
/**
 * Fonction récupérant l'adresse IP du post utilisé
 * @return ss la chaine contenant l'adresse ip
 */
string NetworkUDP::getIp_static() {

    char hostname[128];
    struct hostent *host;

    gethostname(hostname, sizeof hostname);
    host = gethostbyname(hostname);

    std::string ss(inet_ntoa(*(struct in_addr*)host->h_addr));

    return ss;
}
/**
 * Fonction récupérant l'adresse IP de l'interface utilisée
 * @return ss2 la chaine contenant l'adresse ip
 */
string NetworkUDP::getIp_interface(string interface) {

    struct ifaddrs * ifAddrStruct=NULL;
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
            cout << ss << "\n" << endl;
            ss2 = ss;
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return ss2;
}
