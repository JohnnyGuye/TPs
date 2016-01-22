#include "Shape.h"

Shape::Shape()
{
	//ctor
}

Shape::~Shape()
{
	//dtor
}

void Shape::Move(Vector2D const vect)
{
	offset+=vect;
}

bool Shape::IsInShape(int const x, int const y)
{
	return false;
}

bool Shape::IsInShape(Vector2D point)
{
	return IsInShape(point.GetX(), point.GetY());
}
