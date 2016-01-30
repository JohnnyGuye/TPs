#include "PolyIntersect.h"

using namespace std;

PolyIntersect::PolyIntersect(string name, vector<Shape*> shapes)
: ShapeMultiple(name, Shape::INTERSHAPE)
{
	for(Shape* sh : shapes)
		this->shapes.push_back(sh->Clone());
}

PolyIntersect::PolyIntersect(const PolyIntersect& copie)
: ShapeMultiple(name, Shape::INTERSHAPE)
{
	for(Shape* sh : copie.shapes)
		this->shapes.push_back(sh->Clone());
}

PolyIntersect::~PolyIntersect()
{
	for(Shape* sh : shapes)
		delete sh;
}

bool PolyIntersect::IsInShape(Vector2D point) const
{
	point -= offset;
	bool ans = true;
		for(Shape* sh : shapes)
		{
			if(!sh->IsInShape(point))
				ans = false;
		}
	return ans;
}

bool PolyIntersect::IsInShape(int x, int y) const
{
	return IsInShape(Vector2D(x,y));
}

Shape* PolyIntersect::Clone()
{
	return new PolyIntersect(*this);
}