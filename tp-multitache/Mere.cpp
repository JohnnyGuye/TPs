/*
* Parking main file	
*/
#include <unistd.h>

#include "Heure.h"
#include "Outils.h"
#include "Menu.h"

int main(void)
{
	InitialiserApplication(XTERM);
	
	//---------fin init
	sleep(10);
	//------debut close
	
	TerminerApplication();
	return 0;
}
