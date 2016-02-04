#include "Rectangle.h"

using namespace std;

Rectangle::Rectangle(string name, Vector2D vect1, Vector2D vect2)
: ShapeSingle(name, Shape::RECTANGLE)
{

	Vector2D A = Vector2D(min(vect1.GetX(), vect2.GetX()), min(vect1.GetY(), vect2.GetY()));
	Vector2D B = Vector2D(max(vect1.GetX(), vect2.GetX()), max(vect1.GetY(), vect2.GetY()));

	points.push_back(A);
	points.push_back(B);
}

Rectangle::Rectangle(string name, int x1, int y1, int x2, int y2)
: ShapeSingle(name, Shape::RECTANGLE)
{
	Vector2D A = Vector2D(min(x1, x2), min(y1, y2));
	Vector2D B = Vector2D(max(x1, x2), max(y1, y2));

	points.push_back(A);
	points.push_back(B);
}

Rectangle::Rectangle(const Rectangle& copie)
: ShapeSingle(copie)
{
	this->shapeType = Shape::RECTANGLE;
}

Shape* Rectangle::Clone()
{
	return new Rectangle(*this);
}
Rectangle::~Rectangle()
{
}

bool Rectangle::IsInShape(Vector2D P) const
{
	P -= offset;

	if(P.GetX() > points[1].GetX() || P.GetX() < points[0].GetX() || P.GetY() > points[1].GetY() || P.GetY() < points[0].GetY())
		return false;

	return true;
}
