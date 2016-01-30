#ifndef SHAPEMULTIPLE_H
#define SHAPEMULTIPLE_H

#include <vector>
#include <Vector2D.h>
#include <Shape.h>

class ShapeMultiple: public Shape
{

	public:
		ShapeMultiple(std::string name, int shapeType);
		virtual ~ShapeMultiple();

		virtual bool IsInShape(Vector2D point) const = 0;
		virtual bool IsInShape(int x, int y) const = 0;
		virtual Shape* Clone() = 0;
	protected:
		std::vector<Shape*> shapes;
	private:
};

#endif // SHAPEMULTIPLE_H
