#ifndef SHAPE_H
#define SHAPE_H

#include <Vector2D.h>
#include <string>
#include <vector>

class Shape
{
	// -------------------------------------------Constantes
	public:
		static const int	SEGMENT = 1,		//0000 0001
							RECTANGLE = 2,		//0000 0010
							POLYCONV = 4,		// etc...
							REUSHAPE = 8,
							INTERSHAPE = 16,
							FAILSHAPE = 32;

	// --------------------------------------------- Methods
	public:
		static bool Unify(std::string name, Shape shape1, Shape shape2);
		static bool Unify(std::string name, std::vector<Shape> shapes);

		static bool Intersect(std::string name, Shape shape1, Shape shape2);
		static bool Intersect(std::string name, std::vector<Shape> shapes);

		void Move(Vector2D const vect);

		virtual bool IsInShape(Vector2D point);
		virtual bool IsInShape(int x, int y);

		Shape();
		virtual ~Shape();
	protected:
		Vector2D offset;
	private:
};

#endif // SHAPE_H
