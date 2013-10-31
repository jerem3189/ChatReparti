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

	//int		Read(void * pData, size_t nDataSize);
	//int		Write(void * pData, size_t nDataSize);

#endif  //_SENDINGUDP_H
