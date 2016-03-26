#pragma once

//	----------------------------------- PRIVEE

/** Le numéro d'immatriculation de la prochaine
*	voiture **/
static int indexVoiture;

/** @brief Constructeur du processus Clavier
**/
//static void Clavier();

/** @brief Destructeur du processus Clavier
**/
//static void killClavier();

// 	----------------------------------- PUBLIC

void ClavManager();

void Commande( char code, unsigned int value);
