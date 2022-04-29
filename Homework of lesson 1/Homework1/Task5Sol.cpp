#include <string>
using std::string;

unsigned binary_string_to_int(string s)
{
	unsigned x = 0;
	for (char c : s) {
		x <<= 1;
		x ^= c - '0';
	}
	return x;
}
