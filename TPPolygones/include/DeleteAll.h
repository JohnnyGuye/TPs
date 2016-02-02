/*************************************************************************
                           DeleteAll.h  -  description
                             -------------------
    début                : 2016.01.22
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <DeleteAll.h> (fichier DeleteAll.h) ------
#if ! defined ( DELETEALL )
#define DELETEALL

//--------------------------------------------------- Interfaces utilisées
#include "Shape.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <DeleteAll.h>
//
//
//------------------------------------------------------------------------

class DeleteAll : public UndoRedoFunction
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


    virtual ~DeleteAll ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    virtual void Do();
    // Mode d'emploi:
    // execute la methode move de shape avec direction en parametre

    virtual void Cancel();
    // Mode d'emploi:
    // deplace la forme associe  avec -direction en parametre;



//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Attributs protégés
	std::map<std::string,Shape> shapes;


};

//----------------------------------------- Types dépendants de <DeleteAll>

#endif // DELETEALL
