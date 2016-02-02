/*************************************************************************
                           History.h  -  description
                             -------------------
    début                : 2016.01.22
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <History.h> (fichier History.h) ------
#if ! defined ( LOADALL )
#define LOADALL

//--------------------------------------------------- Interfaces utilisées
#include "UndoRedoFunction.h"

#include "deque"
#include "stack"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <History.h>
//
//
//------------------------------------------------------------------------ 

class History
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


    virtual ~History ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void undo();
    // Mode d'emploi:
    // defaire la derniere action
    
    void redo();
    // Mode d'emploi:
    // refaire la derniere action defaite
    
    
    void newFunction(UndoRedoFunction new);
    // Mode d'emploi:
    // ajoute l'action dans la pile et appelle la methode do

//------------------------------------------------------------------ PRIVE 
protected:
//----------------------------------------------------- Attributs protégés
	std::deque<UndoRedoFunction> undoDeque;
	std::stack<UndoRedoFunction> redoStack;


};

//----------------------------------------- Types dépendants de <LoadAll>

#endif // LOADALL
