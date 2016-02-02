#ifndef SHAPESINGLE_H
#define SHAPESINGLE_H

#include <Shape.h>
#include <vector>
#include <Vector2D.h>

class ShapeSingle : public Shape
{

	public:
		ShapeSingle(std::string name = "", int shapeType = Shape::NOT_SHAPE);
		ShapeSingle(const ShapeSingle& copie);

		virtual ~ShapeSingle();

		virtual std::string toString(int tab = -1) const;

		virtual bool IsInShape(Vector2D point) const = 0;
		virtual bool IsInShape(int x, int y) const = 0;

		virtual Shape* Clone() = 0;
	protected:
		std::vector<Vector2D> points;
	private:
};

#endif // SHAPESINGLE_H
