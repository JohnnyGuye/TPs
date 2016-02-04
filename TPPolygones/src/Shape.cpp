#include "Shape.h"

using namespace std;

Shape::Shape(string name, int shapeType )
: name(name), offset(0,0), shapeType(shapeType)
{
}

Shape::Shape(const Shape& copie)
: name(copie.name), offset(copie.offset), shapeType(copie.shapeType)
{
}

Shape::~Shape()
{
}

Vector2D& Shape::Move(Vector2D const vect)
{
	offset+=vect;
	return offset;
}


Vector2D Shape::GetOffset() const
{
	return offset;
}

int Shape::GetType() const
{
	return shapeType;
}

string Shape::GetName() const
{
	return name;
}

string Shape::toString(int tab) const
{
	string s = "";
	for(int i = 0; i < tab; i++)
		s+=" ";
	if(tab >= 0)
		s+="+";
	return s + name;
}
