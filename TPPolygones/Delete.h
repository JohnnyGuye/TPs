/*************************************************************************
                           Delete  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <Delete> (fichier Delete.h) ------
#if ! defined ( DELETE )
#define DELETE
#include "Shape.h"
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Delete>
//
//
//------------------------------------------------------------------------ 

class Delete 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Delete ( );
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
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

Shape shape;



};

//----------------------------------------- Types dépendants de <Delete>

#endif // DELETE
