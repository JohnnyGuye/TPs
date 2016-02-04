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
							NOT_SHAPE = 0;

	// --------------------------------------------- Methods
	public:
		Vector2D& Move(Vector2D const vect);
		Vector2D GetOffset() const;

		virtual bool IsInShape(Vector2D point) const = 0;

		int GetType() const;
		std::string GetName() const;

		virtual std::string toString(int tab = -1) const;
		virtual std::string GetPersistence() const;

		Shape(std::string name = "", int shapeType = NOT_SHAPE);
		Shape(const Shape& copie);

		virtual ~Shape();
		virtual Shape* Clone() = 0;
	protected:
		std::string name;
		Vector2D offset;
		int shapeType;
	private:
};

#endif // SHAPE_H
