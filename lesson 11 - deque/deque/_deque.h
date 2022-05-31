#pragma once
#include <new>
#include <assert.h>

using namespace std;

template <typename T>
class _deque
{
public:
	using value_type		= T;
	using reference			= value_type&;
	using const_reference	= const reference;
	using size_type			= size_t;
	using diff_type			= ptrdiff_t;

	class _deque_iterator
	{
		friend class _deque;

		value_type** map_ptr;
		value_type* first;
		value_type* current;
		value_type* last;

		void advance(diff_type n)
		{
		//	if (n == 0) return;
			diff_type chunk_size = last - first;
			n += current - first;

			current = first;

			diff_type map_offset;
			if (n > 0)
			{
				map_offset = n / chunk_size;
			}
			else
			{
				map_offset = -(chunk_size - 1 - n) / chunk_size; // -1
			}

			diff_type chunk_offset = n - chunk_size * map_offset;

			map_ptr += map_offset;
			first = *map_ptr;
			current = first + chunk_offset;
			last = first + chunk_size;
		}
	public:
		_deque_iterator& operator++()
		{
			advance(1);
			return *this;
		}
		_deque_iterator& operator--()
		{
			advance(-1);
			return *this;
		}
		_deque_iterator operator+(size_type n) const
		{
			_deque_iterator t(*this);
			t.advance(n);
			return t;
		}
		_deque_iterator operator-(size_type n) const
		{
			_deque_iterator t(*this);
			t.advance(-n);
			return t;
		}
		diff_type operator-(const _deque_iterator& d)
		{	
			if (map_ptr == d.map_ptr) return current - d.current;
			diff_type chunk_size = last - first;
			diff_type map_dist = (map_ptr - d.map_ptr) - 1;

			return map_dist * chunk_size + current - first + d.last - d.current;
		}

		bool operator==(const _deque_iterator& d2) const
		{
			return current == d2.current;
		}
		bool operator!=(const _deque_iterator& d2) const
		{
			return current != d2.current;
		}
		reference operator*()
		{
			return *current;
		}
	};

	_deque(size_type size = 0, const value_type& v = value_type()) : map_size(min_map_size), chunk_size(size / map_size + 1), map_head(allocate_map(map_size)) 
	{
		for (size_type i = 0; i < map_size; ++i)
		{
			map_head[i] = allocate_chunk(chunk_size);
		}
		
		set_begin(size);
		set_end(size);

		assert(_end - _begin == size);
		initialize_data(_begin, _end, v);
	}

	~_deque() 
	{
		while (_begin != _end)
		{
			(*_begin).~value_type();
			++_begin;
		}
		for (size_type i = 0; i < map_size; ++i)
		{
			operator delete (map_head[i]);
		}
		delete[] map_head;
	}

	void push_back(const value_type& v)
	{

	}
	void pop_back()
	{

	}

	void push_front(const value_type& v)
	{
		if (_begin.current > _begin.first || _begin.map_ptr > map_head)
		{
			--_begin;
			new(&*_begin) value_type(v);
		}
		else
		{
			value_type* new_chunk = allocate_chunk(chunk_size);
			++map_size;
			value_type** new_map = allocate_map(map_size);
			size_type n = size_used();
			
			new_map[0] = new_chunk;
			for (size_type i = 1; i < map_size; ++i)
			{
				new_map[i] = map_head[i - 1];
			}
			delete[] map_head;
			map_head = new_map;

			set_to_begin(_begin);
			_begin.advance(chunk_size);
			//set_begin(n);
			//set_end
			push_front(v);
		}
	}
	void pop_front()
	{

	}

	_deque_iterator begin()
	{
		return _begin;
	}
	_deque_iterator end()
	{
		return _end;
	}
	_deque_iterator _begin;
	_deque_iterator _end;

private:
	size_type map_size;
	const size_type chunk_size;
	value_type** map_head;

	const static size_type min_map_size = 8;
private:
	constexpr size_type size_used() 
	{
		return _end - _begin;
	}
	constexpr size_type capacity() const
	{
		return chunk_size * map_size;
	}
	value_type** allocate_map(size_type size) const
	{
		return new value_type* [size];
	}
	value_type* allocate_chunk(size_type size) const
	{
		return (value_type*) operator new(size * sizeof(value_type));
	}

	void set_to_begin(_deque_iterator& d)
	{
		d.map_ptr	= map_head;
		d.first		= *d.map_ptr;
		d.current	= d.first;
		d.last		= d.first + chunk_size;
	}

	void set_begin(size_type n)
	{
		set_to_begin(_begin);
		size_type offset = (capacity() - n) / 2;
		_begin.advance(offset);
	}
	void set_end(size_type n)
	{
		_end = _begin + n;
	}
	void initialize_data(_deque_iterator first, _deque_iterator last, const value_type& v)
	{
		while (first != last)
		{
			new (&*first) value_type(v);
			++first;
		}
	}
};