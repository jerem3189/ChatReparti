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
 * énumération des erreurs de socket possibles
 */
enum SOCK_ERROR_ENUM {
    SOCK_OK,
    SOCK_NOK,
    SOCK_BIND_OK,
    SOCK_BIND_NOK,
    ERR_SOCK_HINTS,
    ERR_SOCK_CREATE,
    ERR_GETADDRINFO,
    NETWORK_HINTS_OK,
    NETWORK_HINTS_NOK
};

/**
 * enumération des erreurs d'annuaire possibles
 */
enum BOOK_ERROR_ENUM {
    CLIENT_ADD_OK,
    CLIENT_ADD_NOK,
    ERR_UNKNOWN_ROOM,
    ERR_UNKNOWN_CLIENT,
    CLIENT_DEL_NOK,
    CLIENT_DEL_OK,
    ERR_ADD_CLIENT_TO_ROOM,
    CLIENT_ADD_TO_ROOM_OK,
    ERR_REMOVE_CLIENT_FROM_ROOM,
    REMOVE_CLIENT_FROM_ROOM_OK
};

/**
 * enumération des erreurs de room possibles
 */
enum ROOM_ERROR_ENUM {
    ROOM_CLIENT_ADD_OK,
    ROOM_CLIENT_ADD_NOK
};

/**
 * enumération des erreurs de network possibles
 */
enum NETWORK_ERROR_ENUM {
    ERR_SEND,
    ERR_RECV,
    SEND_OK,
    RECV_OK
};

#endif  //_ERRORCODES_H
