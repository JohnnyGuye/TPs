/*************************************************************************
                           Delete  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <Delete> (fichier Delete.h) ------
#if ! defined ( DELETE )
#define DELETE

#include "UndoRedoFunction.h"

class Delete : public UndoRedoFunction
{

public:

    Delete ( Shape* shape = nullptr, ShapeManager* shapeManager = nullptr);

    virtual ~Delete ( );

    virtual void Do();

    virtual void Cancel();

protected:

Shape* shape;

};

//----------------------------------------- Types dépendants de <Delete>

#endif // DELETE
