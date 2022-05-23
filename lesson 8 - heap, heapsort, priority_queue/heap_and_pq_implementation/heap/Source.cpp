#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <limits>
#include <iterator>
#include <queue>
using namespace std;

// max-heap min-heap
/*
1
16 14 10 8 7 9 3 2 4 1

data[i] >= data[left(i)]
data[i] >= data[right(i)]

			16
	  /    \
	14      10
 /  \    /  \
8    7  9    3
/    \ /
2    4 1

left(i) = 2*i == i<<1
right(i) = 2*i + 1 = (i<<1) | 1
parent(i) = i>>1

l_h = pow(2, h-1);
l_h = 2*(l_h-1)
2^0 + 2^1 +...+2^(h-1) = 2^h - 1
q = 2

h = log(n)
h = log(n+1) = O(logn)
n/2+1, ..., n

boundary of number of elements -> [2^(h-1) - 1 + 1,  2^h - 1]
*/

#define DEBUG

template<typename T, typename Cmp = greater<T>>
class priority_queue_;

template<typename T, typename Compare = greater<T>>
class heap
{
	friend priority_queue_<T, Compare>;
	vector<T> data;
	Compare cmp;
	size_t heap_size;

	size_t left(size_t i)
	{
		return i << 1;
	}
	size_t right(size_t i)
	{
		return (i << 1) | 1;
	}
	size_t parent(size_t i)
	{
		return i >> 1;
	}

	void heapify(size_t i)
	{
		/*
				  4
			  /   \
			 8     7
			/ \   /
		 2   4 1
	*/
	// max-heap
		size_t l = left(i);
		size_t r = right(i);
		size_t max_ = i;
		if (l <= heap_size && !cmp(data[max_], data[l]))
		{
			max_ = l;
		}
		if (r <= heap_size && !cmp(data[max_], data[r]))
		{
			max_ = r;
		}
		if (max_ == i) return;
		swap(data[max_], data[i]);
		heapify(max_);
	}

	void build_heap()
	{
		for (size_t i = heap_size / 2; i >= 1; --i)
		{
			heapify(i);
		}
	}
public:
	heap() : data(vector<T>(1, T())), cmp(greater<T>{}), heap_size(0) {}

	template<typename It>
	heap(It start, It end) : heap()
	{
		heap_size = distance(start, end);
		copy(start, end, back_inserter(data));
		// TODO to build the heap
		build_heap();
	}

	heap(const vector<T>& vec) : heap(vec.cbegin(), vec.cend()) {}

	heap(const heap<T>& other) : heap(++other.data.cbegin(), other.data.cend()) {}

	void heap_sort()
	{
		for (size_t i = heap_size; i > 1; --i)
		{
			swap(data[heap_size], data[1]);
			--heap_size;
			heapify(1);
		}
	}

	const T& operator[](size_t i) const { return data[i + 1]; }
	size_t size() const { return heap_size; }
};

template <typename T, typename Cmp = greater<T>>
bool operator==(const heap<T, Cmp>& h1, const heap<T, Cmp>& h2)
{
	if (h1.size() != h2.size()) return false;

	for (size_t i = 1; i < h1.size(); ++i)
	{
		if (h1[i] != h2[i]) return false;
	}
	return true;
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
		cout << boolalpha << is_heap(&h[0], &h[h.size()-1]) << endl;
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

// priority_queue
template<typename T, typename Cmp>
class priority_queue_
{
	heap<T, Cmp> h;

	void change_val(size_t i, const T& new_val)
	{
		h.data[i] = new_val;

		while (i > 1 && !h.cmp(h.data[h.parent(i)], h.data[i]))
		{
			swap(h.data[h.parent(i)], h.data[i]);
			i = h.parent(i);
		}
	}

public:
	priority_queue_() : h() {}

	template <typename It>
	priority_queue_(It begin, It end) : h(begin, end) {}

	priority_queue_(const vector<T>& vec) : h(vec.cbegin(), vec.cend()) {}

	priority_queue_(const heap<T>& h2) : h(h2) {}

	priority_queue_(const priority_queue_<T>& other) : h(other.h) {}

	const T& top() const
	{
		return h[0];
	}

	void push(const T& t)
	{
		// max-heap
		if (h.heap_size < h.data.size() - 1)
		{
			h.data[h.heap_size] = numeric_limits<T>::min();
		}
		else
			h.data.push_back(numeric_limits<T>::min());

		++h.heap_size;
		change_val(h.heap_size, t);
	}

	void pop()
	{
		swap(h.data[1], h.data[h.size()]);
		--h.heap_size;
		h.heapify(1);
	}

#ifdef DEBUG
	bool is_heap() const
	{
		return std::is_heap(next(h.data.cbegin()), h.data.cend());
	}
#endif

	bool empty() const
	{
		return h.heap_size == 0;
	}
};

void priority_queue_construction_tests()
{
	vector<int> random_vec = generate_random_vector(100);

	priority_queue_<int> pq1(random_vec);
	priority_queue_<int> pq2(random_vec.cbegin(), random_vec.cend());
	priority_queue_<int> pq3;

	for (int i : random_vec)
	{
		pq3.push(i);
	}

	vector<priority_queue_<int>> input_pqs{ pq1, pq2, pq3 };

	for (const priority_queue_<int>& pq_ : input_pqs)
	{
		cout << boolalpha << pq_.is_heap() << endl;
	}
}

void priority_queue_tests()
{
	bool b = false;

	vector<int> random_vec = generate_random_vector(1000);

	priority_queue_<int> pq1(random_vec);
	priority_queue_<int> pq2(random_vec.cbegin(), random_vec.cend());
	priority_queue_<int> pq3(pq2);
	priority_queue_<int> pq4;

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

int main() {
	heap_sort_construction_tests();
	build_heap_tests();
	heap_sort_tests();
	priority_queue_construction_tests();
	priority_queue_tests();
	
	return 0;
}