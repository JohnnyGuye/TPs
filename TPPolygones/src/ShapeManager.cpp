#include "ShapeManager.h"

using namespace std;

void split(string str, vector<string>& tokens)
{
    istringstream iss(str);
	tokens.clear();
	//int i = 0;
    do
    {
        string sub;
        iss >> sub;
		if(sub != "")
		{
			tokens.push_back(sub);
		}
    } while (iss);
}

int my_stoi(string str)
{
	int ans = 0;
	int fact = 1;
	if(str.at(0) == '-')
	{
		fact = -1;
		str = str.substr(1);
	}

	for(char c : str)
	{
		if(c < '0' || c > '9')
			break;
		ans = 10 * ans + (c - '0');
	}
	return fact * ans;
}

bool ShapeManager::Answer(string s, bool isOk)
{
	cout << (isOk ? "R: OK" : "R: ERR") << endl;
	cout << "R: #" << s << endl << endl;
	return isOk;
}

ShapeManager::ShapeManager()
{

}

ShapeManager::~ShapeManager()
{
	for(pair<string, Shape*> it : ShapeTable)
		delete it.second;
}

bool ShapeManager::Add(Shape* shape)
{
	if(shape->GetType() == Shape::NOT_SHAPE)
		return Answer("This shape is not valid");
	else if(ShapeTable.find(shape->GetName()) != ShapeTable.end())
		return Answer("This name already exists");
	else
	{
		ShapeTable.insert(pair<string,Shape*>(shape->GetName(), shape));
		return Answer("New baby called " + shape->GetName() + " is born !", true);
	}
}

bool ShapeManager::Delete(string name)
{
	ShapeMap::iterator shapeIt = ShapeTable.find(name);
	if(shapeIt == ShapeTable.end())
		return Answer("This name is not attributed");
	else
	{
		delete shapeIt->second;
		ShapeTable.erase(name);
		return Answer("The shape " + name + " has been successfully deleted"), true;
	}
}

bool ShapeManager::Empty()
{

	for(ShapeMap::iterator it = ShapeTable.begin(); it != ShapeTable.end() ; it++)
	{
		delete it->second;
	}
	ShapeTable.clear();
	return Answer("Time for a new display of skills !", true);
}

bool ShapeManager::Move(string name, Vector2D delta)
{
	ShapeMap::iterator shapeit = ShapeTable.find(name);
	if(shapeit == ShapeTable.end())
		return Answer("Sorry, your shape is in another castle");
	Vector2D offsetOld = shapeit->second->GetOffset();
	Vector2D offsetNew = (shapeit->second->Move(delta));
	return Answer(name + " has been moved from " + offsetOld.toString() + " to " + offsetNew.toString(), true );
}

void ShapeManager::Read()
{
	string line = "";

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
					for(int i = 2; i < tokens.size(); i+=2)
						points.push_back(Vector2D(my_stoi(tokens[i]),my_stoi(tokens[i+1])));

					Segment* seg = new Segment(tokens[1], points[0], points[1]);
					if(!Add(seg))	delete seg;
				}
				catch(exception e)
				{
					Answer("Invalide syntax. Here is the truth: ");
					Answer("S name x y x' y'");
				}
			}
			else if(cmd == "R")//RECTANGLE
			{
				try
				{
					vector<Vector2D> points;
					for(int i = 2; i < tokens.size(); i+=2)
						points.push_back(Vector2D(my_stoi(tokens[i]),my_stoi(tokens[i+1])));

					Rectangle* rec = new Rectangle(tokens[1], points[0], points[1]);
					if(!Add(rec))	delete rec;
				}
				catch(exception e)
				{
					Answer("Invalide syntax. Here is the truth: ");
					Answer("R name x y x' y'");
				}
			}
			else if(cmd == "PC")
			{
				try
				{
					vector<Vector2D> points;
					for(int i = 2; i < tokens.size(); i+=2)
						points.push_back(Vector2D(my_stoi(tokens[i]),my_stoi(tokens[i+1])));

					if(PolyConv::VerifyConvexity(points))
					{
						PolyConv* pc = new PolyConv(tokens[1], points);
						if(!Add(pc))	delete pc;
					}
					else
					{
						Answer("Not a convex polygone :/ If you want to design this, try to unify more single shapes");
					}
				}
				catch(exception e)
				{
					Answer("Invalide syntax. Here is the truth: ");
					Answer("PC name x0 y0 x1 y1 ... xn yn");
				}
			}
			else if(cmd == "OI")
			{
				try
				{
					vector<string> notInTable;
					for(unsigned int i = 2; i < tokens.size(); i++)
						if(ShapeTable.find(tokens[i]) == ShapeTable.end())
						{
							notInTable.push_back(tokens[i]);
						}

					if(notInTable.size() == 0)
					{
						vector<Shape*> shapes1;
						for(unsigned int i = 2; i < tokens.size(); i++)
						{
							Shape* sh = ShapeTable.find(tokens[i])->second;
							shapes1.push_back(sh->Clone());
						}
						PolyIntersect* pi = new PolyIntersect(tokens[1], shapes1);
						if(!Add(pi))	delete pi;

					}
					else
					{
						Answer("These names are not saved in the app.");
						for(string s : notInTable)
							cout << s << " | " ;
						cout << endl << endl;
					}

				}
				catch(exception e)
				{
					Answer("Invalid syntax, here lies the truth: ");
					Answer("OI name name0 name1 ... namen");
				}
			}
			else if(cmd == "OR")
			{
				try
				{
					vector<string> notInTable;
					for(unsigned int i = 2; i < tokens.size(); i++)
						if(ShapeTable.find(tokens[i]) == ShapeTable.end())
						{
							notInTable.push_back(tokens[i]);
						}

					if(notInTable.size() == 0)
					{
						vector<Shape*> shapes1;
						for(unsigned int i = 2; i < tokens.size(); i++)
						{
							Shape* sh = ShapeTable.find(tokens[i])->second;
							shapes1.push_back(sh->Clone());
						}
						PolyUnion* pu = new PolyUnion(tokens[1], shapes1);
						if(!Add(pu))	delete pu;

					}
					else
					{
						Answer("These names are not saved in the app.");
						cout << "R: #";
						for(string s : notInTable)
							cout << s << " | " ;
						cout << endl;
					}

				}
				catch(exception e)
				{
					Answer("Invalid syntax, here lies the truth: ");
					Answer("OR name name0 name1 ... namen");
				}
			}
			else if(cmd == "DELETE")//BYE BYE SHAPE !
			{
				try
				{
					Delete(tokens[1]);
				}
				catch(exception e)
				{
					Answer("Invalide syntax. Here lies the truth: ");
					Answer("DELETE name");
				}
			}
			else if(cmd == "CLEAR")
			{
				Empty();
			}
			else if(cmd == "MOVE")//MOVE OFFSET
			{
				try
				{
					Vector2D delta(5,5);
					Move(tokens[1], delta);
				}
				catch(exception e)
				{
					Answer("Invalide syntax. Here lies the truth: ");
					Answer("MOVE name dx dy");
				}
			}
			else if(cmd == "HIT")//IS IN SHAPE ?
			{
				try
				{
					string name = tokens[1];
					Vector2D point(my_stoi(tokens[2]),my_stoi(tokens[3]));

					ShapeMap::iterator shapeit = ShapeTable.find(name);
					if(shapeit == ShapeTable.end())
					{
						Answer("Sorry, your shape is in another castle");
					}
					else
					{
						if(!shapeit->second->IsInShape(point))
							Answer("This point isn't in the shape");
						else
							Answer("The point " + point.toString() + " is in the shape " + name, true);
					}
				}
				catch(exception e)
				{
					Answer("Invalide syntax. Here lies the truth : ");
					Answer("HIT name x y");
				}
			}
			else if(cmd == "LIST")// WHAT'S IN MY APP ?
			{
				Answer("Here you have a list of all the shape loaded in you application", true);
				for(ShapeMap::iterator it = ShapeTable.begin(); ShapeTable.end() != it; it++)
				{
					cout << it->second->toString(0);
				}
			}
			else
			{

			}
		}
	}while(line != "EXIT");//GET OUT OF THERE
}
