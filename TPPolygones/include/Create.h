/*************************************************************************
                           Create  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <Create> (fichier Create.h) ------
#if ! defined ( CREATE )
#define CREATE
#include "Shape.h"

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Create>
//
//
//------------------------------------------------------------------------ 

class Create // interface
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Create ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    virtual void do();
    // Mode d'emploi :
    // Execute l'action
    
    virtual void cancel();
    // Mode d'emploi :
    // Execute l'action inverse

//------------------------------------------------------------------ PRIVE 


protected:
//----------------------------------------------------- Attributs protégés

Shape shape;


};

//----------------------------------------- Types dépendants de <Create>

#endif // CREATE
