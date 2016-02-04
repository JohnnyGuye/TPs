#ifndef POLYINTERSECT_H
#define POLYINTERSECT_H

#include <iostream>
#include <ShapeMultiple.h>
#include <Rectangle.h>
#include <Segment.h>
#include <PolyConv.h>
#include <vector>

class PolyIntersect: public ShapeMultiple
{
	public:
		PolyIntersect(std::string name = "", std::vector<Shape*> shapes = {});
		PolyIntersect(const PolyIntersect& copie);
		virtual ~PolyIntersect();

		virtual bool IsInShape(Vector2D point) const;

		virtual Shape* Clone();

	protected:
	private:
};

#endif // POLYINTERSECT_H
