/*************************************************************************
                           LoadAll  -  description
                             -------------------
    début                : 04/12/2015
    copyright            : (C) 2015 par B3403
*************************************************************************/

//---------- Réalisation de la classe <LoadAll> (fichier LoadAll.cpp) --

#include "LoadAllShapes.h"

using namespace std;

LoadAllShapes::LoadAllShapes (ShapeManager* shapeManager, vector<Shape*> shapes)
: UndoRedoFunction(shapeManager)
{
	for(Shape* sh : shapes)
		ShapesOnHold.push_back(sh);
}

LoadAllShapes::~LoadAllShapes ( )
{
	for(Shape* sh : ShapesOnHold)
		delete sh;
}

void LoadAllShapes::Do()
{
	for(Shape* sh : ShapesOnHold)
		shapeManager->Add(sh->Clone());
}

void LoadAllShapes::Cancel()
{
	for(Shape* sh : ShapesOnHold)
		shapeManager->Delete(sh->GetName());
}


