/** \file Signalisation.cpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#include "Signalisation.hpp"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int Signalisation::sendKeepAlive() {

}

void sleep(int nbr_seconds)
{
	clock_t goal;
	goal = (nbr_seconds * CLOCKS_PER_SEC) + clock();
	while(goal > clock())
	{
		;
	}
}

int Signalisation::runkeep() {


   while(1)
 {
    //printf("Il vous reste %ld secondes.\n", i);
    // ENVOI KEEP ALIVE
    sleep(1);



 }
return 0;
}

int Signalisation::time() {

}

