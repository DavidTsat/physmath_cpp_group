#pragma once
#include <iostream>
#include <iterator>
#include <assert.h>
#include <algorithm>
#include <string>

using namespace std;

#define DEFAULT_M 17

template <class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
class _unordered_map
{
    // hash: h(k) -> {0, 1, 2, ..., m - 1} // deterministic
    /*
    k1 != k2; h(k1) == h(k2) // collision
    // birthday paradox
    // randomness -> uniform distribution. p(h(k) == i) = 1/m
    */
    /*
    m = 10
    k1 = 7
    k2 = 17
    h(k1) = 7
    h(k2) = 17%10 = 7

    k mod m; if m == 2^p; h(k) == last p bits of k
    1/p*k*(m-1)
    k*k 3 digits from middle
    multiplicative hash:
    h(k) = [m (kA mod 1)]; A: [0, 1); A = s/(2^w)
    h(k) = k*k*k,
    A = (sqrt(5) - 1)/2 = 0.618...
    */
    /*
    h(k) choice
    growing factor/max_load/load_factor
  */

public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = pair<const Key, T>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using reference = value_type&;
    using const_reference = const value_type&;
private:
    struct node {
        value_type val;
        node* left, * right;

        node(const_reference _val, node* _left = nullptr, node* _right = nullptr) : val(_val), left(_left),
            right(_right) {}

    };

    size_type sz;
    node** data;
    size_type m; //bucket_count
    hasher h;
    key_equal ke;
    float max_load_factor = 2.;

public:
    class iterator : public std::iterator<bidirectional_iterator_tag, value_type> {
        friend class _unordered_map<key_type, mapped_type, hasher, key_equal>;
        // forward ++, bidirectional ++/-- and random_access ++/--/+/-

        node** _list;
        node* curr;
        //curr == *_list + id
    public:
        iterator(node** list_, node* curr_) : _list(list_), curr(curr_) {}

        reference operator*()
        {
            return curr->val;
        }

        value_type* operator->()
        {
            return &curr->val;
        }

        iterator& operator++()
        {
            if (curr->right)
                curr = curr->right;
            else {
                /*
                curr = *++_list;
                while (!curr)
                {
                  ++_list;
                  curr = *_list;
                }
                */
                while (!*(++_list));
                curr = *_list;
            }
            return *this;
        }

        iterator& operator--()
        {
            if (curr == *(_list) || !(curr->left)) {
                while (!*(--_list));
                curr = *_list;
                while (curr->right) curr = curr->right;
            }
            else
                curr = curr->left;
            return *this;
        }

        bool operator==(const iterator& other) const
        {
            return curr == other.curr;
        }

        bool operator!=(const iterator& other) const
        {
            return curr != other.curr;
        }
    };

    class const_iterator : public std::iterator<bidirectional_iterator_tag, value_type> {
        friend class _unordered_map<key_type, mapped_type, hasher, key_equal>;
        // forward ++, bidirectional ++/-- and random_access ++/--/+/-

        node** _list;
        node* curr;
        //curr == *_list + id
    public:
        const_iterator(node** list_, node* curr_) : _list(list_), curr(curr_) {}

        const_reference operator*() const
        {
            return curr->val;
        }

        const value_type* operator->() const
        {
            return &curr->val;
        }

        const_iterator& operator++()
        {
            if (curr->right)
                curr = curr->right;
            else {
                while (!*(++_list));
                curr = *_list;
            }
            return *this;
        }

        const_iterator& operator--()
        {
            if (curr == *(_list) || !(curr->left)) {
                while (!*(--_list));
                curr = *_list;
                while (curr->right) curr = curr->right;
            }
            else
                curr = curr->left;
            return *this;
        }

        bool operator==(const const_iterator& other) const
        {
            return curr == other.curr;
        }

        bool operator!=(const const_iterator& other) const
        {
            return curr != other.curr;
        }
    };

    _unordered_map() : sz(0), data(new node* [DEFAULT_M]()), m(DEFAULT_M),
        h(hasher()), ke(key_equal()) {}

    _unordered_map(const _unordered_map& other) : sz(0), data(new node* [other.m]()), m(other.m), h(other.h), ke(other.ke) {
        for (const_iterator it = other.cbegin(); it != other.cend(); ++it) {
            this->operator[](it->first) = it->second;
        }
    }

    void swap(_unordered_map& other) noexcept {
        std::swap(this->h, other.h);
        std::swap(this->m, other.m);
        std::swap(this->sz, other.sz);
        std::swap(this->ke, other.ke);
        std::swap(this->data, other.data);
    }

    _unordered_map(_unordered_map&& other) : _unordered_map() {
        swap(this, other);
    }

    _unordered_map& operator=(const _unordered_map& other) {
        // copy and swap idiom
        _unordered_map a(other);
        this->swap(a);
        return *this;
    }

    _unordered_map& operator=(_unordered_map&& other) noexcept {
        this->swap(other);
        return *this;
    }

    ~_unordered_map() {
        for (iterator it = begin(); it != end();) {
            iterator it2 = next(it);
            delete(it.curr);
            it = it2;
        }
        delete[] data;
    }

    mapped_type& operator[](const Key& k)
    {
        size_type ind = h(k) % m;
        if (data[ind] == nullptr) {
            data[ind] = new node(value_type(k, mapped_type()));
            ++sz;
            return data[ind]->val.second;
        }

        for (node* it = data[ind]; it->right; it = it->right)
            if (ke(k, it->val.first))
                return it->val.second;

        node* new_elem = new node(value_type(k, mapped_type()), nullptr, data[ind]);
        // TODO if load_factor >= max_load_factor rehash
        ++sz;
        data[ind]->left = new_elem;
        data[ind] = new_elem;
        return new_elem->val.second;
    }

    iterator find(const key_type& k)
    {
        size_type ind = h(k) % m;
        if (data[ind] == nullptr)
            return end();
        for (node* it = data[ind]; it->right; it = it->right)
            if (ke(k, it->val.first))
                return { data + ind, it };
        return end();
    }

    void erase(iterator it)
    {
        node** a = it._list;
        node* p = it.curr;
        if (p->left) {
            (p->left)->right = p->right;
        }
        else {
            *a = p->right;
        }

        if (p->right) {
            (p->right)->left = p->left;
        }
        --sz;
        delete p;
    }

    iterator begin()
    {
        if (sz == 0)
            return end();

        for (size_type i = 0; i < m; ++i)
        {
            if (data[i] != nullptr)
                return { &data[i], data[i] };
        }

        return end();
    }

    iterator end()
    {
        return { data + m, *(data + m) };
    }

    const_iterator cend() const
    {
        return { data + m, *(data + m) };
    }

    const_iterator cbegin() const
    {
        if (sz == 0)
            return cend();

        for (size_type i = 0; i < m; ++i)
        {
            if (data[i] != nullptr)
                return { &data[i], data[i] };
        }

        return cend();
    }

    float load_factor() const
    {
        return (float)sz / m;
    }

    size_type size() const
    {
        return sz;
    }

    void reserve(size_type count)
    {
        // TODO
    }
    
    void max_load_factor(float ml)
    {

    }

    bool operator==(const _unordered_map& other) const {
        /*
        1 2 3 4
        4 3 2 1
        */

        return sz == other.sz && m == other.m
            && std::equal(cbegin(), cend(), other.cbegin()); // TODO

          // to add ke and h
    }

    size_type bucket(const key_type& key) const
    {

    }
    
    size_type bucket_size(size_type n) const
    {

    }

    size_type max_bucket_count() const
    {

    }
};