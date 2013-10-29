/** \file SendingUDP.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_SENDINGUDP_H)
#define _SENDINGUDP_H

#include "Thread.hpp"

class SendingUDP : public Thread {
public:
	void sendDatagrams();
	void run();
};

#endif  //_SENDINGUDP_H
