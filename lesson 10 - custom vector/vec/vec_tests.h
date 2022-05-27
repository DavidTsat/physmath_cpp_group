#pragma once
#include "vec.h"
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

std::vector<int> generate_random_vector(size_t size, int left = -1000, int right = 1000)
{
	using value_type = int;

	static uniform_int_distribution<value_type> distribution(
		left, right
	);
	static default_random_engine generator;

	vector<value_type> data(size);
	generate(data.begin(), data.end(), []() { return distribution(generator); });
	return data;
}

template <typename T>
void print_vec(const vec<T>& v)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << ' ';
	}
	cout << endl;
}

void vec_test1() // empty vec
{
	vec<int> v;

	cout << boolalpha;

//	cout << v.size() << endl;
//	cout << v.capacity() << endl;

	cout << (v.size() == 0) << endl;
	cout << (v.capacity() == INITIAL_SIZE) << endl;
}

void vec_test2() // push_back 1 test
{
	vec<string> v;
	v.push_back("ABC");
	v.push_back("DEF");
	v.push_back("GHI");
	v.push_back("JKLM");
//	print_vec(v);
	
	cout << boolalpha;
	cout << (v.size() == 4) << endl;
}

void vec_test3() // operator[] 2 test
{
	vec<string> v;
	v.push_back("ABC");
	v.push_back("DEF");
	v.push_back("GHI");

	v[2] = "ABC";
	cout << boolalpha;

	cout << (v[0] == "ABC") << endl;
	cout << (v[1] == "DEF") << endl;
	cout << (v[2] == "ABC") << endl;
}

void vec_test4() // push_back and capacity
{
	vec<size_t> v;
	for (size_t i = 0; i < v.capacity(); ++i)
	{
		v.push_back(i);
	}

//	print_vec(v);
	
	size_t sz1 = v.size();
	size_t cp1 = v.capacity();
	
	v.push_back(100);
//	print_vec(v);

	cout << boolalpha;

	cout << (v.size() == sz1 + 1) << endl;
	cout << (v.capacity() == cp1*2) << endl;
}

void vec_test5() // pop_back
{
	vec<size_t> v;
	for (size_t i = 0; i < 20; ++i)
	{
		v.push_back(i);
	}

	size_t sz1 = v.size();
	size_t cp1 = v.capacity();
	
	cout << boolalpha;

	//print_vec(v);
	v.pop_back();
	v.pop_back();
	//print_vec(v);
	cout << (v.size() == sz1 - 2) << endl;
	cout << (v.capacity() == cp1) << endl;
	v.push_back(145);
	cout << (v.size() == sz1 - 1) << endl;
	cout << (v.capacity() == cp1) << endl;
}

struct A
{
	int* p = nullptr;

	static int t;

	A() : p(new int[100]) {}
	
	A(const A& a2) : p(new int[100]) 
	{
		copy(a2.p, a2.p + 100, p);
	}
	
	A& operator=(const A& a2)
	{
		delete p;
		A temp(a2);
		p = temp.p;
		temp.p = nullptr;
	}

	~A() 
	{
		delete p;
		--t;
	}
};

int A::t = 100;

void vec_test6() // memory leak tests
{
	cout << boolalpha;
	cout << (A::t == 100) << endl;
	{
		vec<A> vv(100);
	}
	cout << (A::t == 0) << endl;
}

void vec_test7() // copy ctor tests
{
	vec<string> v1(101, "abc");
	vec<string> v2(v1);

	cout << boolalpha;

	cout << (v1 == v2) << endl;
	v2.pop_back();
	cout << !(v1 == v2) << endl;
	v1.pop_back();
	cout << (v1 == v2) << endl;
	v1.push_back("AAAA");
	cout << !(v1 == v2) << endl;
	v2.push_back("AAAD");
	cout << !(v1 == v2) << endl;
	v2.pop_back();
	v2.push_back("AAAA");
	cout << (v1 == v2) << endl;
}

void vec_test8() // copy assignment operator tests
{
	vec<string> v1(101, "abc");
	vec<string> v2(100, "abc");

	cout << boolalpha;
	cout << !(v1 == v2) << endl;

	v1 = v2; 

	cout << (v1 == v2) << endl;
}

template <typename T1, typename T2>
bool all_equal(const T1& t1, const T2& t2)
{
	return (t1 == t2);
}

template <typename T1, typename T2, typename... T3>
bool all_equal(const T1& t1, const T2& t2, const T3&... args)
{
	return (t1 == t2) && all_equal(t2, args...);
}

void vec_test9() // move ctor and move assignment tests
{
	vec<double> v1(245);
	vec<double> v2(147);
	vec<double> v3(v2);

	v1 = move(v2);
	cout << boolalpha;
	cout << all_equal(v1.size(), 147, v3.size()) << endl;
}

void vec_test10() // tests with std::vector conversions
{
	vector<int> v1 = generate_random_vector(1001);
	vec<int> v(v1);
	cout << boolalpha;
	cout << (v1 == (vector<int>)v) << endl;
}

void vec_test11()
{
	vec<vec<int>> v;
	vector<vector<int>> v2;

	for (int i = 0; i < 5; ++i)
	{
		vector<int> r = generate_random_vector(1001);
		v.push_back(r);
		v2.push_back(r);
	}

	cout << boolalpha;
	
	for (int i = 0; i < 5; ++i)
	{
		cout << equal(v[i].cbegin(), v[i].cend(), v2[i].cbegin(), v2[i].cend()) << endl;
	}
}

void vec_tests12()
{
	vector<vector<int>> v = { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} };

	vec<vec<int>> vc;
	vc.reserve(v.size());
	for (int i = 0; i < v.size(); ++i)
	{
		vc.push_back(v[i]);
	}

	cout << boolalpha;

	bool b = true;
	for (int i = 0; i < v.size(); ++i)
	{
		b &= equal(v[i].cbegin(), v[i].cend(), vc[i].cbegin(), vc[i].cend());
	}
	cout << b << endl;
}