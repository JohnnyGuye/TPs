#include "GestClav.h"

//#include <fcntl.h>
//#include <unistd.h>
//#include <sys/types.h>
#include "Menu.h"
#include "Globaux.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h> //pour exit
#include <iostream>
//-----------------------------------------------Portée programme

static int tubePBP, tubeABP, tubeGB, tubeS;

/** @brief fonctionnement du processus Clavier
**/

void ClavManager()
{
	//init
	cerr << "Initialisation des canaux clavier" << endl;
	tubePBP = open(CANAL_PBP, O_WRONLY);
	cerr << "tubPBP" << endl;
	tubeABP  = open(CANAL_ABP, O_WRONLY);
	cerr << "tubABP" << endl;
	tubeGB = open(CANAL_GB, O_WRONLY);
	cerr << "tubGB" << endl;
	tubeS = open(CANAL_S, O_WRONLY);
	cerr << "tubS" << endl;
	//WIP
	for(;;)    Menu();

	//end
}

/** @brief gestionnaire de touches, 
*	voir Menu(void) de Menu.h pour le fonctionnement**/
void Commande(char code,unsigned int valeur)
{
	switch(code)
    {
        case 'e':
        case 'E':
			if(valeur == 0)
			{
				close(tubePBP);
				close(tubeABP);
				close(tubeGB);
				close(tubeS);
				exit(0);
			}
//end application
            break;
            //Cas professeur
    	case 'p':
		case 'P':
			{
				indexVoiture = (indexVoiture + 1) % 1000;
		
				Voiture v;
				v.numIndex = indexVoiture;
				v.arrivee = time(NULL);
				v.usager = PROF;
		
				if(valeur == 1)//Blaise Pascal
				{
					write(tubePBP, &v, sizeof(v));
				}
				else if(valeur == 2)//Gaston Berger
				{
					write(tubeGB, &v, sizeof(v));
				}
			}
            break;
            //Cas autres
        case 'a':
        case 'A':
		    {
		    	indexVoiture = (indexVoiture + 1) % 1000;
			
				Voiture v;
				v.numIndex = indexVoiture;
				v.arrivee = time(NULL);
				v.usager = AUTRE;
			
				if(valeur == 1)//Blaise Pascal
				{
					write(tubeABP, &v, sizeof(v));
				}
				else if(valeur == 2)//Gaston Berger
				{
					write(tubeGB, &v, sizeof(v));
				}
        	}
        	break;
        case 's':
        case 'S':
        	{
        		if(valeur < 9)
        		{
        			write(tubeS, &valeur, sizeof(valeur));
        		}
        	}
        	break;
        default:
            break;
    }
}
