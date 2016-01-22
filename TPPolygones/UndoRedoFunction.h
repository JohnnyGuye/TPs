/*************************************************************************
                           UndoRedoFunction  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <UndoRedoFunction> (fichier UndoRedoFunction.h) ------
#if ! defined ( UNDOREDOFUNCTION )
#define UNDOREDOFUNCTION

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <UndoRedoFunction>
//
//
//------------------------------------------------------------------------ 

class UndoRedoFunction // interface
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~UndoRedoFunction ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    virtual void do() =0;
    // Mode d'emploi :
    // Execute l'action
    
    virtual void cancel() = 0;
    // Mode d'emploi :
    // Execute l'action inverse

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <UndoRedoFunction>

#endif // UNDOREDOFUNCTION
