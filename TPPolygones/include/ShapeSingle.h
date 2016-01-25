#ifndef SHAPESINGLE_H
#define SHAPESINGLE_H

#include <Shape.h>
#include <vector>
#include <Vector2D.h>

class ShapeSingle : public Shape
{

	public:
		ShapeSingle(std::string name = "", int shapeType = Shape::NOT_SHAPE);
		virtual ~ShapeSingle();

		virtual bool IsInShape(Vector2D point) const = 0;
		virtual bool IsInShape(int x, int y) const = 0;
	protected:
		std::vector<Vector2D> points;
	private:
};

#endif // SHAPESINGLE_H
