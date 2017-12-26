#include "Utilities.h"

string substr(const string& str, int l, int r)
{
	return str.substr(l, r - l + 1);
}
string to_string(char c)
{
	return string({ c });
}