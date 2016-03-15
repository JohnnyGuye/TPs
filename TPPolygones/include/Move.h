/*************************************************************************
                           Move.h  -  description
                             -------------------
    début                : 2016.01.22
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <Move.h> (fichier ${file_name}) ------
#if ! defined ( MOVE )
#define MOVE

//--------------------------------------------------- Interfaces utilisées
#include "UndoRedoFunction.h"

class Move : public UndoRedoFunction
{
public:
//----------------------------------------------------- Méthodes publiques

    Move(Shape* shape, Vector2D vect, ShapeManager* shapeManager);

    virtual ~Move ( );

    virtual void Do();

    virtual void Cancel();

protected:
//----------------------------------------------------- Attributs protégés
	Shape* shape;
	Vector2D direction;


};

//----------------------------------------- Types dépendants de <Move>

#endif // MOVE
