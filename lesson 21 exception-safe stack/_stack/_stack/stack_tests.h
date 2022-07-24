#pragma once
#include "_stack.h"
#include <string>

using namespace std;

void test1()
{
	_stack<string> s;

	for (int i = 0; i < 299989; ++i)
	{
		s.push(to_string(i) + "abc");
		if (i % 7 == 0)
			s.pop();
	}

	
	int i = 0;
	while (!s.empty())
	{
///		cout << i << ' ' << s.top() << '\n';
		s.pop();
	}

}

struct S
{
	int a;
	bool b;
	char c;
public:
	S(int _a, bool _b, char _c) : a(_a), b(_b), c(_c) { cout << "S()\n"; }
	S(const S& s) : a(s.a), b(s.b), c(s.c) { cout << "S(const S& s)\n"; }
};

void test2()
{
	_stack<S> s;

//	s.push({ 14, true, 'c' });
	s.emplace( 14, true, 'c' );

	const S& c = s.top();

	cout << c.a << ' ' << c.b << ' ' << c.c << endl;
}

void test3()
{
	_stack<string> s1, s2;

	for (int i = 0; i < 317; ++i)
	{
		s1.push(to_string(i) + "abc");
		if (i % 7 == 0)
			s1.pop();

		s2.push(to_string(31457 - i) + "cba");
		if (i % 4 == 0)
			s2.pop();
	}

	cout << s1.size() << " : " << s1.top() << endl;
	cout << s2.size() << " : " << s2.top() << endl;

	s1 = s2;
	cout << endl;
	
	cout << s1.size() << " : " << s1.top() << endl;
	cout << s2.size() << " : " << s2.top() << endl;
}

void test4()
{
	_stack<string> s1, s2;

	for (int i = 0; i < 17; ++i)
	{
		s1.push(to_string(i) + "abc");
		if (i % 7 == 0)
			s1.pop();

		s2.push(to_string(17 - i) + "cba");
		if (i % 4 == 0)
			s2.pop();
	}

	cout << s1.size() << " : " << s1.top() << endl;
	cout << s2.size() << " : " << s2.top() << endl;

	try
	{
		s1 = s2;
	} 
	catch (...)
	{
		/*
		cout << s1.size() << endl;
		while (!s1.empty())
		{
			cout << s1.top() << endl;
			s1.pop();
		}
		*/
	}

	cout << endl;

	cout << s1.size() << " : " << s1.top() << endl;
	cout << s2.size() << " : " << s2.top() << endl;
}