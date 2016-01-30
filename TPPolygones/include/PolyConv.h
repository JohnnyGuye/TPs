#ifndef POLYCONV_H
#define POLYCONV_H

#include <string>
#include <vector>

#include <ShapeSingle.h>

class PolyConv : public ShapeSingle
{
	public:
		PolyConv(std::string name, int x1, int y1, int x2, int y2);
		PolyConv(std::string name, Vector2D vect1, Vector2D vect2);
		PolyConv(const PolyConv& copie);

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

		static bool VerifyConvexity(std::vector<Vector2D>& points);

		PolyConv();
		virtual ~PolyConv();
	private:
};

#endif // POLYCONV_H
