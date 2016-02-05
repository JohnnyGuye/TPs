/*************************************************************************
                           LoadAll.h  -  description
                             -------------------
    début                : 2016.01.22
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <LoadAll.h> (fichier LoadAll.h) ------
#if ! defined ( LOADALLSHAPES )
#define LOADALLSHAPES

//--------------------------------------------------- Interfaces utilisées
#include "UndoRedoFunction.h"
#include <vector>

class LoadAllShapes : public UndoRedoFunction
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    LoadAllShapes ( ShapeManager* shapeManager = nullptr, std::vector<Shape*> shapes = {});

    virtual ~LoadAllShapes ( );

    /** Delete all the shapes **/
    virtual void Do();

    /** Restore all the shapes **/
    virtual void Cancel();

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Attributs protégés
	std::vector<Shape*> ShapesOnHold;


};

//----------------------------------------- Types dépendants de <LoadAll>

#endif // LOADALL
