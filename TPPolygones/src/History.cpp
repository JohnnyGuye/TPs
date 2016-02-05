#include "History.h"
#include "util.h"
#include "Create.h"
#include "Move.h"
#include "Delete.h"
#include "LoadAllShapes.h"
#include "DeleteAll.h"

using namespace std;

int History::stackindex = 0;

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

void History::Read(istream& is)
{
	string line;
	do
	{
		vector<string> tokens;
		getline(is, line);
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
					if(tokens.size() != 6)	throw exception();

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
						if(!Manager->IsInTable(tokens[i]))
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
						if(!Manager->IsInTable(tokens[i]))
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
					if(Manager->IsInTable(tokens[1]))
					{
						Do(new Delete(Manager->findShape(tokens[1])->Clone(), Manager));
						Manager->Delete(tokens[1]);
					}
				}
				catch(exception e)
				{
					Manager->Answer("Invalide syntax. Here lies the truth: ");
					Manager->Answer("DELETE name");
				}
			}
			else if(cmd == "CLEAR")
			{
				Do(new DeleteAll(Manager));
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
					if(tokens.size() != 4)	throw exception();
					string name = tokens[1];
					Vector2D point(my_stoi(tokens[2]),my_stoi(tokens[3]));

					Manager->Hit(name, point);
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
			else if(cmd == "LOAD")
			{
				try
				{
					if(tokens.size() != 2)	throw exception();
					Load(tokens[1]);
				}
				catch(exception e)
				{
					Manager->Answer("Invalid syntax.");
				}
			}
			else if(cmd == "STORE")
			{
				try
				{
					if(tokens.size() != 2)	throw exception();
					Store(tokens[1]);
				}
				catch(exception e)
				{
					Manager->Answer("Invalid syntax.");
				}
			}
			else if(cmd != "EXIT")
			{
				cout << "New into this ? Here is the help : " << endl;
				cout << " - EXIT : end the program" << endl
					<< " - S [name] x y x' y' : create a segment beginning in x,y ending in x',y' " << endl
					<< " - R [name] x y x' y' : create a rectangle with top left corner x,y  end bottom right corner  in x',y' " << endl
					<< " - PC [name] x0 y0 x1 y1 ... xn yn : create a convex polygon with the following points " << endl
					<< " - OR [name] <name0> <name1> ... <namen> : create an union of these shapes" << endl
					<< " - OI [name] <name0> <name1> ... <namen> : create an intersection of these shapes" << endl
					<< " - LIST : list the shapes storred" << endl
					<< " - CLEAR : clear all shapes" << endl
					<< " - LOAD <fileName> : load shapes from a file" << endl
					<< " - SAVE <fileName> : store all shapes in a file" << endl
					<< " - DELETE <name> : delete a shape " << endl
					<< " - UNDO/REDO : rewind or forward in timeline of program (20 actions max)" << endl
					<< " - HIT [name] x y : verify if the point is in the shape " << endl
					<< endl;
			}
		}
	}while(line != "EXIT");//GET OUT OF THERE
}

vector<Shape*> History::Stack(ifstream& is)
{

	vector<Shape*> shapes;
	vector<string> tokens;
	string line;

	while(getline(is, line))
	{
		split(line, tokens);
		if(tokens.size() == 0 || tokens[0] == "}")	break;

		if(tokens.size() >= 4)
		{
			try
			{
				string 		name = tokens[0];
				int 		type = my_stoi(tokens[1]);
				Vector2D 	offset(my_stoi(tokens[2]), my_stoi(tokens[3]));

				if(type == Shape::SEGMENT || type == Shape::RECTANGLE)
				{
					if(tokens.size() != 8) throw exception();

					Vector2D A(my_stoi(tokens[4]), my_stoi(tokens[5]));
					Vector2D B(my_stoi(tokens[6]), my_stoi(tokens[7]));

					if(type == Shape::SEGMENT)	shapes.push_back(new Segment(name, A, B));
					if(type == Shape::RECTANGLE)	shapes.push_back(new Rectangle(name, A, B));
				}
				else if(type == Shape::POLYCONV)
				{
					if(tokens.size() < 8 || tokens.size()%2 == 1) throw exception();

					vector<Vector2D> points;
					for(unsigned i = 4; i < tokens.size(); i+=2)
						points.push_back(Vector2D(my_stoi(tokens[i]), my_stoi(tokens[i+1])));
					shapes.push_back(new PolyConv(name, points));
				}
				else if(type == Shape::REUSHAPE)
				{
					shapes.push_back(new PolyUnion(name, Stack(is)));
				}
				else if(type == Shape::INTERSHAPE)
				{
					shapes.push_back(new PolyIntersect(name, Stack(is)));
				}
				shapes.back()->Move(offset);
			}
			catch (exception e)
			{
				return shapes;
			}
		}
	}
	return shapes;
}

bool History::Load(string const& fileName)
{
	ifstream iFile("saves/"+fileName);
	if (iFile.fail())
	{
		return Manager->Answer("File do not exists");
	}

	if(iFile)
	{
		vector<Shape*> shapes = Stack(iFile);

		UndoRedoFunction* urf = new LoadAllShapes(Manager, shapes);
		urf->Do();
		Do(urf);

		return Manager->Answer("All shapes from " + fileName + " have been loaded", true);
	}
	return Manager->Answer("Enable to open the file");

}

bool History::Store(string const& fileName)
{

	ifstream ifile("saves/"+fileName);
	if (ifile.good())
	{
		return Manager->Answer("File already exists");
	}

	ofstream storeFile("saves/"+fileName);

	if(storeFile)
	{
		for(Shape* shape : Manager->TableCopy())
			storeFile << shape->toStore();
		return Manager->Answer("All shapes have been stored in "+ fileName, true);
	}
	return Manager->Answer("Not writable");
}
