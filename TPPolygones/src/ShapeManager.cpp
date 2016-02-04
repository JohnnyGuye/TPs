#include "ShapeManager.h"

using namespace std;

bool ShapeManager::Answer(string const& s, bool const& isOk)
{
	cout << (isOk ? "OK" : "ERR") << endl;
	cout << "#" << s << endl << endl;
	return isOk;
}

ShapeManager::ShapeManager()
{

}

ShapeManager::~ShapeManager()
{
	Empty();
}

bool ShapeManager::IsInTable(string const& name)
{
	return ShapeTable.find(name) != ShapeTable.end();
}

Shape* ShapeManager::findShape(string const& name)
{
	return ShapeTable.find(name)->second;
}

void ShapeManager::List()
{
	if(ShapeTable.begin() != ShapeTable.end())
	{
		Answer("Here you have a list of all the shape loaded in you application", true);
		for(ShapeMap::iterator it = ShapeTable.begin(); ShapeTable.end() != it; it++)
		{
			cout << it->second->toString(0);
		}
	}
	else
	{
		Answer("Nothing to display :/");
	}
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

bool ShapeManager::Delete(string const& name)
{
	ShapeMap::iterator shapeIt = ShapeTable.find(name);
	if(shapeIt == ShapeTable.end())
		return Answer("This name is not attributed");
	else
	{
		delete shapeIt->second;
		ShapeTable.erase(name);
		return Answer("The shape " + name + " has been successfully deleted", true);
	}
}

bool ShapeManager::Empty()
{

	for(ShapeMap::iterator it = ShapeTable.begin(); it != ShapeTable.end() ; it++)
	{
		delete it->second;
	}
	ShapeTable.clear();
	return Answer("Cleared !", true);
}

bool ShapeManager::Move(string const& name, Vector2D const& delta)
{
	ShapeMap::iterator shapeit = ShapeTable.find(name);
	if(shapeit == ShapeTable.end())
		return Answer("Sorry, your shape is in another castle");
	else
	{
		Vector2D offsetOld = shapeit->second->GetOffset();
		Vector2D offsetNew = (shapeit->second->Move(delta));
		return Answer(name + " has been moved from " + offsetOld.toString() + " to " + offsetNew.toString(), true );
	}
}

bool ShapeManager::Hit(std::string const& name, Vector2D const& point)
{
	if(!IsInTable(name))
	{
		return Answer("Sorry, your shape is in another castle");
	}
	else
	{
		if(!findShape(name)->IsInShape(point))
		{
			cout << "NO" << endl;
			return false;
		}
		else
		{
			cout << "YES" << endl;
			return true;
		}
	}
}

vector<Shape*> ShapeManager::TableCopy()
{
	vector<Shape*> tC;
	for(ShapeMap::iterator it = ShapeTable.begin(); ShapeTable.end() != it; it++)
		tC.push_back(it->second->Clone());
	return tC;

}

bool ShapeManager::Store(string const& fileName)
{
	ofstream storeFile(fileName.c_str());
	ifstream ifile(fileName);
	if (ifile.good())
	{
		return Answer("File already exists");
	}
	if(storeFile)
	{
		ShapeMap::iterator shapeIt = ShapeTable.begin();
		string compose="";
		while(shapeIt != ShapeTable.end())
		{
			Shape* tmp = shapeIt->second;
			string details = "";
			switch(tmp->GetType())
			{
			case Shape::SEGMENT:
				details=tmp->GetPersistence();
				break;
			case Shape::RECTANGLE:
				details=tmp->GetPersistence();
				break;
			case Shape::POLYCONV:
                details=tmp->GetPersistence();
                break;
			case Shape::REUSHAPE:
			    compose+=tmp->GetPersistence()+"\r\n";
			    break;
			case Shape::INTERSHAPE:
			    compose+=tmp->GetPersistence()+"\r\n";
			    break;
			case Shape::NOT_SHAPE:
			    break;
			}
			storeFile<<details<<"\r\n";
		}
		storeFile<<compose;
	} else
	{
		return Answer("Unable to create file",false);
	}
	return Answer("The shapes are now stored in the file " + fileName,true);
}
//il faut envoyer shapesAdded a un LoadAll et l'ajouter dans History
bool ShapeManager::Load(string fileName){
    std::ifstream loadFile(fileName.c_str());
    if(loadFile.fail())
    {
        return Answer("File does not exist",false);
    }
    string line;
    vector<string> tokens;
    vector<Shape *> shapesAdded;
    vector<string> retry;
	while(getline(loadFile, line))
    {

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
                    if(Add(seg))
                        shapesAdded.push_back(seg);
                    else
                        delete seg;
                }
                catch(exception e)
                {
                    Answer("Invalide syntax. Here is the truth: ");
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
                    if(Add(rec))
                        shapesAdded.push_back(rec);
                    else
                        delete rec;
                }
                catch(exception e)
                {
                    Answer("Invalide syntax. Here is the truth: ");
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
                        if(Add(pc))
                            shapesAdded.push_back(pc);
                        else
                            delete pc;
                    }
                    else
                    {
                        Answer("Not a convex polygone :/ If you want to design this, try to unify more single shapes");
                    }
                }
                catch(exception e)
                {
                    Answer("Invalide syntax. Here is the truth: ");
                    cout << "PC name x0 y0 x1 y1 ... xn yn";
                }
            }
            else if(cmd == "OI")
            {
                try
                {
                    vector<string> notInTable;
                    for(unsigned int i = 2; i < tokens.size(); i++)
                        if(IsInTable(tokens[i]))
                            notInTable.push_back(tokens[i]);

                    if(notInTable.size() == 0)
                    {
                        vector<Shape*> shapes1;
                        for(unsigned int i = 2; i < tokens.size(); i++)
                            shapes1.push_back(findShape(tokens[i])->Clone());

                        PolyIntersect* pi = new PolyIntersect(tokens[1], shapes1);
                        if(Add(pi))
                            shapesAdded.push_back(pi);
                        else
                            delete pi;

                    }
                    else
                    {
                        retry.push_back(line);
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
                        if(IsInTable(tokens[i]))
                            notInTable.push_back(tokens[i]);

                    if(notInTable.size() == 0)
                    {
                        vector<Shape*> shapes1;
                        for(unsigned int i = 2; i < tokens.size(); i++)
                            shapes1.push_back(findShape(tokens[i])->Clone());

                        PolyUnion* pu = new PolyUnion(tokens[1], shapes1);
                        if(Add(pu))
                           shapesAdded.push_back(pu);
                        else
                            delete pu;

                    }
                    else
                    {
                        retry.push_back(line);
                    }

                }
                catch(exception e)
                {
                    Answer("Invalid syntax, here lies the truth: ");
                    Answer("OI name name0 name1 ... namen");
                }
            }
        }
    }
    bool proceed = retry.size()!=0;
    while(proceed)
    {
        proceed=false;
        for(string command:retry)
        {
             split(command, tokens);
             string cmd = tokens[0];
             if(cmd == "OI")
            {
                try
                {
                    vector<string> notInTable;
                    for(unsigned int i = 2; i < tokens.size(); i++)
                        if(IsInTable(tokens[i]))
                            notInTable.push_back(tokens[i]);

                    if(notInTable.size() == 0)
                    {
                        vector<Shape*> shapes1;
                        for(unsigned int i = 2; i < tokens.size(); i++)
                            shapes1.push_back(findShape(tokens[i])->Clone());

                        PolyIntersect* pi = new PolyIntersect(tokens[1], shapes1);
                        if(Add(pi))
                        {
                            shapesAdded.push_back(pi);
                            proceed=true;
                        }
                        else
                            delete pi;

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
                        if(IsInTable(tokens[i]))
                            notInTable.push_back(tokens[i]);

                    if(notInTable.size() == 0)
                    {
                        vector<Shape*> shapes1;
                        for(unsigned int i = 2; i < tokens.size(); i++)
                            shapes1.push_back(findShape(tokens[i])->Clone());

                        PolyUnion* pu = new PolyUnion(tokens[1], shapes1);
                        if(Add(pu))
                        {
                           shapesAdded.push_back(pu);
                           proceed=true;
                        }
                        else
                            delete pu;

                    }

                }
                catch(exception e)
                {
                    Answer("Invalid syntax, here lies the truth: ");
                    Answer("OI name name0 name1 ... namen");
                }
            }
        }
    }
    if(retry.size()!=0){
        return Answer("Error loading shapes");
    }
	return Answer("The shapes have been copied into the local context",true);
}
