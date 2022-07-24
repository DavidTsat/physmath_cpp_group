#pragma once
#include <new>

#include <iostream>

#define default_size 10

#define default_size 20

using namespace std;

template <typename T>

class _stack
{
public:
	using value_type = T;
	using size_type = size_t;
	using reference = T&;
	using const_reference = const T&;
private:
	size_type capacity;
	size_type size_used;
	value_type* data;

	void copy_data(value_type* src, value_type* dst, size_type sz) // uninitialized copy
	{
		size_type i = 0;
		try
		{
			for (; i < sz; ++i)
			{
				new (&dst[i]) value_type(src[i]);
				if (i == 5)
					throw 7;
			}
		} 
		catch (...)
		{
			for (size_type j = 0; j < i; ++j)
			{
				dst[j].~value_type();
			}
			operator delete[](dst);
			throw;
		}
	}

	void grow_stack()
	{
		// QUESTION
		capacity *= 2;
		//cout << capacity << " : ";
		value_type* new_data = (value_type*) operator new[](capacity * sizeof(value_type));
		copy_data(data, new_data, size_used); // QUESTION
		this->~_stack();
		data = new_data;
	}
public:
	_stack() : capacity(default_size), size_used(0), data((value_type*)operator new[](capacity * sizeof(value_type))) { }
	
	~_stack() noexcept
	{
		for (size_type i = 0; i < size_used; ++i)
			data[i].~value_type();

	//	cout << endl<< "sz: " << size_used << endl;
		
		operator delete[](data);
	}
	
	_stack(const _stack& s) : size_used(s.size_used)/*QUESTION size_used(s.size_used)*/, capacity(s.capacity), data((value_type*) operator new[](capacity * sizeof(value_type)))
	{
		copy_data(s.data, data, size_used);
	}
	
	_stack(_stack&& s) noexcept : size_used(0), capacity(0), data((value_type*) operator new[](capacity * sizeof(value_type)))
	{
		swap(*this, s);
	}
	
	_stack& operator=(const _stack& s)
	{
		if (this != &s)
		{
			value_type* new_data = ((value_type*) operator new[](s.capacity * sizeof(value_type)));
			copy_data(s.data, new_data, s.size_used);
			this->~_stack();
			data = new_data;
			size_used = s.size_used;
			capacity = s.capacity;
		}

		return *this;
	}
	
	_stack& operator=(_stack&& s) noexcept
	{
		swap(*this, s);
		return *this;
	}

	reference top()
	{
		return data[size_used - 1];
	}
	
	const_reference top() const
	{
		return data[size_used - 1];
	}

	bool empty() const
	{
		return !size_used;
	}
	
	size_type size() const
	{
		return size_used;
	}
	
	void push(const_reference v)
	{
		if (size_used == capacity)
		{
			grow_stack();
		}
		new (&data[size_used]) value_type(v);
		++size_used; // QUESTION
	}

	template <typename... Args>
	void emplace(Args&&... args)
	{
		if (size_used == capacity)
		{
			grow_stack();
		}
		new (&data[size_used]) value_type(forward<Args>(args)...);
		++size_used; // QUESTION
	}
	
	void pop()
	{
		// QUESTIONSSSSSSSSSS
		// TO ADDD
		data[size_used-1].~value_type();
		--size_used;
	}
	
	void swap(_stack& s) noexcept
	{
		std::swap(data, s.data);
		std::swap(size_used, s.size_used);
		std::swap(capacity, s.capacity);
	}
};