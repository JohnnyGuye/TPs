/*************************************************************************
                           Create  -  description
                             -------------------
    début                : 04/12/2015
    copyright            : (C) 2015 par B3403
*************************************************************************/

//---------- Réalisation de la classe <Create> (fichier Create.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système


//------------------------------------------------------ Include personnel
#include "Create.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type Create::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
Create::Create ( const Create & anotherCreate )
// Algorithme :
//
{
	shape=anotherCreate.shape;
	shapeManager=anotherCreate.shapeManager;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Create>" << endl;
#endif
} //----- Fin de Create (constructeur de copie)



Create::Create (Shape theShape, ShapeManager theManager)
// Algorithme :
//
{
	shape = theShape;
	shapeManager=theManager;
#ifdef MAP
    cout << "Appel au constructeur de <Create>" << endl;
     cout << "pour le shape"<<theShape.GetName()<<endl;
#endif

} //----- Fin de Create

Create::~Create ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Create>" << endl;
#endif
} //----- Fin de ~Create

void Create::Do()
{
	shapeManager.Add(*shape);
} // ---- Fin de do

void Create::Cancel()
{
	shapeManager.Remove(shape.GetName());
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
