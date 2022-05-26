#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <functional>
#include <set>
#include <iterator>
#include <limits>
#include <queue>

using namespace std;

template <typename T, typename Compare = greater<T>>
class heap;

template<
	class T,
	class Compare = std::greater<T>,
	class Container = heap<T, Compare>
>
class priority_queue_;

template <typename T, typename Compare>
class heap
{
	friend class priority_queue_<T, Compare>;
public:
	using value_type = T;
private:
	vector<value_type> v;
	Compare cmp;
	size_t heap_size;
	bool is_heap;

	size_t parent(size_t i)
	{
		return i >> 1;
	}
	size_t left(size_t i)
	{
		return i << 1;
	}
	size_t right(size_t i)
	{
		return i << 1 | 1;
	}

	void heapify(size_t i)
	{
		/*
			4
		   / \
		  -1  2
		 / \
		1   0
		*/
		size_t l = left(i);
		size_t r = right(i);
		size_t largest = i;

		if (l <= heap_size && cmp(v[l], v[i]))
		{
			largest = l;
		}
		if (r <= heap_size && cmp(v[r], v[largest]))
		{
			largest = r;
		}
		if (largest == i) return;
		swap(v[i], v[largest]);
		heapify(largest);
	}

	void build_heap()
	{
		heap_size = v.size() - 1;
		for (int i = heap_size / 2; i >= 1; --i)
		{
			heapify(i);
		}
		is_heap = true;
	}

	void increase_val(size_t i, const value_type& new_val)
	{
		if (!cmp(new_val, v[i]))
		{
			// TODO throw an exception
			return;
		}
		v[i] = new_val;

		while (i > 1 && !cmp(v[parent(i)], v[i]))
		{
			swap(v[i], v[parent(i)]);
			i = parent(i);
		}
	}

public:

	heap() : v(vector<T>(1, T())), cmp(Compare()), heap_size(0), is_heap(false) {}
	heap(Compare cmp) : v(vector<T>(1, T())), cmp(cmp), heap_size(0), is_heap(false) {}
	heap(const heap<T>& m2) : v(m2.v), cmp(m2.cmp), heap_size(m2.heap_size) { }

	heap(const vector<value_type>& v2) : heap()
	{
		for (const value_type& q : v2)
		{
			v.push_back(q);
		}
		build_heap();
	}

	template <typename It>
	heap(It begin, It end) : heap()
	{
		while (begin != end)
		{
			v.push_back(*begin++);
		}
		build_heap();
	}

	heap(heap<value_type>&& m2) : heap()
	{
		swap_(*this, m2);
	}

	heap<value_type>& operator=(const heap<value_type>& m2)
	{
		heap<T> h(m2);
		swap_(*this, h);
	}

	heap<value_type>& operator=(heap<value_type>&& m2)
	{
		swap_(*this, m2);
	}

	friend void swap_(heap<value_type, Compare>& m1, heap<value_type, Compare>& m2)
	{
		std::swap(m1.v, m2.v);
		std::swap(m1.cmp, m2.cmp);
		std::swap(m1.heap_size, m2.heap_size);
	}

	value_type& operator[](size_t i) { return v[i]; }
	const value_type& operator[](size_t i) const { return v[i]; }
	
	template <typename Q>
	friend ostream& operator<<(ostream& os, const heap<Q>& h)
	{
		copy(next(h.v.cbegin()), h.v.cbegin() + h.heap_size + 1, ostream_iterator<Q>(os, " "));
		return os;
	}
	
	void heap_sort()
	{
		//	build_heap();
			// TODO for min-heap
		size_t hs = heap_size;
		for (size_t i = heap_size; i >= 2; --i)
		{
			swap(v[1], v[i]);
			--heap_size;
			heapify(1);
		}
		heap_size = hs;
		is_heap = false;
	}

	const size_t size() const { return heap_size; }
	//	const vector<value_type>& get_vector() const { return v; }
};


template<class T, class Compare, class Container>
class priority_queue_
{
	Container m;
	using value_type = typename Container::value_type;
public:
	priority_queue_() : m() {}

	priority_queue_(Compare cmp) : m(cmp) {}

	template <typename It>
	priority_queue_(It begin, It end) : m(begin, end) { }

	const value_type& top() const
	{
		return m[1];
	}

	void push(const value_type& value)
	{
		++m.heap_size;
		m.v.push_back(numeric_limits<value_type>::min());
		m.increase_val(m.heap_size, value);
	}

	template< class... Args >
	void emplace(Args&&... args)
	{

	}

	void pop()
	{
		if (m.heap_size == 0)
		{
			//throw an exception
			return;
		}
		m[1] = m[m.heap_size];
		--m.heap_size;
		m.heapify(1);
	}

	const size_t empty() const { return m.heap_size == 0; }
};


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

template <typename T, typename Compare = greater<T>>
bool operator==(const heap<T, Compare>& m, const vector<T>& v)
{
	if (m.size() != v.size())
		return false;

	for (int i = 0; i < m.size(); ++i)
	{
		if (m[i+1] != v[i])
			return false;
	}
	return true;
}

void make_heap_tests()
{
	for (int i = 0; i < 10; ++i)
	{
		vector<int> v = generate_random_vector(10000);
	//	vector<int> v2(v);
		heap<int> m(v);
	//	make_heap(v2.begin(), v2.end());
	//	cout << boolalpha << (m == v2) << endl; // QUESTION: WHY ? 
		cout << boolalpha << is_heap(&m[1], &m[1] + m.size()) << endl;
	}

}

void heap_sort_tests()
{
	vector<int> v1 = { 16,14,10,8,7,9,3,2,4,1 };
	vector<int> v2 = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> v3 = { 4,1,3,2,16,9,10,14,8,7 };

	heap<int> m(v3);

	cout << m << endl;
	m.heap_sort();
	cout << m << endl;

	for (int i = 0; i < 10; ++i)
	{
		vector<int> v = generate_random_vector(10000);
		vector<int> v2(v);

		heap<int> m(v);

		sort(v2.begin(), v2.end());
		m.heap_sort();

		cout << boolalpha << (m == v2) << endl;
	}
}

void priority_queue_test()
{
	vector<int> v1 = { 4,1,3,2,16,9,10,14,8,7 };
	priority_queue_<int> pq(v1.cbegin(), v1.cend());
	priority_queue_<int> pq2;
	std::priority_queue<int> pq_std(v1.cbegin(), v1.cend());

	for (int i : v1)
	{
		pq2.push(i);
	}

	bool b = true;
	while (!pq.empty())
	{
		int c = pq.top();
		pq.pop();

		int c2 = pq2.top();
		pq2.pop();

		int c3 = pq_std.top();
		pq_std.pop();
		
		if (c != c3 || c2 != c3)
		{
			b = false;
			cout << boolalpha << false << endl;
			break;
		}
	}
	if (b)
	{
		cout << boolalpha << true << endl;
	}
}


void priority_queue_tests()
{
	for (int i = 0; i < 10; ++i)
	{
		size_t sz = 10000;
		vector<int> v = generate_random_vector(sz);

		priority_queue_<int> pq(v.cbegin(), v.cend());
		priority_queue_<int> pq2;
		std::priority_queue<int> pq_std(v.cbegin(), v.cend());

		for (int i : v)
		{
			pq2.push(i);
		}

		bool b = true;
		while (sz--)
		{
			int c = pq.top();
			pq.pop();

			int c2 = pq2.top();
			pq2.pop();

			int c3 = pq_std.top();
			pq_std.pop();

			if (c != c3 || c2 != c3)
			{
				b = false;
				cout << boolalpha << false << endl;
				break;
			}
		}
		if (b)
		{
			cout << boolalpha << true << endl;
		}
	}
}

//https://leetcode.com/problems/kth-largest-element-in-an-array/
// QUESTION: Solution with min-heap ?

int main()
{
	make_heap_tests();
	heap_sort_tests();

	priority_queue_test();
	
	priority_queue_tests();
	return 0;
}