#include "ShapeManager.h"

using namespace std;

bool ShapeManager::Answer(string s, bool isOk)
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
	for(pair<string, Shape*> it : ShapeTable)
		delete it.second;
}

bool ShapeManager::IsInTable(string name)
{
	return ShapeTable.find(name) == ShapeTable.end();
}

Shape* ShapeManager::findShape(string name)
{
	return ShapeTable.find(name)->second;
}


void ShapeManager::List()
{
	Answer("Here you have a list of all the shape loaded in you application", true);
	for(ShapeMap::iterator it = ShapeTable.begin(); ShapeTable.end() != it; it++)
	{
		cout << it->second->toString(0);
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

bool ShapeManager::Delete(string name)
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
	return Answer("Time for a new display of skills !", true);
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

bool ShapeManager::Store(string fileName)
{
	ofstream storeFile(fileName.c_str());
	ifstream ifile(fileName);
	if (ifile.fail())
	{
		return Answer("File already exists");
	}
	if(storeFile)
	{
		/*
		ShapeMap::iterator shapeIt = ShapeTable.begin();
		while(shapeIt != ShapeTable.end())
		{
			Shape* tmp = shapeIt->second;
			string details = "";
			switch(tmp->GetType())
			{
			case Shape::SEGMENT:
				details = "S" + " " + tmp->GetName();
				for(Vector2D vect : tmp->GetPositions)
					details += " " + vect.GetX() + " " + vect.GetY();
			case Shape::RECTANGLE:
				details = "R "+tmp->GetName();
				for(Vector2D vect : tmp->GetPositions())
					details +=" "+vect.GetX()+ " " + vect.GetY();
			case Shape::POLYCONV:
				details = "PC "+tmp->GetName();
				for(Vector2D vect : tmp->GetPositions())
					details += " " + vect.GetX() + " " + vect.GetY();
			case Shape::REUSHAPE:
			case Shape::INTERSHAPE:
			case Shape::NOT_SHAPE:
			}
		}
		*/
	} else
	{
		return Answer("Unable to create file",false);
	}
	return Answer("The shapes are now stored in the file " + fileName,true);
}

bool ShapeManager::Load(string fileName){
	return Answer("The shapes have been copied into the local context",true);
}

