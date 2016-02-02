#include "History.h"
#include "util.h"
#include "Create.h"
#include "Move.h"
#include "Delete.h"
#include "LoadAll.h"
#include "DeleteAll.h"

using namespace std;

History::History()
{
	Manager = new ShapeManager();
}

History::~History()
{
	delete Manager;
	for(UndoRedoFunction* urf : undoDeque)	delete urf;
	for(UndoRedoFunction* urf : redoDeque)	delete urf;
}

void History::Undo()
{
	if(undoDeque.size() > 0)
	{
		UndoRedoFunction* action = undoDeque.front();
		action->Cancel();
		undoDeque.pop_front();
		redoDeque.push_front(action);
		if(redoDeque.size() > 20)
		{
			delete redoDeque.back();
			redoDeque.pop_back();
		}
	}
}

void History::Redo()
{
	if(redoDeque.size() > 0 )
	{
		UndoRedoFunction* action = redoDeque.front();
		action->Do();
		redoDeque.pop_front();
		undoDeque.push_front(action);
		if(undoDeque.size() > 20)
		{
			delete undoDeque.back();
			undoDeque.pop_back();
		}
	}
}

void History::Do(UndoRedoFunction* urf)
{
    undoDeque.push_front(urf);
    if(undoDeque.size() > 20)
	{
		delete undoDeque.back();
		undoDeque.pop_back();
	}

}

void History::Read()
{
	string line;
	do
	{
		vector<string> tokens;
		getline(cin, line);
		split(line, tokens);

		if(tokens.size() > 0)
		{
			string cmd = tokens[0];

			if(cmd == "S")//SEGMENT
			{
				try
				{
					vector<Vector2D> points;
					if(tokens.size() != 6)	throw exception();

					for(unsigned int i = 2; i < tokens.size(); i+=2)
						points.push_back(Vector2D(my_stoi(tokens[i]),my_stoi(tokens[i+1])));

					Segment* seg = new Segment(tokens[1], points[0], points[1]);
					if(Manager->Add(seg))
						Do(new Create(seg, Manager));
					else
						delete seg;
				}
				catch(exception e)
				{
					Manager->Answer("Invalide syntax. Here is the truth: ");
					cout << "S name x y x' y'";
				}
			}
			else if(cmd == "R")//RECTANGLE
			{
				try
				{
					vector<Vector2D> points;
					if(tokens.size()%2 != 6)	throw exception();

					for(unsigned int i = 2; i < tokens.size(); i+=2)
						points.push_back(Vector2D(my_stoi(tokens[i]),my_stoi(tokens[i+1])));

					Rectangle* rec = new Rectangle(tokens[1], points[0], points[1]);
					if(Manager->Add(rec))
						Do(new Create(rec, Manager));
					else
						delete rec;
				}
				catch(exception e)
				{
					Manager->Answer("Invalide syntax. Here is the truth: ");
					cout << "R name x y x' y'";
				}
			}
			else if(cmd == "PC")
			{
				try
				{
					vector<Vector2D> points;
					if(tokens.size()%2 == 1 || tokens.size() < 8)	throw exception();
					for(unsigned int i = 2; i < tokens.size(); i+=2)
						points.push_back(Vector2D(my_stoi(tokens[i]),my_stoi(tokens[i+1])));

					if(PolyConv::VerifyConvexity(points))
					{
						PolyConv* pc = new PolyConv(tokens[1], points);
						if(Manager->Add(pc))
							Do(new Create (pc, Manager));
						else
							delete pc;
					}
					else
					{
						Manager->Answer("Not a convex polygone :/ If you want to design this, try to unify more single shapes");
					}
				}
				catch(exception e)
				{
					Manager->Answer("Invalide syntax. Here is the truth: ");
					cout << "PC name x0 y0 x1 y1 ... xn yn";
				}
			}
			else if(cmd == "OI")
			{
				try
				{
					vector<string> notInTable;
					for(unsigned int i = 2; i < tokens.size(); i++)
						if(Manager->IsInTable(tokens[i]))
							notInTable.push_back(tokens[i]);

					if(notInTable.size() == 0)
					{
						vector<Shape*> shapes1;
						for(unsigned int i = 2; i < tokens.size(); i++)
							shapes1.push_back(Manager->findShape(tokens[i])->Clone());

						PolyIntersect* pi = new PolyIntersect(tokens[1], shapes1);
						if(Manager->Add(pi))
							Do( new Create(pi, Manager));
						else
							delete pi;

					}
					else
					{
						Manager->Answer("These names are not saved in the app.");
						for(string s : notInTable)
							cout << s << " | " ;
						cout << endl << endl;
					}

				}
				catch(exception e)
				{
					Manager->Answer("Invalid syntax, here lies the truth: ");
					Manager->Answer("OI name name0 name1 ... namen");
				}
			}
			else if(cmd == "OR")
			{
				try
				{
					vector<string> notInTable;
					for(unsigned int i = 2; i < tokens.size(); i++)
						if(Manager->IsInTable(tokens[i]))
							notInTable.push_back(tokens[i]);

					if(notInTable.size() == 0)
					{
						vector<Shape*> shapes1;
						for(unsigned int i = 2; i < tokens.size(); i++)
							shapes1.push_back(Manager->findShape(tokens[i])->Clone());

						PolyUnion* pu = new PolyUnion(tokens[1], shapes1);
						if(Manager->Add(pu))
							Do( new Create(pu, Manager));
						else
							delete pu;

					}
					else
					{
						Manager->Answer("These names are not saved in the app.");
						for(string s : notInTable)
							cout << s << " | " ;
						cout << endl << endl;
					}

				}
				catch(exception e)
				{
					Manager->Answer("Invalid syntax, here lies the truth: ");
					Manager->Answer("OI name name0 name1 ... namen");
				}
			}
			else if(cmd == "DELETE")//BYE BYE SHAPE !
			{
				try
				{
					if(Manager->Delete(tokens[1]))
						Do(new Delete(Manager->findShape(tokens[1])->Clone(), Manager));
				}
				catch(exception e)
				{
					Manager->Answer("Invalide syntax. Here lies the truth: ");
					Manager->Answer("DELETE name");
				}
			}
			else if(cmd == "CLEAR")
			{
				Manager->Empty();
			}
			else if(cmd == "MOVE")//MOVE OFFSET
			{
				try
				{
					if(tokens.size() != 4)	throw exception();
					Vector2D movement = Vector2D(my_stoi(tokens[2]), my_stoi(tokens[3]));

					if(Manager->Move(tokens[1], movement))
						Do(new Move(Manager->findShape(tokens[1])->Clone(), movement, Manager));

				}
				catch(exception e)
				{
					Manager->Answer("Invalide syntax. Here lies the truth: ");
					Manager->Answer("MOVE name dx dy");
				}
			}
			else if(cmd == "HIT")//IS IN SHAPE ?
			{
				try
				{
					string name = tokens[1];
					Vector2D point(my_stoi(tokens[2]),my_stoi(tokens[3]));

					if(!Manager->IsInTable(name))
					{
						Manager->Answer("Sorry, your shape is in another castle");
					}
					else
					{
						if(Manager->findShape(name)->IsInShape(point))
							Manager->Answer("This point isn't in the shape");
						else
							Manager->Answer("The point " + point.toString() + " is in the shape " + name, true);
					}
				}
				catch(exception e)
				{
					Manager->Answer("Invalide syntax. Here lies the truth : ");
					Manager->Answer("HIT name x y");
				}
			}
			else if(cmd == "LIST")// WHAT'S IN MY APP ?
			{
				Manager->List();
			}
			else if(cmd == "UNDO")
			{
				Undo();
			}
			else if(cmd == "REDO")
			{
				Redo();
			}
			else
			{

			}
		}
	}while(line != "EXIT");//GET OUT OF THERE
}
