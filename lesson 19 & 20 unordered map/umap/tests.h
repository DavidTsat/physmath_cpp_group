#pragma once
#include "umap.h"
#include <iostream>
#include <assert.h>

void test1()
{
    _unordered_map<int, string> m;
    m[14] = "sdfsd";
    m[7] = "woek";
    m[74] = "pklfowdk";
    m[856] = "sdfsdfasd";

    for (_unordered_map<int, string>::iterator it = m.begin(); it != m.end(); ++it)
    {
        cout << it->first << " : " << it->second << endl;
    }
    cout << endl;
    for (_unordered_map<int, string>::iterator it = --(m.end()); it != m.begin(); --it)
    {
        cout << it->first << " : " << it->second << endl;
    }

}

void test2()
{
    _unordered_map<string, int> m;

    for (int i = 0; i < 200; ++i)
    {
        m["abc" + to_string(i)] = i;
    }

    for (_unordered_map<string, int>::iterator it = m.begin(); it != m.end();)
    {
        _unordered_map<string, int>::iterator it1 = next(it);
        m.erase(it);
        it = it1;
        assert(distance(m.begin(), m.end()) == m.size());
        //   cout << m.load_factor() << endl;
    }
}

void test3()
{
    _unordered_map<string, int> m;

    for (int i = 0; i < 200; ++i)
    {
        m["abc" + to_string(i)] = i;
    }

    _unordered_map<string, int> m2(m);

    // assert(m == m2);

    assert(m.size() == m2.size());
    assert(m.load_factor() == m2.load_factor());
    assert(distance(m.cbegin(), m.cend()) == distance(m2.cbegin(), m2.cend()));
}

#include <unordered_map>
#include <string>

void test_std_umap()
{
    unordered_map<string, int> m;
    m.reserve(1000000);

    //  m.max_load_factor(100);

    cout << m.bucket_count() << endl;
    cout << m.max_load_factor() << endl; // 1

    cout << m.load_factor() << endl; // size/bucket_count

    for (int i = 0; i < 200; ++i)
    {
        m["abc" + to_string(i)] = i;
        /*
          max_load_factor 1
          m = 10
          k1 = 7; h(k1) == 7
          k2 = 17; h(k2) == 7
          m = 20
          h(k1) = 7
          h(k2) = 17
        */

        // if load_factor >= max_load_factor rehash
    }

    cout << endl;
    cout << m.bucket_count() << endl; // vector size
    cout << m.max_load_factor() << endl;
    cout << m.load_factor() << endl;
}

/*
to add tests on swap, move ctor, copy/move assignment operator
*/