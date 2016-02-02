#ifndef SHAPEMANAGER_H
#define SHAPEMANAGER_H

#include <string>
#include <cstring>
#include <sstream>

#include <Shape.h>
#include <Segment.h>
#include <Rectangle.h>
#include <PolyConv.h>
#include <PolyUnion.h>
#include <PolyIntersect.h>

#include <map>
#include <tuple>

#include <iostream>

typedef std::map<std::string, Shape*> ShapeMap;

class ShapeManager
{
	public:
        /** \brief The methods wich reads the command.
         */
		void Read();

        /** \brief standardize the answer of the program
         *
         * \param s : the message to display
         * \param isOk : true if no problem, false if not
         * \return isOk (serialization)
         *
         */
		bool Answer(std::string s, bool isOk = false);

		bool Add(Shape* shape);
		bool Delete(std::string name);
		bool Remove(std::string const name);
		bool Move(std::string const name, Vector2D const vect);
		bool Load(std::string const fileName);
		bool Empty();

		ShapeManager();
		virtual ~ShapeManager();
	protected:
		ShapeMap ShapeTable;
	private:
};

#endif // SHAPEMANAGER_H
