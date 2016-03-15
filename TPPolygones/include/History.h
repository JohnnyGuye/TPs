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

	static int stackindex;

	History();
    virtual ~History ( );

	/**
	* \brief Read inputs and try to do things
	*/
	virtual void Read(std::istream& is = std::cin);

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

    /**
    * @brief Add a shape and its follow in undo/redo
    */
    virtual void Add(Shape* shape);

    /**
	* @brief Load a file in the program
	* @return true if loaded, false otherwise
	**/
	virtual bool Load(std::string const& fileName);

	/**
	* @brief Store all shapes in a file
	* @return true if stored, false otherwise
	**/
	virtual bool Store(std::string const& fileName);

	/**
	* @brief used for recursive course of the file for loading
	* @return the created Shapes
	**/
	virtual std::vector<Shape*> Stack(std::ifstream& is);

protected:

	/** maximum number of undo (or redo) in a row **/
	int const STACK_MAX = 20;

	/** pile undo each action changing the state
	* of the Manager is stored in there and you can cancel it **/
	std::deque<UndoRedoFunction*> undoDeque;

	/** redo the last cancelled action **/
	std::deque<UndoRedoFunction*> redoDeque;

	/** The shape manager **/
	ShapeManager* Manager;
};

#endif // LOADALL
