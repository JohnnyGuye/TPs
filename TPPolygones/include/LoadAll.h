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

class LoadAll : public UndoRedoFunction
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    LoadAll (ShapeManager* shapeManager = nullptr);

    virtual ~LoadAll ( );

    /** Delete all the shapes **/
    virtual void Do();

    /** Restore all the shapes **/
    virtual void Cancel();

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Attributs protégés
	std::map<string,Shape> shapes;


};

//----------------------------------------- Types dépendants de <LoadAll>

#endif // LOADALL
