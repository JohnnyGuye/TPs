#include "ShapeMultiple.h"

using namespace std;

ShapeMultiple::ShapeMultiple(string name, int shapeType )
: Shape(name, shapeType)
{
}

ShapeMultiple::ShapeMultiple(const ShapeMultiple& copie)
: Shape(copie)
{
    for(Shape* sh : copie.shapes)
		this->shapes.push_back(sh->Clone());
}
ShapeMultiple::~ShapeMultiple()
{
	for(Shape* sh : shapes)
		delete sh;
}

string ShapeMultiple::toString(int tab) const
{
	string s = Shape::toString() + " is a ";
	string space = "";
	for(int i = 0; i < tab; i++)
		space += " ";
	switch(shapeType)
	{
		case Shape::REUSHAPE:
			s+="complex union form";
			break;
		case Shape::INTERSHAPE:
			s+="complex intersection form";
			break;
		case Shape::NOT_SHAPE:
		default:
			s += "shape";
	}
	s += " using these shapes: \r\n";
	for(Shape* sh : shapes)
		s += space + sh->toString(tab+1) + "\r\n";
	return s;
}
