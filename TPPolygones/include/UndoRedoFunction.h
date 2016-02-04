/*************************************************************************
                           UndoRedoFunction  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

#if ! defined ( UNDOREDOFUNCTION )
#define UNDOREDOFUNCTION

#include "ShapeManager.h"

class UndoRedoFunction // interface
{

public:

    /** @brief create a UndoRedoFunction
    * @param shapeManager a pointer on the shapeManager on wich you want to do actions
    **/
    UndoRedoFunction(ShapeManager* shapeManager = NULL);

    /**
    * \brief Do the action
    **/
    virtual void Do() = 0;


    /**
    * \brief Cancel the action
    */
    virtual void Cancel() = 0;

    virtual ~UndoRedoFunction();

protected:
    ShapeManager* shapeManager;
};
#endif // UNDOREDOFUNCTION
