#include <iostream>
#include <algorithm>

template <size_t N>
class array_
{
	size_t sz;
	int arr[N];
public:
	using reference = int&;
	using const_reference = const int&;

	using iterator = int*;
	using const_iterator = const int*;

	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	array_() : arr{} {}

	array_(std::initializer_list<int> l) : arr{ 0 }
	{
		for (auto it = l.begin(); it != l.end(); ++it)
		{
			arr[std::distance(l.begin(), it)] = *it;
		}
		sz = std::distance(l.begin(), l.end());
	}

	array_& operator=(const array_& other)
	{
		for (int i = 0; i < N; ++i)
			arr[i] = other.arr[i];
		return *this;
	}

	template <size_t N>
	friend std::ostream& operator<<(std::ostream& os, const array_<N>& arr_);

	iterator begin() noexcept
	{
		return arr;
	}

	iterator end() noexcept
	{
		return arr + sz; //why sz and not N?
	}

	const_iterator cbegin() const noexcept
	{
		return arr;
	}

	const_iterator cend() const noexcept
	{
		return arr + sz;
	}

	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend() noexcept
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator crbegin() const noexcept
	{
		return const_reverse_iterator(cend());
	}

	const_reverse_iterator crend() const noexcept
	{
		const_reverse_iterator(cbegin());
	}

	reference at(size_t pos)
	{
		if (pos >= N)
			throw std::out_of_range("given pos to at() is bigger than array size");
		return *(arr + pos);
	}

	const_reference at(size_t pos) const
	{
		if (pos >= N)
			throw std::out_of_range("given pos to at() is bigger than array size");
		return *(arr + pos);
	}

	reference operator[](size_t pos)
	{
		return *(arr + pos);
	}

	const_reference operator[](size_t pos) const
	{
		return *(arr + pos);
	}

	reference front()
	{
		return arr[0];
	}

	const_reference front() const
	{
		return arr[0];
	}

	reference back()
	{
		return arr[N - 1];
	}

	const_reference back() const
	{
		return arr[N - 1];
	}

	int* data() noexcept
	{
		return arr;
	}

	const int* data() const noexcept
	{
		return arr;
	}

	void swap(array_& other) noexcept
	{
		for (int i = 0; i < N; ++i)
			std::swap(arr[i], other[i]);
	}
};

template <size_t N>
std::ostream& operator<<(std::ostream& os, const array_<N>& arr_)
{
	std::copy(arr_.cbegin(), arr_.cend(), std::ostream_iterator<int>(os));
	return os;
}

template<size_t N>
constexpr array_<N> to_array_(int(&a)[N])
{
	array_<N> arr;
	for (int i = 0; i < N; ++i)
		arr[i] = a[i];
	return arr;
}
