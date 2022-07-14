#include <iostream>
#include <cassert>

using LL = long long;
using ULL = unsigned long long;

using namespace std;

ULL MSB_value(ULL num)
{
	if (!num)
		return 0;
	ULL ans = 1;
	while (num >>= 1)
		ans <<= 1;
	return ans;
}

LL get_and_for_range(LL left, LL right)
{
	assert(("left number can't be greater than right number", left <= right));
	if (left < 0 && right > 0 || !left || !right)
		return 0;
	if (left == right)
		return left;
	if (left > 0) {
		ULL MSBvall = MSB_value(left);
		if (MSBvall << 1 <= right) // this is the key optimization. Great!
			return 0;
		return MSBvall + get_and_for_range(left ^ MSBvall, right ^ MSBvall);
	}
	LL ones = 1ll << ((sizeof(LL) << 3) - 1), i = 1ll << ((sizeof(LL) << 3) - 2);
	//finding 1s, that all numbers in given range have
	while (left & right & i) { //checking if left and right have 1 in some position
		ones |= i;
		i >>= 1;
	}
	return ones | get_and_for_range(left ^ ones, right ^ ones);
}

int nulls_count(int x)
{
	if (!x)
		return 32;
	int c = (sizeof(int) << 3);
	int ans = 0, y = 1 << (sizeof(int) << 3) - 2;
	while (y && !(x & y)) {
		y >>= 1;
		++ans;
	}
	return ans;
}

string short_to_binary_string(short x)
{
	string s;
	int neg = x < 0;
	x = neg ? ~x : x;
	
	while (x) {
		if ((x & 1) ^ neg)
			s = '1' + s;
		else
			s = '0' + s;
		x >>= 1;
	}
	
	return neg ? string((sizeof(short) << 3) - s.size(), '1') + s : string((sizeof(short) << 3) - s.size(), '0') + s;
}

unsigned binary_string_to_int(std::string s)
{
	unsigned x = 0;
	for (char c : s) {
		x <<= 1;
		x ^= c - '0';
	}
	return x;
}

int main()
{
	int l1 = 1;
	int r1 = 2147483647;

	int l2 = 5;
	int r2 = 7;

	cout << short_to_binary_string(-7) << endl;
	cout << short_to_binary_string(513) << endl;
	cout << short_to_binary_string(0) << endl;
	cout << short_to_binary_string(7) << endl;

	cout << binary_string_to_int(short_to_binary_string(513)) << endl;
	cout << nulls_count(784252715/4) << endl;
	cout << get_and_for_range(-5, -1) << endl;
	cout << get_and_for_range(l1, r1) << endl;

	return 0;
}