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
: ShapeSingle(copie)
{
	this->shapeType = Shape::SEGMENT;
}

Segment::~Segment()
{
}

Shape* Segment::Clone()
{
	return new Segment(*this);
}

bool Segment::IsInShape(Vector2D P) const
{
	P -= offset;
	Vector2D AB = points[1] - points[0];
	Vector2D AP = P - points[0];

    if(AB.length() < AP.length())
		return false;

	if(AP.IsNull())
		return true;

	AP.normalize();
	AB.normalize();

	if(AB != AP)
		return false;

	return true;
}
