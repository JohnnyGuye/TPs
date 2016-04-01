/*
* Parking main file	
*/
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>	//ftok
#include <sys/ipc.h>	//ftok
#include <sys/shm.h>	//shared memory
#include <sys/sem.h>	//semget et autres
#include <iostream>

#include "Globaux.h"
#include "GestClav.h"
#include "Entree.h"
#include "Heure.h"
#include "Outils.h"
#include "Menu.h"

static int memId, semId;

int main(void)
{
	//------------------------------------------------------------------------Déclarations
	pid_t procClavier;
	pid_t porteGB;
	pid_t portePBP;
	pid_t porteABP;
	pid_t procHeure;
	
	//cout << DROITS << endl;
	//Memoire partagée
	if( (memId = shmget(ftok("./Parking", 1), sizeof(shMem),  IPC_CREAT | IPC_EXCL | DROITS) ) == -1)
	{
		cerr << "Echec à la création de la mémoire" << endl;
		return -1;
	}
	
	if( (semId = semget(ftok("./Parking", 2), 5,  IPC_CREAT | IPC_EXCL | DROITS ) ) == -1 )
	{
		cerr << "Echec à la création du sémaphore" << endl;
		return -1;
	}
	
	//----------------------------------------------------------------------Initialisations
	
	//Memoire partagées
	cerr << "Initialisation mémoire" << endl;
	//On récupère une référence sur la mémoire partagée pour pouvoir travailler dessus
	shMem *sharedMemory = (shMem *) shmat(memId, NULL, 0);
	for(unsigned int i = 0 ; i < NB_PLACES; i++)	{	sharedMemory->places[i] = { 0, 0, AUCUN };	}
	for(unsigned int i = 0 ; i < NB_BARRIERES_ENTREE; i++)	{	sharedMemory->requetes[i] = { 0, 0, AUCUN };	}
	sharedMemory->nbPlacesTaken = 0;
	shmdt(sharedMemory);	
	
	//On détache parce qu'il n'y en a plus besoin ici (plus le temps de faire des tests, 
	//mais ça a l'air faisable par héritage sans détacher en passant la référence. Hum
	
	cerr << "Création canaux" << endl;
	//Canaux entrée/clavier
	if(mkfifo(CANAL_PBP, DROITS) == -1)
	{
		cerr << "Fail PBP" << endl;
		return -1;
	}
	else if(mkfifo(CANAL_ABP, DROITS) == -1)
	{
		cerr << "Fail ABP" << endl;
		return -1;
	}
	else if(mkfifo(CANAL_GB, DROITS) == -1)
	{
		cerr << "Fail GB" << endl;
		return -1;
	}
	else if(mkfifo(CANAL_S, DROITS) == -1)
	{
		cerr << "Fail S" << endl;
		return -1;
	}
	else
	{
		cerr << "Tout les canaux ont bien été instanciés" << endl;
	}
	
	
	
	
	//Affichage
	InitialiserApplication(XTERM);
	
	
	
	//---------fin init
	//NOTE A MOI MEME : ne pas oublier les parenthèses, sinon == est testé en premier
	//Donc on procHeure = 0 parce que faux, donc recréer un processus ActiverHeure...
	//et on perd la trace du premier
	//Créations des processus
	if( (procHeure = ActiverHeure() ) == 0)
	{
		procHeure = ActiverHeure();
	}
	else if( ( procClavier = fork() ) == 0)	//processus clavier
	{
		ClavManager();
	}
	else if( ( porteGB = fork() ) == 0)
	{
		Entree(ENTREE_GASTON_BERGER, memId, semId);
	}
	
	else if( ( portePBP = fork() ) == 0)
	{
		Entree(PROF_BLAISE_PASCAL, memId, semId);
	}
	else if( ( porteABP = fork() ) == 0)
	{
		Entree(AUTRE_BLAISE_PASCAL, memId, semId);
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
		
		unlink(CANAL_PBP);
		unlink(CANAL_ABP);
		unlink(CANAL_GB);
		unlink(CANAL_S);
		
		shmctl(memId, IPC_RMID, 0);
		semctl(semId, IPC_RMID, 0);
		
		TerminerApplication();
		exit(0);
	}
	//------debut close
	
	
	//Fin propre
	
	
	
	
	return 0;
	
	
}
