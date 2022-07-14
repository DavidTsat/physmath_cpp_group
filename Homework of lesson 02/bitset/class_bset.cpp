#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <assert.h>

// this is std::bit_set like class bset https://en.cppreference.com/w/cpp/utility/bitset
// the difference from the std::bit_set is that our bset is based on std::vector<char> hence it's size can be determined run-time not only compile-time but the size of our bset will be larger than std::bitset
class bset
{
	std::vector<char> v;

public:
	bset() = default;
	bset(unsigned x)
	{
		unsigned i = 1;
		while (i > 0) {
			v.push_back(x & i ? '1' : '0');
			i <<= 1;
		}
		v.push_back(x & i ? '1' : '0');
	}
	bset(std::string s)
	{
		std::copy(s.cbegin(), s.cend(), back_inserter(v));
	}

	void push_left(char c)
	{
		if (c != '0' & c != '1')
			throw std::invalid_argument("only '0' and '1' can be pushed to bset");
		v.push_back(c);
	}

	unsigned to_unsigned() const
	{
		unsigned ans = 0, i = 1, ind = 0, unsignedsz = sizeof(unsigned) << 3;
		for (const char& c : v) {
			if (c == '1')
				if (ind >= unsignedsz)
					throw std::overflow_error("bset can't be represented in unsigned");
				else
					ans |= i;
			i <<= 1;
			++ind;
		}
		return ans;
	}

	std::string to_string() const
	{
		return std::string(v.rbegin(), v.rend());
	}

	char& operator[](unsigned i)
	{
		return v[i];
	}

	const char& operator[](unsigned i) const
	{
		return v[i];
	}

	bool operator==(const bset& b) const
	{
		size_t sz = size();
		if (sz < b.size())
			for (size_t i = sz; i < b.size(); ++i)
				if (b[i] == '1')
					return false;
		if (sz > b.size()) {
			for (size_t i = b.size(); i < sz; ++i)
				if (v[i] == '1')
					return false;
			sz = b.size();
		}
		for (size_t i = 0; i < sz; ++i)
			if (v[i] != b[i])
				return false;
		return true;
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
		size_t cnt = 0;
		for (const char& c : v)
			if (c == '1')
				++cnt;
		return cnt;
	}

	size_t size() const
	{
		return v.size();
	}

	friend std::ostream& operator<<(std::ostream& os, const bset& b);

	/*
	* logical operators
	*/

	bset& operator&=(const bset& b)
	{
		assert(size() == b.size());
		for (size_t i = 0; i < size(); ++i)
			v[i] = ((v[i] - '0') & (b[i] - '0')) + '0';
		return *this;
	}

	bset& operator|=(const bset& b)
	{
		assert(size() == b.size());
		for (size_t i = 0; i < size(); ++i)
			v[i] = ((v[i] - '0') | (b[i] - '0')) + '0';
		return *this;
	}

	bset& operator^=(const bset& b)
	{
		assert(size() == b.size());
		for (size_t i = 0; i < size(); ++i)
			v[i] = ((v[i] - '0') ^ (b[i] - '0')) + '0';
		return *this;
	}

	bset operator~()
	{
		bset b;
		for (const char& c : v)
			b.push_left(c == '1' ? '0' : '1');
		return b;
	}

	bset operator<<(std::size_t pos) const
	{
		unsigned d = this->to_unsigned();
		d <<= pos;
		return d;
	}

	bset& operator>>=(std::size_t pos)
	{
		for (size_t i = 0; i < size(); ++i)
			if (i + pos < size())
				v[i] = v[i + pos];
			else
				v[i] = 0;
		return *this;
	}
};

std::ostream& operator<<(std::ostream& os, const bset& b)
{
	for (size_t i = b.size() - 1; i > 0; --i)
		os << b[i];
	return os << b[0];
}

bset operator^(const bset& b1, const bset& b2)
{
	bset b = b1;
	return b ^= b2;
}