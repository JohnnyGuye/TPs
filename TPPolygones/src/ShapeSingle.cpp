#include "ShapeSingle.h"

using namespace std;

ShapeSingle::ShapeSingle(string name, int shapeType)
: Shape(name, shapeType)
{}

ShapeSingle::ShapeSingle(const ShapeSingle& copie)
: Shape(copie)
{
	for(Vector2D point : copie.points)
		points.push_back(point);
}

ShapeSingle::~ShapeSingle()
{
	//dtor
}

string ShapeSingle::toString(int tab) const
{
	string s = Shape::toString(tab) + " is a ";
	string space = "";
	for(int i = 0; i < tab; i++)
		space += " ";
	switch(shapeType)
	{
		case Shape::RECTANGLE:
			s+="rectangle";
			break;
		case Shape::POLYCONV:
			s+="convex polygon";
			break;
		case Shape::SEGMENT:
			s+="segment";
			break;
		case Shape::NOT_SHAPE:
		default:
			s += "shape";
	}
	s += " using these points: \r\n";
	for(Vector2D vect : points)
		s += space + "|" + vect.toString() + "\r\n";
	return s;
}
