/*************************************************************************
                           Delete  -  description
                             -------------------
    début                : 04/12/2015
    copyright            : (C) 2015 par B3403
*************************************************************************/

//---------- Réalisation de la classe <Delete> (fichier Delete.cpp) --

#include "Delete.h"

Delete::Delete (Shape* shape, ShapeManager* shapeManager)
: UndoRedoFunction(shapeManager), shape(shape->Clone())
{
} //----- Fin de Delete

Delete::~Delete ( )
{
	delete shape;
}

void Delete::Do()
{
	shapeManager->Delete(shape->GetName());
}

void Delete::Cancel()
{
	shapeManager->Add(shape->Clone());
}


