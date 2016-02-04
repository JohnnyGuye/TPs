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

		/** @brief return a string that describe the shape */
		virtual std::string toString(int tab = -1) const;

		/** @brief verify if a point is in the shape
		* @return true if in shape, false if not
		**/
		virtual bool IsInShape(Vector2D point) const = 0;

		/** @brief Create a copy of the shape
		* @return a pointer on the copy
		**/
		virtual Shape* Clone() = 0;

		/** @brief return a tab with all points **/
		std::vector<Vector2D> GetPositions();

	protected:
		std::vector<Vector2D> points;
	private:
};

#endif // SHAPESINGLE_H
