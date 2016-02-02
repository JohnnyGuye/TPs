#include "PolyConv.h"

using namespace std;

bool PolyConv::VerifyConvexity(vector<Vector2D>& points)
{
	Vector2D BA, BC;
	double sum = 0;
	int nbPoints = points.size();
	double angleABC;
	for (int i = 0 ; i < nbPoints; i++)
	{
		BA = points[(i-1)%nbPoints] - points[i];
		BC = points[(i+1)%nbPoints] - points[i];
		angleABC = Vector2D::angle(-BA,BC);
		if(angleABC < 0)
			return false;
		sum += angleABC;
	}
	if(sum > PI)
		return false;
	return true;
}

PolyConv::PolyConv(string nick, const vector<Vector2D>& points)
: ShapeSingle(nick, Shape::POLYCONV)
{
	for(Vector2D point : points)
		this->points.push_back(point);
}

PolyConv::PolyConv(const PolyConv& copie)
: ShapeSingle(copie)
{
	this->shapeType = Shape::POLYCONV;
}

Shape* PolyConv::Clone()
{
	return new PolyConv(*this);
}

PolyConv::~PolyConv()
{
}

bool PolyConv::IsInShape(int const x, int const y) const
{
      bool c = false;
      for (unsigned int i = 0, j = points.size() - 1 ; i < points.size(); j = i++) {
        if (
				(
					((points[i].GetY() <= y) && (y < points[j].GetY())) ||
					((points[j].GetY() <= y) && (y < points[i].GetY()))
				) &&
				((points[j].GetY() - points[i].GetY()) * ( points[i].GetX() - x) > (points[j].GetX() - points[i].GetX()) * (points[i].GetY() - y))
			)

          c = !c;
      }
      return c;
}

bool PolyConv::IsInShape(Vector2D point) const
{
	return IsInShape(point.GetX(), point.GetY());
}
