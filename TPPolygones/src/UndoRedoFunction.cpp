/*************************************************************************
                           Create  -  description
                             -------------------
    début                : 04/12/2015
    copyright            : (C) 2015 par B3403
*************************************************************************/
#include "Create.h"



UndoRedoFunction::UndoRedoFunction (ShapeManager* shapeManager)
: shapeManager(shapeManager)
{
}

UndoRedoFunction::~UndoRedoFunction()
{
	delete shapeManager;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
