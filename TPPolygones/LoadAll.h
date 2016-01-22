/*************************************************************************
                           LoadAll.h  -  description
                             -------------------
    début                : 2016.01.22
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <LoadAll.h> (fichier LoadAll.h) ------
#if ! defined ( LOADALL )
#define LOADALL

//--------------------------------------------------- Interfaces utilisées
#include "Shape.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <LoadAll.h>
//
//
//------------------------------------------------------------------------ 

class LoadAll : public UndoRedoFunction
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


    virtual ~LoadAll ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    virtual void do();
    // Mode d'emploi:
    // execute la methode move de shape avec direction en parametre
    
    virtual void cancel();
    // Mode d'emploi:
    // deplace la forme associe  avec -direction en parametre;
    
    

//------------------------------------------------------------------ PRIVE 
protected:
//----------------------------------------------------- Attributs protégés
	std::map<string,Shape> shapes;


};

//----------------------------------------- Types dépendants de <LoadAll>

#endif // LOADALL
