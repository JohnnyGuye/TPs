#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <vector>

#include <ShapeSingle.h>

class Rectangle : public ShapeSingle
{
	public:
		Rectangle(std::string name, int x1, int y1, int x2, int y2);
		Rectangle(std::string name, Vector2D vect1, Vector2D vect2);
		Rectangle(const Rectangle& copie);

        /** \brief Verify if the point is in the shape
         *
         * \param point : the point you want to test
         * \return true if in the shape, false if not
         */
		virtual bool IsInShape(Vector2D point) const;

		virtual Shape* Clone();
		Rectangle& operator=(const Rectangle& copie);

		Rectangle();
		virtual ~Rectangle();
	private:
};

#endif // RECTANGLE_H
