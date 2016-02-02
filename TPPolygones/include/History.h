/*************************************************************************
                           History.h  -  description
                             -------------------
    début                : 2016.01.22
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

//---------- Interface de la classe <History.h> (fichier History.h) ------
#if ! defined ( LOADALL )
#define LOADALL

//--------------------------------------------------- Interfaces utilisées
#include "UndoRedoFunction.h"

#include "deque"

class History
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	History();
    virtual ~History ( );

    virtual void Do(UndoRedoFunction* urf);

    virtual void Undo();

    virtual void Redo();

	virtual void Read();

protected:

	std::deque<UndoRedoFunction*> undoDeque;
	std::deque<UndoRedoFunction*> redoDeque;
	int const STACK_MAX = 20;
	ShapeManager* Manager;


};

#endif // LOADALL
