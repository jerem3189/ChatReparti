/** \file ErrorCodes.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_ERRORCODES_H)
#define _ERRORCODES_H

/**
 * énumération des erreurs UDP
 */
enum UDP_ERROR_ENUM {
    UDP_ERROR
};

/**
 * énumération des erreur de socket possible
 */
enum SOCK_ERROR_ENUM {
    SOCK_OK,
    SOCK_NOK,
    SOCK_BIND_OK,
    SOCK_BIND_NOK,
    ERR_SOCK_HINTS,
    ERR_SOCK_CREATE,
    ERR_GETADDRINFO,
    NETWORK_HINTS_OK
};
/**
 * enumération des erreur d'annuaire possible
 */
enum BOOK_ERROR_ENUM {
    CLIENT_ADD_OK,
    CLIENT_ADD_NOK,
    ERR_UNKNOWN_ROOM
};

#endif  //_ERRORCODES_H
