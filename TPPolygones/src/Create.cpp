/*************************************************************************
                           Create  -  description
                             -------------------
    début                : 04/12/2015
    copyright            : (C) 2015 par B3403
*************************************************************************/
#include "Create.h"



Create::Create (Shape* shape, ShapeManager* shapeManager)
: UndoRedoFunction(shapeManager), shape(shape->Clone())
{

}

void Create::Do()
{
	shapeManager->Add(shape);
}

void Create::Cancel()
{
	shapeManager->Delete(shape->GetName());
}

Create::~Create()
{
	delete shape;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
