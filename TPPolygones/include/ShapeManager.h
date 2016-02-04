#ifndef SHAPEMANAGER_H
#define SHAPEMANAGER_H

#include <string>
#include <cstring>
#include <sstream>
#include <fstream>

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

        /** \brief standardize the answer of the program
         *
         * \param s : the message to display
         * \param isOk : true if no problem, false if not
         * \return isOk (serialization)
         *
         */
		bool Answer(std::string const& s, bool const& isOk = false);

		/** \brief Add a shape into the table if possible
		* \param shape a pointer on the shape you want to add
		* \return true if added, false if not
		**/
		bool Add(Shape* shape);

		/** \brief Delete a shape
		* \param name the name of the shape you want to delete
		* \return true if deleted, false if not
		**/
		bool Delete(std::string const& name);

		/** \brief Move a shape
		* \param name the name of the shape
		* \param vect the vector of translation
		* \return true if moved
		**/
		bool Move(std::string const& name, Vector2D const& vect);

		/** @brief Store the current state of the program in a file
		** @param fileName the name of the file
		** @return true if successfully stored
		**/
		bool Store(std::string const& fileName);

		/** @brief Restore an old state of the program from a file
		** @param fileName the name of the file
		** @return true if successfully reloaded
		**/
		bool Load(std::string const& fileName);

		/** @brief Verify if the point is in the shape
		*
		* @param name the name of the shape
		* @param point the point you want to test
		* @return true if in the shape, false if not or if the shape doesn't exist
		**/
		bool Hit(std::string const& name, Vector2D const& point);

		/** @brief Clear the shape map
		** @return true if successfully cleared
		**/
		bool Empty();

		/** @brief Display the shapes
		**/
		void List();

		/** @brief Verify if a name is attributed to a shape
		** @param name the name
		** @return true if taken
		**/
		bool IsInTable(std::string const& name);

		/** @brief Search a shape with a given name
		* don't forget to delete it after use
		* @param name the name of the shape
		* @return a pointer on the shape
		**/
		Shape* findShape(std::string const& name);

		/** @brief Return a vector wich contains
		* all the shapes from the ShapeMaager **/
		std::vector<Shape*> TableCopy();

		/** @brief Create a shape manager **/
		ShapeManager();

		/** @brief delete the shape manager **/
		virtual ~ShapeManager();
	protected:

		///A table wich contains all the shape in the map
		ShapeMap ShapeTable;
};

#endif // SHAPEMANAGER_H
