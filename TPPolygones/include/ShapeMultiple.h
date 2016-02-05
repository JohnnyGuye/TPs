#ifndef SHAPEMULTIPLE_H
#define SHAPEMULTIPLE_H

#include <vector>
#include <Vector2D.h>
#include <Shape.h>

class ShapeMultiple: public Shape
{

	public:
		ShapeMultiple(std::string name, int shapeType);
		ShapeMultiple(const ShapeMultiple& copie);
		virtual ~ShapeMultiple();

		/** @brief return a string that describe the shape */
		virtual std::string toString(int tab = -1) const;

		/** @brief string computed for an easy storage **/
		virtual std::string toStore() const;

		/** @brief verify if a point is in the shape
		* @return true if in shape, false if not
		**/
		virtual bool IsInShape(Vector2D point) const = 0;

		/** @brief Create a copy of the shape
		* @return a pointer on the copy
		**/
		virtual Shape* Clone() = 0;
	protected:
		std::vector<Shape*> shapes;
	private:
};

#endif // SHAPEMULTIPLE_H
