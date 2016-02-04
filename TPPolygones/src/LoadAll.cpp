/*************************************************************************
                           LoadAll  -  description
                             -------------------
    début                : 04/12/2015
    copyright            : (C) 2015 par B3403
*************************************************************************/

//---------- Réalisation de la classe <LoadAll> (fichier LoadAll.cpp) --

#include "LoadAll.h"

LoadAll::LoadAll (ShapeManager* shapeManager)
: UndoRedoFunction(shapeManager)
{
	ShapesOnHold = shapeManager->TableCopy();
} //----- Fin de Delete

LoadAll::~LoadAll ( )
{
	for(Shape* sh : ShapesOnHold)
		delete sh;
}

void LoadAll::Do()
{
	for(Shape* sh : ShapesOnHold)
		shapeManager->Add(sh->Clone());
}

void LoadAll::Cancel()
{
	for(Shape* sh : ShapesOnHold)
		shapeManager->Delete(sh->GetName());
}


