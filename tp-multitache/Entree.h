#pragma once

#include "Globaux.h"
#include "Outils.h"

#include <signal.h> //pour sigaction SIGUSR2 et SIGCHLD
#include <stdlib.h> //pour exit

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>	//shared memory
#include <sys/sem.h>	//semget et autres
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

#include <map>
#include <tuple>
/** @brief Représente une des portes d'entrée.
*	Porte d'entrée gérant l'arrivée des voitures 
*	dans le Parking
**/

//	------------------------------------------- PRIVEE

/** Initialisation de la porte
*	@param le type de porte 
**/
//static void init(TypeBarriere type);

/** Fonctionnement de la porte
*	@param le type de la porte
**/
//static void run(TypeBarriere type);

/** Destruction de la porte 
*	@param le signal reçu
**/
//void killBarriere(int noSignal);

//	------------------------------------------- PUBLIC

/** @brief création de la tâche
*	@param type l'identificateur pour une des portes
*	@param memID l'ID de la mémoire partagée
*	@param semID l'ID du sémaphore
**/
void Entree(TypeBarriere type, int memID, int semID);


