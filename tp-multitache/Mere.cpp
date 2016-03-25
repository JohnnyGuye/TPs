/*
* Parking main file	
*/
#include <unistd.h>
#include <sys/wait.h>

#include "GestClav.h"
#include "Entree.h"
#include "Heure.h"
#include "Outils.h"
#include "Menu.h"

int MEM_ID;
int SEM_ID;

int main(void)
{
	//Init
	pid_t procClavier;
	pid_t porteGB;
	
	
	//Affichage
	InitialiserApplication(XTERM);
	
	
	//---------fin init
	//Créations des processus
	if( ( procClavier = fork() ) == 0)	//processus clavier
	{
		ClavManager();
	}
	else if( ( porteGB = fork() ) == 0)
	{
		Entree(GB_ALL, MEM_ID, SEM_ID);
	}
	else
	{
		waitpid( procClavier, NULL, 0);
		
		kill(porteGB, SIGUSR2);
		
		waitpid(porteGB, NULL, 0);
		
		TerminerApplication();
		exit(0);
	}
	//------debut close
	
	
	//Fin propre
	
	
	
	
	return 0;
	
	
}
