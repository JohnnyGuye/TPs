#include <iostream>

#include <ShapeManager.h>

using namespace std;

int main()
{
	cout << "=================================" << endl;
	cout << "========= Shape Manager =========" << endl;
	cout << "=================================" << endl << endl;

	cout << "New into this ? Here is the help : " << endl;
	cout << " - EXIT : end the program" << endl
		<< " - S [name] x y x' y' : create a segment beginning in x,y ending in x',y " << endl
		<< " - HIT [name] x y : verify if the point is in the shape " << endl
		<< endl;

    ShapeManager Manager = ShapeManager();
	Manager.Read();
	cout << " ================================" << endl;
	cout << "=== It was nice to meet you ! ===" << endl;
	cout << "=================================" << endl;

    return 0;
}
