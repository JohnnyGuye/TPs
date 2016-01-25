#include "Shape.h"

using namespace std;

Shape::Shape(string name, int shapeType )
: name(name), offset(0,0), shapeType(shapeType)
{

}

Shape::~Shape()
{
	//dtor
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

string Shape::toString() const
{
	return name + ": ";
}
