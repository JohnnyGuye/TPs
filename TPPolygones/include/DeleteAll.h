/*************************************************************************
                           DeleteAll.h  -  description
                             -------------------
    début                : 2016.01.22
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <DeleteAll.h> (fichier DeleteAll.h) ------
#if ! defined ( DELETEALL_H )
#define DELETEALL_H

#include "UndoRedoFunction.h"
#include <vector>


class DeleteAll : public UndoRedoFunction
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    DeleteAll (ShapeManager* shapeManager = nullptr);

    virtual ~DeleteAll ( );

    /** Delete all the shapes **/
    virtual void Do();

    /** Restore all the shapes **/
    virtual void Cancel();


protected:
	std::vector<Shape*> ShapesOnHold;


};

//----------------------------------------- Types dépendants de <DeleteAll>

#endif // DELETEALL_H
