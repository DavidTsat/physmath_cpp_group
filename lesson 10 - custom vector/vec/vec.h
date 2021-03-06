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
	
	// TODO
	vec()
	explicit vec(size_type);
	vec(size_type, const value_type&);
	vec(const vec<value_type>&);
	vec(const vec<value_type>&&);
	vec(const std::vector<value_type>&);
	explicit operator std::vector<value_type>() const;
	~vec() noexcept;
	vec<value_type>& operator=(const vec<value_type>&);
	vec<value_type>& operator=(vec<value_type>&&) noexcept;
	template <typename Q>
	friend void swap_(vec<Q>&, vec<Q>&);
	void resize(size_type);
	void reserve(size_type);
	size_type size() const;
	size_type capacity() const;
	void push_back(const value_type&);
	void pop_back();
	reference operator[](size_type);
	const_reference operator[](size_type);
	value_type* cbegin();
	value_type* cend();
	bool empty() const;
	// emplace, etc.
private:
	value_type* data;
	size_t capacity_;
	size_t size_used;

	static const size_type default_init_capacity = INITIAL_SIZE;
};

template <typename Q>
void swap_(vec<Q>& v1, vec<Q>& v2)
{
	// TODO
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
		// TODO
		// don't use std::vectors inside, only vec
		return 0;
	}
};