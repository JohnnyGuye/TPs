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

bool PolyConv::IsInShape(Vector2D P) const
{
	bool c = false;
	for (unsigned int i = 0, j = points.size() - 1 ; i < points.size(); j = i++) {
		Vector2D A = points[i];
		Vector2D B = points[j];
		if (
				(
					(((A.GetY() <= P.GetY())) && (P.GetY() < B.GetY())) ||
					(((B.GetY() <= P.GetY())) && (P.GetY() < A.GetY()))
				) &&
				((B.GetY() - A.GetY()) * ( A.GetX() - P.GetX()) > (B.GetX() - A.GetX()) * (A.GetY() - P.GetY()))
			)

			c = !c;
	}
	return c;
}
