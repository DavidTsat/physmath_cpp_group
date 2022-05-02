#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <sstream>
#include <assert.h>

using namespace std;

string short_to_binary_string(short x)
{
	bitset<sizeof(x)*8> b(x);
	return b.to_string();
}

unsigned binary_string_to_int(string s)
{
	bitset<sizeof(unsigned)*8> b(s);
	return b.to_ulong();
}


// implement a std::bit_set like class bset https://en.cppreference.com/w/cpp/utility/bitset
// the difference from the std::bit_set is that our bset is based on std::vector<char> hence it's size can be determined run-time not only compile-time but the size of our bset will be larger than std::bitset
class bset
{
	vector<char> v;

public:
	bset() = default;
	bset(unsigned x)
	{
		//...
	}

	bset(string s)
	{
		std::copy(s.cbegin(), s.cend(), back_inserter(v));
	}

	unsigned to_unsigned() const
	{
		//...
	}

	string to_string() const
	{
		//...
	}

	char& operator[](unsigned i)
	{
		//...
	}

	const char& operator[](unsigned i) const
	{
		//...
	}

	bool operator==(const bset& b) const
	{
		//...
	}
	bool any() const
	{
		for (char c : v)
		{
			if (c == '1')
				return true;
		}
		return false;
	}

	bool all() const
	{
		for (char c : v)
		{
			if (c == '0')
				return false;
		}
		return true;
	}

	size_t count() const
	{
	   // ....
	}

	size_t size() const
	{
		return v.size();
	}

	friend ostream& operator<<(ostream& os, const bset& b);

	/*
	* logical operators
	*/

	bset& operator&=(const bset& b)
	{
		assert(size() == b.size());
		// ...
	}
	// implement operators |=, ^=, ~
	

	bset operator<<(std::size_t pos) const
	{
		unsigned d = this->to_unsigned();
		d <<= pos;
		return d;
	}

	bset& operator>>=(std::size_t pos)
	{
		
	}
};

ostream& operator<<(ostream& os, const bset& b)
{
	//...
}

bset operator^(const bset& b1, const bset& b2)
{
	//...
}

int main()
{
	return 0;
}