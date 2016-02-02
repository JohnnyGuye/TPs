#include "PolyUnion.h"

using namespace std;

PolyUnion::PolyUnion(string name, vector<Shape*> shapes)
: ShapeMultiple(name, Shape::REUSHAPE)
{
	for(Shape* sh : shapes)
		this->shapes.push_back(sh->Clone());
}

PolyUnion::PolyUnion(const PolyUnion& copie)
: ShapeMultiple(copie)
{
	this->shapeType = copie.shapeType;
}

PolyUnion::~PolyUnion()
{
}

bool PolyUnion::IsInShape(Vector2D point) const
{
	point -= offset;
	for(Shape* sh : shapes)
	{
		if(sh->IsInShape(point))
			return true;
	}
	return false;
}

bool PolyUnion::IsInShape(int x, int y) const
{
	return IsInShape(Vector2D(x,y));
}

Shape* PolyUnion::Clone()
{
	return new PolyUnion(*this);
}
