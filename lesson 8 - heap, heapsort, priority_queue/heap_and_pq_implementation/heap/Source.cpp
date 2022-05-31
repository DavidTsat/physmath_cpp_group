#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <limits>
#include <iterator>
#include <queue>

#include "pq.h"

using namespace std;


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

template<typename T1, typename T2, typename... Args>
bool equal_(const T1& first_obj, const T2& second_obj)
{
	return first_obj == second_obj;
}

template<typename T1, typename T2, typename... Args>
bool equal_(const T1& first_obj, const T2& second_obj, const Args&... args)
{
	return (first_obj == second_obj) && equal_(second_obj, args...);
}

template <typename T, typename Cmp = greater<T>>
ostream& operator<<(ostream& os, const heap<T, Cmp>& h)
{
	if (!h.size()) return os;

	copy(&h[0], next(&h[1], h.size() - 1), ostream_iterator<T>(os, " "));
	return os;
}

void heap_sort_construction_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	vector<vector<int>> input_vecs = { v1, v2, v3, generate_random_vector(1000) };

	for (int i = 0; i < 4; ++i)
	{
		heap<int> h1(input_vecs[i]);
		heap<int> h2(input_vecs[i].cbegin(), input_vecs[i].cend());
		heap<int> h3(h2);
		cout << boolalpha << equal_(h1, h2, h3) << endl;
	}
}
void build_heap_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	vector<vector<int>> input_vecs = { v1, v2, v3, generate_random_vector(1000), generate_random_vector(1000) };
	for (int i = 0; i < 3; ++i)
	{
		heap<int> h(input_vecs[i]);
		cout << h << endl;
		cout << boolalpha << is_heap(&h[0], &h[h.size() - 1]) << endl;
	}
}

void heap_sort_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	vector<vector<int>> input_vecs = { v1, v2, v3, generate_random_vector(1000), generate_random_vector(1000) };
	for (int i = 0; i < 5; ++i)
	{
		heap<int> h(input_vecs[i]);
		h.heap_sort();
		cout << boolalpha << is_sorted(&h[0], next(&h[1], h.size() - 1)) << endl;
	}
}


void max_priority_queuetests()
{
	bool b = false;

	vector<int> random_vec = generate_random_vector(1000);

	max_priority_queue<int> pq1(random_vec);
	max_priority_queue<int> pq2(random_vec.cbegin(), random_vec.cend());
	max_priority_queue<int> pq3(pq2);
	max_priority_queue<int> pq4;

	for (int i : random_vec)
	{
		pq4.push(i);
	}

	std::priority_queue<int> pq_std(random_vec.cbegin(), random_vec.cend());

	while (!pq_std.empty())
	{

		int c1 = pq1.top();
		int c2 = pq2.top();
		int c3 = pq3.top();
		int c4 = pq4.top();

		int c_std = pq_std.top();

		if (!equal_(c1, c2, c3, c4, c_std))
		{
			cout << boolalpha << false << " top " << endl;
			b = true;
			break;
		}

		pq1.pop();
		pq2.pop();
		pq3.pop();
		pq4.pop();
		pq_std.pop();
	}
	if (!b)
	{
		cout << boolalpha << true << endl;
	}
	
	if (!equal_(true, pq1.empty(), pq2.empty(), pq3.empty(), pq4.empty()))
		cout << boolalpha << false << " empty " << endl;
	else
		cout << boolalpha << true << endl;
	  
}

void max_priority_queueconstruction_tests()
{
	vector<int> random_vec = generate_random_vector(100);

	max_priority_queue<int> pq1(random_vec);
	max_priority_queue<int> pq2(random_vec.cbegin(), random_vec.cend());
	max_priority_queue<int> pq3;

	for (int i : random_vec)
	{
		pq3.push(i);
	}

	vector<max_priority_queue<int>> input_pqs{ pq1, pq2, pq3 };

	for (const max_priority_queue<int>& pq_ : input_pqs)
	{
		cout << boolalpha << pq_.is_heap() << endl;
	}
}

int main() {
	heap_sort_construction_tests();
	build_heap_tests();
	heap_sort_tests();
	max_priority_queueconstruction_tests();
	max_priority_queuetests();
	
	return 0;
}