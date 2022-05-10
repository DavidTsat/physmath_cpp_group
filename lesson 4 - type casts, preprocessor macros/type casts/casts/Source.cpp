#include <iostream>

using namespace std;

struct B;

struct A
{
	A() = default;

	A(const B&)
	{
		cout << "A(const B&)" << endl;
	}
};

struct B
{
	explicit B(int a) {}
	B(const A&)
	{
		cout << "B(const A&)" << endl;
	}
	B& operator=(const A&)
	{
		cout << "B& operator=(const A&)" << endl;
		return *this;
	}

	operator A()
	{
		cout << "B::operator A()" << endl;
		return A();
	}
	
};

void f(B b)
{
	cout << 7 << endl;
}

class C {
	double i, j;
};

class Addition {
	int x, y;
public:
	Addition(int a, int b) { x = a; y = b; }
	int result() { return x + y; }
};

void example_1()
{
	A a;
	B b = a;    // calls constructor
	b = a;      // calls assignment
	a = b;      // calls type-cast operator


//	f(5);

	int aaa = 7.6;
}

void example_2()
{
	C c;
	Addition* p = (Addition*)&c;
	cout << p->result();
}

class Base { virtual void dummy() {} };
class Derived : public Base { int a; };

class P {};
class Q {};


void print_c(char* str)
{
	cout << str << '\n';
}

void example_3()
{
	P p;
	Q q;

	Q* qq = reinterpret_cast<Q*>(&p);
	//Q q2 = reinterpret_cast<Q>(p);
	//static_cast
}

void example_4()
{
	const char* c = "sample text";

	print_c(const_cast<char*>(c));

	int a = 7;

	const int& bb = a;
	int& b = const_cast<int&>(bb);
	b = 8;
	cout << a << endl;

}

int main()
{
	//example_2();
	//example_3();
	example_4();
	return 0;
}
