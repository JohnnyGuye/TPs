/*
* Parking main file	
*/
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

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
	pid_t portePBP;
	pid_t porteABP;
	pid_t procHeure;
	
	
	//Affichage
	InitialiserApplication(XTERM);
	
	if(procHeure = ActiverHeure() == -1)
	{
		cerr << "Erreur pour l'affichage de l'heure" << endl;
		return -1;
	}
	
	//---------fin init
	//Créations des processus
	if( ( procClavier = fork() ) == 0)	//processus clavier
	{
		ClavManager();
	}
	
	else if( ( porteGB = fork() ) == 0)
	{
		Entree(ENTREE_GASTON_BERGER, MEM_ID, SEM_ID);
	}
	
	else if( ( portePBP = fork() ) == 0)
	{
		Entree(PROF_BLAISE_PASCAL, MEM_ID, SEM_ID);
	}
	else if( ( porteABP = fork() ) == 0)
	{
		Entree(AUTRE_BLAISE_PASCAL, MEM_ID, SEM_ID);
	}
	else
	{
		waitpid( procClavier, NULL, 0);
		
		kill(porteGB, SIGUSR2);
		kill(portePBP, SIGUSR2);
		kill(porteABP, SIGUSR2);
		kill(procHeure, SIGUSR2);
		
		waitpid(porteGB, NULL, 0);
		waitpid(portePBP, NULL, 0);
		waitpid(porteABP, NULL, 0);
		waitpid(procHeure, NULL, 0);
		
		TerminerApplication();
		exit(0);
	}
	//------debut close
	
	
	//Fin propre
	
	
	
	
	return 0;
	
	
}
