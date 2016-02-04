#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include <vector>

#include <ShapeSingle.h>

class Segment : public ShapeSingle
{
	public:
		Segment(std::string name, int x1, int y1, int x2, int y2);
		Segment(std::string name, Vector2D vect1, Vector2D vect2);
		Segment(const Segment& copie);

        /** \brief Verify if the point is in the shape
         *
         * \param point : the point you want to test
         * \return true if in the shape, false if not
         */
		virtual bool IsInShape(Vector2D point) const;

		virtual Shape* Clone();
		Segment();
		virtual ~Segment();
	private:
};

#endif // SEGMENT_H
