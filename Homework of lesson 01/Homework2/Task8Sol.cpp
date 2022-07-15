#include <vector>
using std::vector;

vector<vector<int>> power_set(vector<int> v)
{
	unsigned newsz = 1 << v.size(), i, j;
	vector<int> subset;
	vector<vector<int>> PowerSet;
	for (i = 0; i < newsz; ++i) {
		for (j = 0; j < (sizeof(i) << 3) - 2; ++j)
			if (i & (1 << j))
				subset.push_back(v[j]);
		PowerSet.push_back(move(subset));
	}
	return PowerSet;
}
