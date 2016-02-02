/*************************************************************************
                           UndoRedoFunction  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) 2016 par B3434 Lucas Ono & Quentin "Johnny" Guye
*************************************************************************/

#if ! defined ( UNDOREDOFUNCTION )
#define UNDOREDOFUNCTION

class UndoRedoFunction // interface
{

public:
    /**
    * \brief Do the action
    **/
    virtual void do() = 0;

    /**
    * \brief Cancel the action
    */
    virtual void cancel() = 0;
};
#endif // UNDOREDOFUNCTION
