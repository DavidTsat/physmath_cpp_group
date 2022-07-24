#pragma once
#include <array>
using namespace std;

//exception-safety
// Herb Sutter - exceptional C++/more exceptional C++
/*
1. exception unsafe
2. basic guarantee - no resource leak
3. strong guarantee - basic guarantee & keeping condintion(previous state)
4. noexcept - destructor, move, swap
*/

#define DEFAULT_SIZE 150

template <class T>
class _stack
{
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using diff_type = ptrdiff_t;
private:
    size_type _size, _capacity;
    value_type* data;

    void copy_data(value_type* src, value_type* dest, size_type sz) {
        size_type i = 0;
        try {
            for (; i < sz; ++i, ++src, ++dest) {
                new (dest) value_type(*src);
                /*
                if (i == 2)
                {
                    throw 34;
                }
                */
            }
        }
        catch (...) {
            for (size_type j = 0; j < i; ++j, --dest)
                dest->~value_type();
            /*
            operator delete[] (dest);
            dest = nullptr;
            sz = 0;
            */
            throw;
        }
    }

    void grow_stack() {
        _capacity *= 2;
        value_type* data1 = (value_type*)operator new[](_capacity * sizeof(value_type));
        copy_data(data, data1, _size);
        this->~_stack();
        data = data1;
    }

public:
    _stack() : _size(0), _capacity(DEFAULT_SIZE), data((value_type*)operator new[](DEFAULT_SIZE * sizeof(value_type))) {}

    _stack(const _stack& other) : _size(other._size), _capacity(other._capacity), data((value_type*) operator new[](_capacity * sizeof(value_type))) {
        try
        {
            copy_data(other.data, data, _size);
        }
        catch (...)
        {
            operator delete[](data);
            throw;
        }
    }

    _stack& operator=(const _stack& other) {
        /*
        if(this != &other) {
          value_type* new_data = operator new[](other._capacity * sizeof(value_type));
          copy_data(other.data, new_data, other._size);
          this->~_stack();
          data = new_data;
          _size = other._size;
          _capacity = other._capacity;
        }
        */
        //copy and swap idiom
        _stack s2(other);
        this->swap(s2);
        return *this;
    }

    void swap(_stack& s) noexcept
    {
        std::swap(data, s.data);
        std::swap(_size, s._size);
        std::swap(_capacity, s._capacity);
    }

    void push(const_reference v) {
        if (_size == _capacity)
            grow_stack();
        new (data + _size) value_type(v);
        ++_size;
    }

    template<typename... Args>
    void emplace(Args&&... args)
    {
        if (_size == _capacity)
            grow_stack();
        new (data + _size) value_type(args...);
        //    new (data + _size) value_type(std::forward<Args>(args)...);
        ++_size;
    }

    ~_stack() noexcept {
        value_type* j = data;
        for (size_type i = 0; i < _size; ++i, ++j)
            j->~value_type();
        operator delete[](data);
    }

    void pop() noexcept {
        (data + (_size - 1))->~value_type();
        --_size;
    }

    reference top() {
        return *(data + (_size - 1));
    }

    const_reference top() const
    {
        return *(data + (_size - 1));
    }

    bool empty() const
    {
        return _size == 0;
    }

    size_type size() const
    {
        return _size;
    }

    value_type pop2()
    {
        value_type v = *(data + (_size - 1));
        (data + (_size - 1))->~value_type();
        --_size;
        return v;
    }
};