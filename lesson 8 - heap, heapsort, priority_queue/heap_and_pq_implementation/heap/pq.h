#pragma once
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

template<typename T, typename Cmp = greater<T>>
class max_priority_queue;

template<typename T, typename Cmp = greater<T>>
class min_priority_queue;

template<typename T, typename Compare = greater<T>>
class heap
{
	friend class priority_queue_<T, Compare>;
	friend class max_priority_queue<T, Compare>;
	friend class min_priority_queue<T, Compare>;

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

// priority_queue
template<typename T, typename Cmp>
class priority_queue_
{
protected:
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
	
	priority_queue_() : h() {}

	template <typename It>
	priority_queue_(It begin, It end) : h(begin, end) {}

	priority_queue_(const vector<T>& vec) : h(vec.cbegin(), vec.cend()) {}

	priority_queue_(const heap<T>& h2) : h(h2) {}

	priority_queue_(const priority_queue_<T>& other) : h(other.h) {}
public:

	const T& top() const
	{
		return h[0];
	}

	virtual void push(const T& t) = 0;

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


template<typename T, typename Cmp>
class max_priority_queue : public priority_queue_<T, Cmp>
{
public:

	max_priority_queue() : priority_queue_<T, Cmp>() {}

	template <typename It>
	max_priority_queue(It begin, It end) : priority_queue_<T, Cmp>(begin, end) {}

	max_priority_queue(const vector<T>& vec) : priority_queue_<T, Cmp>(vec) {}

	max_priority_queue(const heap<T>& h2) : priority_queue_<T, Cmp>(h2) {}

	max_priority_queue(const priority_queue_<T>& other) : priority_queue_<T, Cmp>(other.h) {}

	void push(const T& t) override
	{
		// max-heap
		if (this->h.heap_size < this->h.data.size() - 1)
		{
			this->h.data[this->h.heap_size] = numeric_limits<T>::min();
		}
		else
			this->h.data.push_back(numeric_limits<T>::min());

		++this->h.heap_size;
		this->change_val(this->h.heap_size, t);
	}
	
};

template<typename T, typename Cmp>
class min_priority_queue : public priority_queue_<T, Cmp>
{
public:

	// TODO min_priority_queue constructors

	void push(const T& t) override
	{
		// TODO
	}

};