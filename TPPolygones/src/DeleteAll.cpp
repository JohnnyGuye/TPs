/*************************************************************************
                           Delete  -  description
                             -------------------
    début                : 04/12/2015
    copyright            : (C) 2015 par B3403
*************************************************************************/

//---------- Réalisation de la classe <Delete> (fichier Delete.cpp) --

#include "DeleteAll.h"

DeleteAll::DeleteAll (ShapeManager* shapeManager)
: UndoRedoFunction(shapeManager)
{
	ShapesOnHold = shapeManager->TableCopy();
} //----- Fin de Delete

DeleteAll::~DeleteAll ( )
{
	for(Shape* sh : ShapesOnHold)
		delete sh;
}

void DeleteAll::Do()
{
	shapeManager->Empty();
}

void DeleteAll::Cancel()
{
	for(Shape* sh : ShapesOnHold)
		shapeManager->Add(sh->Clone());
}


