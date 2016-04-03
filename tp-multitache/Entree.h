#pragma once

#include "Outils.h"
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


