#pragma once

#include <new>
#include <vector>

using namespace std;

#define INITIAL_SIZE 10

template <typename T>
class vec
{
public:
	using value_type = T;
	using size_type = size_t;
	using reference = value_type&;
	using const_reference = const value_type&;

private:
	void get_memory(size_type sz, size_type cap)
	{
		capacity_ = cap;
		size_used = sz;
		data = (value_type*)operator new[](cap * sizeof(value_type));
	}

	void get_memory(size_type sz)
	{
		get_memory(sz, 2 * sz);
	}
public:
	vec() {
		get_memory(0u, default_init_capacity);
	}

	explicit vec(size_type sz) : vec(sz, value_type()) {}

	vec(size_type sz, const_reference val) {
		get_memory(sz);
		for_each_n(data, size_used, [&val](value_type& elem) { new (&elem) value_type(val); });
	}

	vec(const vec<value_type>& other) {
		get_memory(other.size_used);
		uninitialized_copy_n(other.data, other.size_used, data);
	}

	vec(vec<value_type>&& other) : size_used(other.size_used), capacity_(other.capacity_),
		data(other.data) {
		other.size_used = 0;
		other.capacity_ = 0;
		other.data = nullptr;
		swap_(*this, other);
	}

	vec(const std::vector<value_type>& other) {
		get_memory(other.size());
		uninitialized_copy_n(other.begin(), other.size(), data);
	}

	explicit operator std::vector<value_type>() const {
		return vector<value_type>(data, data + size_used);
	}

	~vec() noexcept {
		for_each_n(data, size_used, [](const value_type& elem) { elem.~value_type(); });
		operator delete[](data);
	}

	vec<value_type>& operator=(const vec<value_type>& other) {
		vec<value_type> temp(other);
		swap_(*this, temp);
		return *this;
	}

	vec<value_type>& operator=(vec<value_type>&& other) noexcept {
		this->~vec();
		size_used = 0;
		capacity_ = 0;
		data = nullptr;
		swap_(*this, other);
		return *this;
	}

	template <typename Q>
	friend void swap_(vec<Q>&, vec<Q>&);

	void resize(size_type sz)
	{
		reserve(sz * 2);
		while (sz < size_used) {
			--size_used;
			pop_back();
		}
		while (sz > size_used) {
			++size_used;
			push_back(value_type());
		}
	}

	void reserve(size_type cap)
	{
		if (cap <= capacity_)
			return;
		vec<value_type> new_vec;
		new_vec.~vec();
		new_vec.get_memory(size_used, cap);
		uninitialized_copy_n(new_vec.data, size_used, data);
		swap_(*this, new_vec);
	}

	size_type size() const
	{
		return size_used;
	}

	size_type capacity() const
	{
		return capacity_;
	}

	void push_back(const_reference val)
	{
		if (size_used < capacity_) {
			new (data + size_used) value_type(val);
			++size_used;
			return;
		}
		reserve(size_used * 2);
		push_back(val);
	}

	void pop_back()
	{
		--size_used;
		(data + size_used)->~value_type();
	}

	reference operator[](size_type i) {
		return data[i];
	}

	const_reference operator[](size_type i) const {
		return data[i];
	}

	value_type* cbegin()
	{
		return data;
	}

	value_type* cend()
	{
		return data + size_used;
	}

	bool empty() const
	{
		return !size_used;
	}
	// emplace, etc.
private:
	value_type* data;
	size_type capacity_;
	size_type size_used;

	static const size_type default_init_capacity = INITIAL_SIZE;
};

template <typename Q>
void swap_(vec<Q>& v1, vec<Q>& v2)
{
	swap(v1.size_used, v2.size_used);
	swap(v1.capacity_, v2.capacity_);
	swap(v1.data, v2.data);
}

template <typename T>
bool operator==(vec<T>& v1, vec<T>& v2)
{
	return v1.size() == v2.size() && v1.capacity() == v2.capacity() && equal(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
}

/*
	Algorithmic Problems
*/

struct sol_unique_paths_with_obstacles
{
	int unique_paths_with_obstacles(vec<vec<int>>& grid)
	{
		size_t n = grid.size(), m = grid[0].size(), i, j;
		vec<vec<int>> dp(n, vec<int>(m));
		dp[0][0] = grid[0][0] ^ 1;
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++i) {
				if (grid[i][j])
					continue;
				if (i != 0)
					dp[i][j] += dp[i - 1][j];
				if (j != 0)
					dp[i][j] += dp[i][j - 1];
			}
		return dp[n - 1][m - 1];
	}
};
