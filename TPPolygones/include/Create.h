/*************************************************************************
                           Create  -  description
                             -------------------
    début                : 2016.01.22
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <Create> (fichier Create.h) ------
#if ! defined ( CREATE )
#define CREATE

#include "Shape.h"
#include "UndoRedoFunction.h"


class Create: public UndoRedoFunction
{
//----------------------------------------------------------------- PUBLIC

public:

	Create ( Shape* shape = nullptr, ShapeManager* shapeManager = nullptr);

    virtual ~Create ( );

    virtual void Do();

    virtual void Cancel();

protected:
//----------------------------------------------------- Attributs protégés

Shape* shape;


};

//----------------------------------------- Types dépendants de <Create>

#endif // CREATE
