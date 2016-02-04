#include <iostream>
#include <History.h>

using namespace std;

int main()
{
	cout << "=================================" << endl;
	cout << "========= Shape Manager =========" << endl;
	cout << "=================================" << endl << endl;

	History history = History();
	history.Read();

	cout << " ================================" << endl;
	cout << "=== It was nice to meet you ! ===" << endl;
	cout << "=================================" << endl;

    return 0;
}
