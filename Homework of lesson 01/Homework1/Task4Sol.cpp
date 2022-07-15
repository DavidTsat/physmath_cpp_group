#include <string>
using std::string;

string short_to_binary_string(short x)
{
	bool neg = x < 0;
	string s;
	if (!x)
		s.append(sizeof(short) << 3, '0');
	if (neg)
		x = ~x;
	while (x) {
		if (x & 1 ^ neg)
			s += '1';
		else
			s += '0';
		x >>= 1;
	}
	if (neg)
		s.append((sizeof(short) << 3) - s.size(), '1');
	else
		s.append((sizeof(short) << 3) - s.size(), '0');
	return string(s.rbegin(), s.rend());
}
