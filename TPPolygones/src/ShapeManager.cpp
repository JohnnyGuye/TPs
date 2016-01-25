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
		if(sub != ""){

			tokens.push_back(sub);
			//cout << tokens[i] << "|(" << i << ")|";
			//i++;
		}

    } while (iss);
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
		string cmd = tokens[0];

		if(cmd == "S")
		{
			try
			{
				std::string::size_type sz;
				Vector2D A(0,0);
				Vector2D B(1,1);

				Segment* seg = new Segment(tokens[1], A, B);
				if(!Add(seg))	delete seg;
			}
			catch(exception e)
			{
				Answer("Invalide syntax. Here is the truth : ");
				Answer("S name x y x' y'");
			}
		}
		else if(cmd == "R")
		{
			try
			{
				std::string::size_type sz;
				Vector2D A(0,0);
				Vector2D B(1,1);

				Rectangle* rec = new Rectangle(tokens[1], A, B);
				if(!Add(rec))	delete rec;
			}
			catch(exception e)
			{
				Answer("Invalide syntax. Here is the truth : ");
				Answer("R name x y x' y'");
			}
		}
		else if(cmd == "MOVE")
		{
			try
			{
				Vector2D delta(5,5);
				Move(tokens[1], delta);
			}
			catch(exception e)
			{
				Answer("Invalide syntax. Here lies the truth : ");
				Answer("MOVE name dx dy");
			}
		}
		else if(cmd == "HIT")
		{
			try
			{
				Vector2D point(0,0);
				string name = tokens[1];
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
	}while(line != "EXIT");
}
