#include "Rectangle.h"

using namespace std;

Rectangle::Rectangle(string name, Vector2D vect1, Vector2D vect2)
: ShapeSingle(name, Shape::RECTANGLE)
{
	points.push_back(vect1);
	points.push_back(vect2);
}

Rectangle::Rectangle(string name, int x1, int y1, int x2, int y2)
: ShapeSingle(name, Shape::RECTANGLE)
{
	points.push_back(Vector2D(x1,y1));
	points.push_back(Vector2D(x2,y2));
}

Rectangle::Rectangle(string name, Rectangle& copie)
{
	this->name = name;
	this->shapeType = Shape::RECTANGLE;
	this->offset = copie.offset;
	for(int i = 0; i < copie.points.size() ; i++)
		this->points.push_back(copie.points[i]);
}

Rectangle::~Rectangle()
{
}

bool Rectangle::IsInShape(int const x, int const y) const
{
	double X = x - offset.GetX();
	double Y = y - offset.GetY();


	if(X > points[1].GetX() || X < points[0].GetX() || Y > points[1].GetY() || Y < points[0].GetY())
		return false;

	return true;
}

bool Rectangle::IsInShape(Vector2D point) const
{
	return IsInShape(point.GetX(), point.GetY());
}
