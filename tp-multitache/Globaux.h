#pragma once

#include <string.h>

#include "Outils.h"

//Droits sur les canaux/semaphore/mémoire partagée
//NOTE A MOI MEME : 0 devant un nombre le transforme en octal
const mode_t DROITS = 0660;

//Noms des canaux
static const char
	*CANAL_PBP = "Canal_Prof_Blaise_Pascal",
	*CANAL_ABP = "Canal_Autre_Blaise_Pascal",
	*CANAL_GB = "Canal_Gaston_Berger",
	*CANAL_S = "Canal_Sortie";

typedef enum Semaphore {
	PortePBPtoExit,
	PorteABPtoExit,
	PorteGBtoExit
} Semaphore;
//Qu'est-ce que c'est que donc une voiture ?
//Note à moi-même, c'était pas ouf de rajouter 
//une heure de départ, parce qu'elle n'est plus
//gérée après.	
typedef struct {
	time_t arrivee;
	int numIndex;
	TypeUsager usager;
} Voiture;
	
typedef struct {
	Voiture places[NB_PLACES];
	Voiture requetes[NB_BARRIERES_ENTREE];
	int nbPlacesTaken;
} shMem;
