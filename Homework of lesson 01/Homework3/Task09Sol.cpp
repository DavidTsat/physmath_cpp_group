#include <vector>
using std::vector;

vector<int> xor_subarrays(vector<int>& arr, vector<vector<int>>& xor_indices)
{
	int i;
	vector<int> xor_prefixes(arr.size() + 1), ans;
	for (i = 1; i <= arr.size(); ++i)
		xor_prefixes[i] = xor_prefixes[i - 1] ^ arr[i - 1];
	for (i = 0; i < xor_indices.size(); ++i)
		ans.push_back(xor_prefixes[xor_indices[i][0]] ^ xor_prefixes[xor_indices[i][1] + 1]);
	return ans;
}
