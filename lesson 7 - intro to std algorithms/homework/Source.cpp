#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <functional>
#include <set>
#include <iterator>

using namespace std;

// TODO
constexpr SourceIt search_(/*TODO*/)
{
	// TODO
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
void upper_bound_(/*TODO*/) // implement or copy/paste upper_bound_from previous class's implementation if you are sure you know the implementation
{
	// TODO
}


void rotate_(/*TODO*/)
{
	// TODO
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


void merge_(/*TODO*/)
{
	// TODO
}

/*
Пусть дан некоторый отсортированный в неубывающем порядке вектор целых чисел {-8, -5, -3, 0, 1, 4, 4, 5, 7, 9}
Требуется написать алгоритм, который за линейное время вернет отсортированный вектор квадратов элементов входного вектора:
{-8, -5, -3, 0, 1, 4, 4, 5, 7, 9} -> {0, 1, 9, 16, 16, 25, 25, 49, 64, 81}
*/

vector<int> square_sort(const vector<int>& v)
{
	// TODO
	return {};
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


bool next_permutation_(/*TODO*/)
{
	// TODO
	// COmparison of elements should be done by operator <
	// If there is no next permutation return false, otherwise permute the sequence in-place and return true

	/*
	Examples:
	{1,2,3} -> {1,3,2}
	{2,4,3,1} -> {3,1,2,4}
	{4,3,2,1} -> {4,3,2,1} // false
	*/
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
		//TODO
	}

	static vector<vector<int>> all_permutations_with_next_permutation(vector<int>& nums)
	{
		//TODO. Use next_permutation_ you implemented
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
	//	test_search_();
	//	square_sort_tests();
	//	test_sort([](vector<int>::iterator begin, vector<int>::iterator end) {merge_sort_(begin, end); });
	//	test_sort([](vector<int>::iterator begin, vector<int>::iterator end) {insertion_sort_(begin, end); });
	//	permutation_tests();
	return 0;
}