#include <cassert>

using LL = long long;
using ULL = unsigned long long;

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
	assert(("left number can't be greater than right number", left < right));
	if (left < 0 && right > 0 || !left || !right)
		return 0;
	if (left == right)
		return left;
	if (left > 0) {
		ULL MSBvall = MSB_value(left);
		if (MSBvall << 1 <= right)
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
