#pragma once
#include "_stack.h"
#include <iostream>

using namespace std;

struct C
{
    int a;
    bool b;
    char c;

    C(int _a, bool _b, char _c) : a(_a), b(_b), c(_c) { cout << "S::C()\n"; }
    C(const C& _c) : a(_c.a), b(_c.b), c(_c.c) { cout << "C(const C& _c)\n"; }
};

void f(_stack<C>& s)
{
    //...
    C c = s.pop2(); // basic, but no strong
    //...

    // strong
    C c2 = s.top(); // thread-safe
    s.pop();

}

#include <vector>
#include <string>

template <typename It>
void f(It first, It last, vector<C>& v)
{
    //basic
    while (first != last)
    {
        v.push_back(*first++);
    }
}

template <typename It>
void f2(It first, It last, vector<C>& v)
{
    //strong
    // copy and swap 
    vector<C> v2(v);
    while (first != last)
    {
        v2.push_back(*first++);
    }

    v.swap(v2);  // noexcept
}

/*
  new/delete . new A[100]; //initialized
  operator new/operator delete // uninitialized. placement new
*/

void test1()
{
    _stack<string> s;
    for (int i = 0; i < 99; ++i)
    {
        s.push(to_string(i) + "abc");
        if (i % 7 == 0)
            s.pop();
    }

    cout << s.size() << endl;
    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
}

void test2()
{
    _stack<C> s;
    //s.push({4,true, 'c'});
    s.emplace(4, true, 'c');
}

void test3()
{
    _stack<string> s;
    for (int i = 0; i < 99; ++i)
    {
        s.push(to_string(i) + "abc");
        if (i % 7 == 0)
            s.pop();
    }

    try
    {
        _stack<string> s2(s);
        cout << s2.size();
    }
    catch (...)
    {
        cout << "catch\n";
    }
}