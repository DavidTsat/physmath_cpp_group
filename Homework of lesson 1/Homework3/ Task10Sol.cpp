#include <vector>

int missing_number(std::vector<int>& nums)
{
	int sum = 0, n = nums.size(), i;
	for (i = 0; i < n; ++i)
		sum += nums[i];
	return n * (n + 1) / 2 - sum;
}
