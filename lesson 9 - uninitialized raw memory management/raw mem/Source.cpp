#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <iterator>
#include <new>
#include <algorithm>
using namespace std;

void f1()
{
	vector<int> v;
	v.reserve(20); // uninitialized new (operator new)
   // v.resize(2); // new + initialize each element with default value
	/*
	capacity/size  <=> reserve()/resize()
	*/

	assert(v.capacity() >= 2);
	v[10] = 1;
	v[11] = 2;
	// memcpy, memzero, 
	// placement new 

	for (vector<int>::const_iterator i = v.cbegin(); i != v.cend(); ++i)
	{
		cout << *i << '\n';
	}

	cout << endl;
}

void f2()
{
	vector<int> v{ 1,2,3,4,5 };

	v.push_back(7);

	cout << v.size() << " : " << v.capacity() << endl;
	// v = vector<int>(v.cbegin(), v.cend());
	// (vector<int>(v)).swap(v);
	// v.resize(140);

	cout << v.size() << " : " << v.capacity() << endl;
}

struct A {
	int c;
	//...
	A() { cout << "A default" << endl; }
	A(int cc) : c(cc) { cout << "A(int cc)" << endl; }
	A(const A& aa) { c = aa.c;  cout << "A(const A&)" << endl; }
	A(A&&) noexcept { cout << "A(A&&)" << endl; }
	A& operator=(const A& aa) { c = aa.c; cout << "operator=(const A&)" << endl; return *this; }
	A& operator=(A&&) noexcept { cout << "operator=(A&&)" << endl; return *this; }

	operator int() { return c; }
};

template<typename A, typename B>
void swap_(A& a, B& b)
{
	A temp(a);
	a = b;
	b = temp;
}
template <typename T1, typename T2>
void construct(T1* p, const T2& v)
{
	new (p) T2(v);
}

template <typename T>
void destroy(T& p)
{
	p.~T();
}

template<typename A, typename B>
void swap2_(A& a, B& b)
{
	A temp(a);

	destroy(a);
	construct(&a, b);

	destroy(b);
	construct(&b, temp);
}

void f3()
{

	//  A* p = new A; // new  

	A* p2 = (A*) operator new[](10 * sizeof(int)); // operator new - uninitialized mem
	//placement new

	new (&p2[4]) A(74);
	p2[4].~A();
	cout << p2[4] << endl;
	operator delete[](p2);
}

void f4()
{
	A a(47), b(58);
	swap2_(a, b);
}

template<class InputIt, class OutputIt>
OutputIt copy_(InputIt first, InputIt last, OutputIt d_first)
{
	for (; first != last; ++first, ++d_first) {
		*d_first = *first;
	}
	return d_first;
}

template<class InputIt, class OutputIt>
OutputIt unitialized_copy_(InputIt first, InputIt last, OutputIt d_first)
{
	using T = typename iterator_traits<OutputIt>::value_type;
	OutputIt d = d_first;
	try
	{
		for (; first != last; (void)++first, (void)++d_first)
		{
			construct((void*)addressof(*d_first), *first);
		}
		return d_first;
	}
	catch (...)
	{
		for_each(d, d_first, [](T& a) { destroy(a); });
		throw;
	}
}

void f5()
{
	vector<int> v{ 1,2,3,4,5 };
	A* p2 = (A*) operator new[](10 * sizeof(int));
	unitialized_copy_(v.cbegin(), v.cbegin() + 5, p2);
	copy(p2, p2 + 5, ostream_iterator<int>(cout, " "));
}

template<typename T1, typename T2>
struct is_same_ {
	const static bool val = false;
};

template<typename T1>
struct is_same_<T1, T1> {
	const static bool val = true;
};

template<typename T1, typename T2>
bool is_same_class()
{
	return is_same_<T1, T2>::val;
}

void ff()
{
	cout << boolalpha << is_same_class<int, double>() << endl; // false
	cout << is_same_class<int, int>() << endl;                 // true
	cout << is_same_class<string, vector<string>>() << endl;   // false
	cout << is_same_class<string, string>() << endl;           // true
}

int main() {
	//  f1();
	//  f2();
	//  f3();
	//  f4();
	//  f5();
	ff();
	return 0;
}