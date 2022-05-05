#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

template <size_t N>
class array_
{
	size_t sz;
	int arr[N];
public:
	using iterator = int*;
	using const_iterator = const int*;

	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	array_(std::initializer_list<int> l) : arr{ 0 }
	{
		for (auto it = l.begin(); it != l.end(); ++it)
		{
			arr[std::distance(l.begin(), it)] = *it;
		}
		sz = distance(l.begin(), l.end());
 	}

	template <size_t N>
	friend std::ostream& operator<<(std::ostream& os, const array_<N>& arr_);

	iterator begin() noexcept
	{
		return arr;
	}

	iterator end() noexcept
	{
		return arr + sz;
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
		//...
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
		//...
	}

	//implement  at, operator[], front, back, data, swap, to_array, operator= (assignment operator)
};

template <size_t N>
std::ostream& operator<<(std::ostream& os, const array_<N>& arr_)
{
	std::copy(arr_.cbegin(), arr_.cend(), std::ostream_iterator<int>(os));
	return os;
}

int main()
{
	
	return 0;
}