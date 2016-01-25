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
		Rectangle(std::string name, Rectangle& copie);

        /** \brief Verify if the point is in the shape
         *
         * \param point : the point you want to test
         * \return true if in the shape, false if not
         */
		virtual bool IsInShape(Vector2D point) const;

		/** \brief Verify if the point is in the shape
         *
         * \param x : the x coordinate of the point you want to test
         * \param y : the y coordinate of the point you want to test
         * \return true if in the shape, false if not
         */
		virtual bool IsInShape(int x, int y) const;

		Rectangle();
		virtual ~Rectangle();
	private:
};

#endif // RECTANGLE_H
