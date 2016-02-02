#include "util.h"

using namespace std;

void split(string str, vector<string>& tokens)
{
    istringstream iss(str);
	tokens.clear();
    do
    {
        string sub;
        iss >> sub;
		if(sub != "")
		{
			tokens.push_back(sub);
		}
    } while (iss);
}

int my_stoi(string str)
{
	int ans = 0;
	int fact = 1;
	if(str.at(0) == '-')
	{
		fact = -1;
		str = str.substr(1);
	}

	for(char c : str)
	{
		if(c < '0' || c > '9')
			break;
		ans = 10 * ans + (c - '0');
	}
	return fact * ans;
}
