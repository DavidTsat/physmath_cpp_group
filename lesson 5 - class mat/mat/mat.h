#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class mat
{
	size_t M;
	size_t N;

	T** v;
public:

	mat(const vector<vector<T>>& v2) : M(v2.size()), N(v2[0].size()), v(new T* [M])
	{
		// TODO
	}

	mat(size_t m, size_t n) : M(m), N(n), v(new T* [M])
	{
		// TODO
	}

	mat(const mat<T>& m2) : M(m2.M), N(m2.N), v(new T* [M])
	{
		// TODO
	}

	~mat()
	{
		// TODO
	}

	mat& operator=(const mat&)
	{
		// TODO
	}
	mat(mat&&) noexcept
	{
		// TODO
	}
	mat& operator=(mat&&)
	{
		// TODO
	}

	template <typename F>
	void swap_(mat<F>&, mat<F>&);

	T*& operator[](size_t i)
	{
		// TODO
	}

	const T* operator[](size_t i) const
	{
		// TODO
	}

	constexpr pair<size_t, size_t> size() const
	{
		// TODO
	}

	vector<vector<T>> to_vec_of_vec() const
	{
		// TODO
	}

	template <typename T>
	mat<T> mat_mul(const mat<T>&, const mat<T>&);

	template <typename F>
	friend ostream& operator<<(ostream&, const mat<F>&);

	/*
	* Algorithmic Problems
	*/

	void rotate()
	{
		// TODO
	}

	vector<int> spiral_order() const
	{
		// TODO
	}

	int max_square() const
	{
		// TODO
	}

	int num_islands()
	{
		// TODO
	}
};

template <typename F>
ostream& operator<<(ostream& os, const mat<F>& m)
{
	// TODO
}

template <typename F>
void swap_(mat<F>&, mat<F>&)
{
	// TODO
}

template <typename T>
mat<T> mat_mul(const mat<T>&, const mat<T>&)
{
	// TODO
}

template <typename T>
mat<T> generate_spiral_mat(int n)
{
	// TODO
}