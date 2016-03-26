#include "GestClav.h"

//#include <fcntl.h>
//#include <unistd.h>
//#include <sys/types.h>
#include "Menu.h"
#include <stdlib.h> //pour exit

//-------------------------------------------------Portée fichier

static void Clavier()
{
	indexVoiture = 0;
}


static void killClavier()
{
	exit(0);
}


//-----------------------------------------------Portée programme


/** @brief fonctionnement du processus Clavier
**/

void ClavManager()
{

	//init
	Clavier();
	
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
				killClavier();
			}
//end application
            break;
    	case 'p':
		case 'P':
		
			indexVoiture = (indexVoiture + 1) % 1000;
			
			if(valeur == 1)//Blaise Pascal
			{
			
			}
			else if(valeur == 2)//Gaston Berger
			{
			
			}
            break;
        case 'a':
        case 'A':
        
        	indexVoiture = (indexVoiture + 1) % 1000;
        	
        	if(valeur == 1)//Blaise Pascal
			{
			
			}
			else if(valeur == 2)//Gaston Berger
			{
			
			}
        
        	break;
        case 's':
        case 'S':
        
        	break;
        default:
            break;
    }
}
