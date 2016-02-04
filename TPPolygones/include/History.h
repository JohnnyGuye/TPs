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

	/**
	* \brief Read inputs and try to do things
	*/
	virtual void Read();

protected:
	/**
	* \brief  Add an UndoRedoFunction to the stack
	* \param urf is the UndoRedoFunction object to add
	**/
    virtual void Do(UndoRedoFunction* urf);

	/**
	* \brief Cancel the last action
	*/
    virtual void Undo();

	/**
	* \brief Redo the last cancelled action
	*/
    virtual void Redo();

protected:

	int const STACK_MAX = 20;

	std::deque<UndoRedoFunction*> undoDeque;
	std::deque<UndoRedoFunction*> redoDeque;

	ShapeManager* Manager;


};

#endif // LOADALL
