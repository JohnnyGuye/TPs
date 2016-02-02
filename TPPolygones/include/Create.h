/*************************************************************************
                           Create  -  description
                             -------------------
    début                : 2016.01.22
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

class Create: public UndoRedoFunction
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

	Create ( const Create & unCreate);
	// Mode d'emploi : Constructeur de copie
	//

	Create ( Shape theShape)
	// Mode d'emploi :
	// cree l'objet a partir de shape

    virtual ~Create ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    virtual void Do();
    // Mode d'emploi :
    // Execute l'action
    
    virtual void Cancel();
    // Mode d'emploi :
    // Execute l'action inverse

//------------------------------------------------------------------ PRIVE 


protected:
//----------------------------------------------------- Attributs protégés

Shape shape;


};

//----------------------------------------- Types dépendants de <Create>

#endif // CREATE
