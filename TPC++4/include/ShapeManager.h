#ifndef SHAPEMANAGER_H
#define SHAPEMANAGER_H

#include <map>
#include <vector>
#include <deque>
#include <stack>
#include <string>
#include <Shape.h>

typedef std::map<std::string, Shape> ShapeMap;

class ShapeManager
{
	public:
		ShapeManager();
		virtual ~ShapeManager();
	protected:
		ShapeMap ShapeTable;
	private:
};

#endif // SHAPEMANAGER_H
