/** \file ReceptionUDP.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_RECEPTIONUDP_H)
#define _RECEPTIONUDP_H

#include "Thread.hpp"

class ReceptionUDP : public Thread, public Thread {
public:
	void receiveDatagrams();
	void run();
};

#endif  //_RECEPTIONUDP_H
