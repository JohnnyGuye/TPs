#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <string>
#include <vector>
#include <sstream>

/** split a string into a vector all together given in parameters **/
void split(std::string str, std::vector<std::string>& tokens);

/** return an int corresponding to the string in base 10 **/
int my_stoi(std::string str);

#endif // UTIL_H_INCLUDED
