#ifndef POLYUNION_H
#define POLYUNION_H

#include <iostream>
#include <ShapeMultiple.h>
#include <Rectangle.h>
#include <Segment.h>
#include <PolyConv.h>
#include <vector>

class PolyUnion: public ShapeMultiple
{
	public:
		PolyUnion(std::string name = "", std::vector<Shape*> shapes = {});
		PolyUnion(const PolyUnion& copie);
		virtual ~PolyUnion();

		virtual bool IsInShape(Vector2D point) const;

		virtual Shape* Clone();

	protected:
	private:
};

#endif // POLYUNION_H
