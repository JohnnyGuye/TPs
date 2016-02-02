/*************************************************************************
                           Delete  -  description
                             -------------------
    début                : 04/12/2015
    copyright            : (C) 2015 par B3403
*************************************************************************/

//---------- Réalisation de la classe <Delete> (fichier Delete.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système


//------------------------------------------------------ Include personnel
#include "Delete.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type Delete::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
Create::Delete ( const Delete & anotherDelete )
// Algorithme :
//
{
	shape=anotherDelete.shape;
	shapeManager=anotherDelete.shapeManager;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Delete>" << endl;
#endif
} //----- Fin de Delete (constructeur de copie)



Delete::Delete (Shape theShape, ShapeManager theManager)
// Algorithme :
//
{
	shape = theShape;
	shapeManager=theManager;
#ifdef MAP
    cout << "Appel au constructeur de <Delete>" << endl;
     cout << "pour le shape"<<theShape.GetName()<<endl;
#endif

} //----- Fin de Delete

Delete::~Delete ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Delete>" << endl;
#endif
} //----- Fin de ~Delete

void Delete::Cancel()
{
	shapeManager.Add(*shape);
} // ---- Fin de Cancel

void Delete::Do()
{
	shapeManager.Remove(shape.GetName());
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
