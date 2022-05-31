#pragma once
#include <new>
#include <assert.h>
#include <iostream>

using namespace std;

template<typename T>
class deque_ {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using diff_type = ptrdiff_t;

    class _deque_iterator
    {
        friend class deque_;

        value_type** map_ptr;
        value_type* chunk_begin;
        value_type* chunk_current;
        value_type* chunk_end;

        void advance(diff_type n)
        {
            if (n == 0) return;
            diff_type chunk_size = chunk_end - chunk_begin;
            n += chunk_current - chunk_begin;

            chunk_current = chunk_begin;

      
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
            chunk_begin = *map_ptr;
            chunk_current = chunk_begin + chunk_offset;
            chunk_end = chunk_begin + chunk_size;
        }

    public:
        _deque_iterator& operator++() {
            advance(1);
            return *this;
        }

        _deque_iterator operator++(int) { //postfix
            _deque_iterator temp(*this);
            advance(1);
            return *this;
        }

        _deque_iterator& operator--() {
            advance(-1);
            return *this;
        }

        _deque_iterator operator--(int) { //postfix
            _deque_iterator temp(*this);
            advance(-1);
            return *this;
        }

        _deque_iterator operator+(size_type n) const {
            _deque_iterator temp(*this);
            temp.advance(n);
            return temp;
        }

        bool operator==(const _deque_iterator& other)  const {
            return chunk_current == other.chunk_current;
        }

        bool operator!=(const _deque_iterator& other)  const {
            return chunk_current != other.chunk_current;
        }

        diff_type operator-(const _deque_iterator& other) const {
            //_end - _begin
            if (map_ptr == other.map_ptr) return chunk_current - other.chunk_current;

            diff_type map_diff = (map_ptr - other.map_ptr - 1) * (chunk_end - chunk_begin);

            return map_diff + chunk_current - chunk_begin + other.chunk_end - other.chunk_current;
        }

        value_type* operator->()
        {
            return addressof(*chunk_current);
        }
        reference operator*()
        {
            return *chunk_current;
        }
    };

    deque_(size_type n = 0, const_reference v = value_type()) : map_size(default_map_size),
        chunk_size(n / map_size + 1), map_head(allocate_map(map_size))
    {
        for (size_type i = 0; i < map_size; ++i)
        {
            map_head[i] = allocate_chunk();
        }

        set_begin(n);
        set_end(n);

        assert(_end - _begin == n);

        initialize_data(_begin, _end, v);
    }

    ~deque_()
    {
        int i = 0;
        while (_begin != _end)
        {
          //  cout << ++i;
            //_begin->~value_type();
            (*_begin).~value_type();
            ++_begin;
        }
        
        for(size_type i = 0;i<map_size;++i)
            operator delete[](map_head[i]);

        delete[] map_head;
    }

    void push_front(const_reference v)
    {
        if (_begin.chunk_current != _begin.chunk_begin || _begin.map_ptr != map_head) {
            --_begin;
            new (&*_begin) value_type(v);
            return;
        }

        value_type** new_map = allocate_map(++map_size);
        for (size_type i = 1; i < map_size; ++i)
        {
            new_map[i] = map_head[i - 1];
        }
        
        delete[] map_head;

        map_head = new_map;
        map_head[0] = allocate_chunk();
        set_to_map_begin(_begin);
        _begin.advance(chunk_size);
        //todo -end_
        push_front(v);
    }

    void pop_front()
    {

    }

    _deque_iterator begin() const
    {
        return _begin;
    }
    _deque_iterator end() const
    {
        return _end;
    }

private:
    size_type map_size;
    const size_type chunk_size;
    value_type** map_head;

    _deque_iterator _begin;
    _deque_iterator _end;

    static const size_type default_map_size = 8;
private:

    size_type size() const
    {
        return _end - _begin;
    }

    size_type capacity() const
    {
        return map_size * chunk_size;
    }

    value_type** allocate_map(size_t map_sz) const
    {
        return new value_type * [map_sz];
    }
    value_type* allocate_chunk() const
    {
        return (value_type*) operator new[](chunk_size * sizeof(value_type));
    }

    void set_to_map_begin(_deque_iterator& d)
    {
        d.map_ptr = map_head;
        d.chunk_begin = *d.map_ptr;
        d.chunk_current = d.chunk_begin;
        d.chunk_end = d.chunk_begin + chunk_size;
    }
    void set_begin(size_type n)
    {
        set_to_map_begin(_begin);
        // TODO
        _begin.advance((capacity() - n) / 2);
    }
    void set_end(size_type n)
    {
        set_to_map_begin(_end);
        _end = _begin + n;
    }

    void initialize_data(_deque_iterator first, _deque_iterator second, const_reference val)
    {
        while (first != second) {
            new (&*first) value_type(val); //placement new 
            ++first;
        }
    }
};