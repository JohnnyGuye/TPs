/*************************************************************************
                           Delete  -  description
                             -------------------
    début                : 04/12/2015
    copyright            : (C) 2015 par B3403
*************************************************************************/

//---------- Réalisation de la classe <Delete> (fichier Delete.cpp) --

#include "Move.h"

Move::Move(Shape* shape, Vector2D vect, ShapeManager* shapeManager)
: UndoRedoFunction(shapeManager), shape(shape->Clone()), direction(vect)
{
}

Move::~Move ( )
{
	delete shape;
}

void Move::Do()
{
	shapeManager->Move(shape->GetName(), direction);
}

void Move::Cancel()
{
	shapeManager->Move(shape->GetName(), -direction);
}


