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
	string s = Shape::toString(tab) + " : ";
	switch(shapeType)
	{
		case Shape::REUSHAPE:
			s+="\tunion";
			break;
		case Shape::INTERSHAPE:
			s+="\tintersection";
			break;
		case Shape::NOT_SHAPE:
		default:
			s += "\tshape";
	}
	s += "\toffset : " + offset.toString() + "\r\n";
	for(Shape* sh : shapes)
		s += sh->toString(tab+1) + "\r\n";
	return s;
}

string ShapeMultiple::toStore() const
{
	ostringstream ss;
	ss << Shape::toStore() << endl
		<< "{" << endl;
	for(Shape* sh : shapes)
		ss << sh->toStore();
	ss << "}" << endl;
	return ss.str();
}
