#include "Segment.h"

using namespace std;

Segment::Segment(string name, Vector2D vect1, Vector2D vect2)
: ShapeSingle(name, Shape::SEGMENT)
{
	points.push_back(vect1);
	points.push_back(vect2);
}

Segment::Segment(string name, int x1, int y1, int x2, int y2)
: ShapeSingle(name, Shape::SEGMENT)
{
	points.push_back(Vector2D(x1,y1));
	points.push_back(Vector2D(x2,y2));
}

Segment::Segment(const Segment& copie)
{
	this->name = name;
	this->shapeType = Shape::SEGMENT;
	this->offset = copie.offset;
	for(int i = 0; i < copie.points.size() ; i++)
		this->points.push_back(copie.points[i]);
}

Segment::~Segment()
{
}

Shape* Segment::Clone()
{
	return new Segment(*this);
}
bool Segment::IsInShape(int const x, int const y) const
{
	Vector2D vect1 = Vector2D(x - offset.GetX(), y - offset.GetY());
	Vector2D seg = Vector2D(points[1].GetX() - points[0].GetX(), points[1].GetY() - points[0].GetY());

	if(seg.length() < vect1.length())
	{
		cerr << "Too far !";
		return false;
	}

	if(vect1.GetX() * seg.GetX() >= 0 && vect1.GetY() * seg.GetY() > 0 )
	{
		cerr << "Wrong direction !";
		return false;
	}


	seg.normalize();
	vect1.normalize();

	if(abs(seg.scalarProduct(vect1) - (seg.GetX() *seg.GetX() + seg.GetY() * seg.GetY())) > 0.01)
	{
		cerr << "Not colinear !";
		return false;
	}



	return true;
}

bool Segment::IsInShape(Vector2D point) const
{
	return IsInShape(point.GetX(), point.GetY());
}
