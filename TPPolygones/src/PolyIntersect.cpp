#include "PolyIntersect.h"

using namespace std;

PolyIntersect::PolyIntersect(string name, vector<Shape*> shapes)
: ShapeMultiple(name, Shape::INTERSHAPE)
{
	for(Shape* sh : shapes)
		this->shapes.push_back(sh->Clone());
}

PolyIntersect::PolyIntersect(const PolyIntersect& copie)
: ShapeMultiple(copie)
{
	this->shapeType = copie.shapeType;
}

PolyIntersect::~PolyIntersect()
{
}

bool PolyIntersect::IsInShape(Vector2D point) const
{
	if(shapes.size() == 0)
		return false;
	point -= offset;
	for(Shape* sh : shapes)
	{
		if(!sh->IsInShape(point))
			return false;
	}
	return true;
}

Shape* PolyIntersect::Clone()
{
	return new PolyIntersect(*this);
}
