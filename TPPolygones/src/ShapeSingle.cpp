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
}

vector<Vector2D> ShapeSingle::GetPositions()
{
	vector<Vector2D> thePoints;
	for(Vector2D vect : points)
		thePoints.push_back(vect);
	return thePoints;
}

string ShapeSingle::toString(int tab) const
{
	string s = Shape::toString(tab) + " : ";
	string space = "";
	for(int i = 0; i < tab; i++)
		space += " ";
	switch(shapeType)
	{
		case Shape::RECTANGLE:
			s+="\trectangle";
			break;
		case Shape::POLYCONV:
			s+="\tconvex polygon";
			break;
		case Shape::SEGMENT:
			s+="\tsegment";
			break;
		case Shape::NOT_SHAPE:
		default:
			s += "\tshape";
	}
	s += "\toffset : " + offset.toString() + "\r\n";
	for(Vector2D vect : points)
		s += space + "| " + vect.toString() + "\r\n";
	return s;
}

string ShapeSingle::toStore() const
{
	ostringstream ss;
	ss << Shape::toStore();
	for(Vector2D point : points)
		ss << point.GetX() << " " << point.GetY() << " ";
	return ss.str() + "\r\n";
}
