#include "PolyConv.h"

using namespace std;

bool VerifyConvexity(vector<Vector2D*> points)
{
		return true;
}

PolyConv::PolyConv(string name, Vector2D vect1, Vector2D vect2)
: ShapeSingle(name, Shape::POLYCONV)
{
	points.push_back(vect1);
	points.push_back(vect2);
}

PolyConv::PolyConv(string name, int x1, int y1, int x2, int y2)
: ShapeSingle(name, Shape::POLYCONV)
{
	points.push_back(Vector2D(x1,y1));
	points.push_back(Vector2D(x2,y2));
}

PolyConv::PolyConv(string name, PolyConv& copie)
{
	this->name = name;
	this->shapeType = Shape::POLYCONV;
	this->offset = copie.offset;
	for(int i = 0; i < copie.points.size() ; i++)
		this->points.push_back(copie.points[i]);
}

PolyConv::~PolyConv()
{
}

bool PolyConv::IsInShape(int const x, int const y) const
{

	return true;
}

bool PolyConv::IsInShape(Vector2D point) const
{
	return IsInShape(point.GetX(), point.GetY());
}
