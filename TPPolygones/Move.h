/*************************************************************************
                           Move.h  -  description
                             -------------------
    début                : 2016.01.22
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <Move.h> (fichier ${file_name}) ------
#if ! defined ( MOVE )
#define MOVE

//--------------------------------------------------- Interfaces utilisées
#include "Shape.h"
#include "Vector2D.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Move.h>
//
//
//------------------------------------------------------------------------ 

class Move : public UndoRedoFunction
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


    virtual ~Move ( );
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
	Shape shape;
	Vector2D direction;


};

//----------------------------------------- Types dépendants de <Move>

#endif // MOVE
