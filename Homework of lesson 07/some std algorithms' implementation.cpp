#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <functional>
#include <set>
#include <iterator>

using namespace std;

template<typename It1, typename It2, typename BinaryPredicate = equal_to<typename iterator_traits<It1>::value_type>>
constexpr It1 search_(It1 start1, It1 end1, It2 start2, It2 end2, BinaryPredicate binary_pred = equal_to<typename iterator_traits<It1>::value_type>{})
{
	size_t sz = distance(start2, end2), i;
	It1 it1, it2;
	It2 it3;
	for (it1 = start1; it1 != end1; ++it1) {
		it2 = it1;
		it3 = start2;
		for (i = 0; i < sz; ++i) {
			if (binary_pred(*it2, *it3)) {
				++it2;
				++it3;
			}
			else
				break;
		}
		if (i == sz)
			return it1;
	}
	return end1;
}

bool contains(const string& str, const string& s)
{
	return search_(str.cbegin(), str.cend(), s.cbegin(), s.cend()) != str.cend();
}


void test_search_()
{
	string str = "why waste time learning, when ignorance is instantaneous?";
	// str.find() can be used as well
	cout << boolalpha << contains(str, "learning") << endl;   // true
	//	<< contains(str, "lemming") << '\n';  // false
}

template<typename It, typename T, typename Compare = less<T>>
It upper_bound_(It start, It end, const T& val, Compare cmp = less<T>{})
{
	size_t count = distance(start, end), step;
	while (count > 0) {
		step = count / 2;
		It mid = next(start, step);
		if (!cmp(val, *mid)) {
			start = next(mid);
			count -= step + 1;
		}
		else {
			end = mid;
			count = step;
		}
	}
	return start;
}

template<typename It>
void rotate_(It start, It n_first, It end)
{
	if (start == n_first || n_first == end)
		return;
	size_t dist = distance(start, n_first), i = 0;
	while (n_first != end) {
		swap(*start, *n_first);
		++start;
		++n_first;
		if (++i > dist)
			i = 0;
	}
	rotate_(start, prev(end, i), end);
}

template <typename It>
void insertion_sort_(It begin, It end)
{
	for (auto it = begin; it != end; ++it)
	{
		auto greater_ = upper_bound_(begin, it, *it);
		rotate_(greater_, it, next(it));
	}
}

template<typename It1, typename It2, typename It3>
void merge_(It1 start1, It1 end1, It2 start2, It2 end2, It3 merged_first)
{
	while (start1 != end1 && start2 != end2) {
		if (*start1 < *start2) {
			*merged_first = *start1;
			++start1;
		}
		else {
			*merged_first = *start2;
			++start2;
		}
		++merged_first;
	}
	while (start1 != end1) {
		*merged_first = *start1;
		++start1;
		++merged_first;
	}
	while (start2 != end2) {
		*merged_first = *start2;
		++start2;
		++merged_first;
	}
}

/*
Пусть дан некоторый отсортированный в неубывающем порядке вектор целых чисел {-8, -5, -3, 0, 1, 4, 4, 5, 7, 9}
Требуется написать алгоритм, который за линейное время вернет отсортированный вектор квадратов элементов входного вектора:
{-8, -5, -3, 0, 1, 4, 4, 5, 7, 9} -> {0, 1, 9, 16, 16, 25, 25, 49, 64, 81}
*/

vector<int> square_sort(const vector<int>& v)
{
	bool first_neg = true;
	vector<int>::const_iterator for_merge = v.begin();
	vector<int> v2, ans;
	for (vector<int>::const_reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
		if (*it < 0) {
			if (first_neg) {
				first_neg = false;
				for_merge = it.base();
			}
			v2.push_back(-*it);
		}
	merge_(v2.begin(), v2.end(), for_merge, v.end(), back_inserter(ans));
	for (size_t i = 0; i < ans.size(); ++i)
		ans[i] *= ans[i];
	return ans;
}

template <typename It>
void merge_sort_(It begin, It end)
{
	if (distance(begin, end) > 1)
	{
		It mid_point = next(begin, distance(begin, end) / 2);
		merge_sort_(begin, mid_point);
		merge_sort_(mid_point, end);
		vector<iterator_traits<It>::value_type> vr;

		merge_(begin, mid_point, mid_point, end, back_inserter(vr));
		copy(vr.cbegin(), vr.cend(), begin);
	}
}

void square_sort_tests()
{
	vector<int> v1 = { -8, -5, -3, 0, 1, 4, 4, 5, 7, 9 };
	vector<int> v2 = { 0, 1, 4 };
	vector<int> v3 = { -5, -3 };
	vector<int> v4;

	vector<int> v1_answer = { 0, 1, 9, 16, 16, 25, 25, 49, 64, 81 };
	vector<int> v2_answer = { 0, 1, 16 };
	vector<int> v3_answer = { 9, 25 };
	vector<int> v4_answer = {};

	vector<vector<int>> inputs = { v1, v2, v3, v4 };
	vector<vector<int>> outputs = { v1_answer, v2_answer, v3_answer, v4_answer };

	for (int i = 0; i < inputs.size(); ++i)
	{
		vector<int> answ = square_sort(inputs[i]);

		cout << boolalpha << (outputs[i] == answ) << endl;
	}
}

std::vector<int> generate_random_vector(size_t size, int left = -1000, int right = 1000)
{
	using value_type = int;

	static std::uniform_int_distribution<value_type> distribution(
		left, right
	);
	static std::default_random_engine generator;

	std::vector<value_type> data(size);
	std::generate(data.begin(), data.end(), []() { return distribution(generator); });
	return data;
}


void test_sort(function<void(vector<int>::iterator, vector<int>::iterator)> my_sort)
{
	for (int i = 0; i < 100; ++i)
	{
		vector<int> v = generate_random_vector(1000);
		vector<int> v2(v);
		my_sort(v.begin(), v.end());
		sort(v2.begin(), v2.end());
		cout << boolalpha << (v == v2) << endl;
	}
}

template<typename It>
bool next_permutation_(It start, It end)
{
	if (start == end || next(start) == end)
		return false;
	It it1, it2;
	for (it1 = prev(end, 2), it2 = prev(end); it1 != start; --it1, --it2)
		if (*it1 < *it2)
			break;
	if (it1 == start && *it1 >= *it2) {
		reverse(start, end);
		return false;
	}
	reverse(it2, end);
	It swap_with = upper_bound_(it2, end, *it1);
	swap(*it1, *swap_with);
	return true;
}

/*
* Permutations
*
* Input: nums = [1, 2, 3]
* Output : [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
* Input : nums = [0, 1]
* Output : [[0, 1], [1, 0]]
* Input : nums = [1]
* Output : [[1]]
*/

struct permuts
{
	static vector<vector<int>> all_permutations_recursive(vector<int>& nums)
	{
		vector<vector<int>> ans, returned;
		if (nums.size() < 2) {
			ans.push_back(nums);
			return ans;
		}
		vector<int> new_nums(nums.size()), temp(nums.size() - 1);
		size_t i, j, k;
		for (i = 0; i < nums.size(); ++i) {
			k = 0;
			for (j = 0; j < nums.size(); ++j)
				if (nums[j] != nums[i]) {
					temp[k] = nums[j];
					++k;
				}
			returned = all_permutations_recursive(temp);
			for (j = 0; j < returned.size(); ++j) {
				new_nums[0] = nums[i];
				copy(returned[j].begin(), returned[j].end(), ++new_nums.begin());
				ans.push_back(new_nums);
			}
		}
		return ans;
	}

	static vector<vector<int>> all_permutations_with_next_permutation(vector<int>& nums)
	{
		vector<vector<int>> ans;
		sort(nums.begin(), nums.end());
		do {
			ans.push_back(nums);
		} while (next_permutation_(nums.begin(), nums.end()));
		return ans;
	}
};

void permutation_tests()
{
	permuts p;
	vector<decltype(&permuts::all_permutations_recursive)> permut_functions = { &permuts::all_permutations_recursive, &permuts::all_permutations_with_next_permutation };

	for (auto permut_function : permut_functions)
	{
		vector<int> v1 = { 1, 2, 3 };
		vector<int> v2 = { 0, 1 };
		vector<int> v3 = { 1 };

		vector<vector<int>> v1_answ = { {1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1} };
		vector<vector<int>> v2_answ = { {0, 1}, {1, 0} };
		vector<vector<int>> v3_answ = { { 1 } };

		vector<vector<int>> v_inputs = { v1, v2, v3 };
		vector<vector<vector<int>>> v_outputs = { v1_answ, v2_answ, v3_answ };

		bool b1 = true;
		bool b2 = true;

		for (int i = 0; i < v_inputs.size(); ++i)
		{
			set<int> s;
			vector<vector<int>> v_answ2 = permut_function(v_inputs[i]);

			for (int j = 0; j < v_outputs[i].size(); ++j)
			{
				auto p = find(v_outputs[i].cbegin(), v_outputs[i].cend(), v_answ2[j]);
				if ((p != v_outputs[i].cend()) && (s.find(distance(v_outputs[i].cbegin(), p)) == s.end()))
				{
					s.insert(distance(v_outputs[i].cbegin(), p));
				}
				else
				{
					cout << boolalpha << false << endl;
					b1 = false;
					break;
				}
			}
			if (b1)
			{
				cout << boolalpha << true << endl;
			}
		}
	}
}

int main()
{
	test_search_();
	square_sort_tests();
	test_sort([](vector<int>::iterator begin, vector<int>::iterator end) {merge_sort_(begin, end); });
	test_sort([](vector<int>::iterator begin, vector<int>::iterator end) {insertion_sort_(begin, end); });
	permutation_tests();
	return 0;
}