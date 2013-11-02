/** \file ErrorCodes.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_ERRORCODES_H)
#define _ERRORCODES_H


enum UDP_ERROR_ENUM {
    UDP_ERROR
};

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

enum BOOK_ERROR_ENUM {
    CLIENT_ADD_OK,
    CLIENT_ADD_NOK,
    ERR_UNKNOWN_ROOM
};

#endif  //_ERRORCODES_H
