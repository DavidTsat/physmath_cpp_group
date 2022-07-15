#include <vector>

int checkbit(std::vector<int>& nums, int i)
{
	int cnt = 0;
	for (const int& x : nums)
		if (x & i)
			++cnt;
	return cnt % 3 ? i : 0;
}

int singleNumber(std::vector<int>& nums)
{
	int i = 1, ans = 0;
	while (i > 0) {
		ans |= checkbit(nums, i);
		i <<= 1;
	}
	return ans | checkbit(nums, i);
}
