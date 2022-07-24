#include <iostream>
#include <string>

using namespace std;

class Base
{
	void print() {
		std::cout << "from base" << std::endl;
	}
public:
	Base() { print(); }
	~Base() { print(); }
	void basePrint() { print(); }
};

class Derived : public Base
{
	void print()
	{
		std::cout << "from Derived" << std::endl;
	}
public:
	Derived() { print(); }
	~Derived() { print(); }
};

void test1()
{
	Base* base = new Derived;
	base->basePrint();
	delete base;
}

class shape
{
protected:
	string name;
public:
	virtual void draw() const = 0;
	virtual void resize(int factor) = 0;
	virtual shape* clone() = 0;
	virtual shape* create() = 0;
	virtual ~shape() {}
	string get_name() const { return name; }
};

class circle : public shape
{
	char c = 'k';
	string ss = "circle";

	circle(const circle& cc) { *this = cc; };
public:
	circle(string n) { shape::name = n; }

	circle* clone() override
	{
		return new circle(*this);
	}

	circle* create() override
	{
		return new circle("c");
	}

	void draw() const override
	{

	}
	void resize(int factor) override
	{

	}
};

class square : public shape
{
	int x;
	const char* cp = "CCPCPPCPC";
	square(const square& cc) { *this = cc; };
public:
	square(string n) { shape::name = n; }
	square* clone() override
	{
		return new square(*this);
	}
	square* create() override
	{
		return new square("s");
	}
	void draw() const override
	{

	}
	void resize(int factor) override
	{

	}
	void rotate(int angle)
	{
		x = angle + 5;
		cout << "rotate: " << cp << x << endl;
	}
};

void f(shape* s)
{

	shape* s1 = s->clone();

	dynamic_cast<square*>(s1)->rotate(5);
	cout << s->get_name() << endl;
}

int test2()
{
	shape* s1 = new circle("circle 1");
	shape* s2 = new square("square 1");
	//f(s1);
	f(s2);

	//circle cc(circle("bg"));
	return 0;
}

class base2 {
protected:
	int arr[10];
//	int c;
};

class b1 : public virtual base2{ };

class b2 : public virtual base2 { };

class derived : public b1, public b2 
{
//	int c;
	/*
	derived()
	{
		arr[0] = 5;
	}
	*/
};

class P {
public:
	void print() { cout << " Inside P"; }
};

class Q : public P {
public:
	void print() { cout << " Inside Q"; }
};

class R : public Q { };

class Base2 {
protected:
	int i, j;
public:
	Base2(int _i , int _j) : i(_i), j(_j) { }
};
class Derived2 : public Base2 {
public:
	Derived2() : Base2(7, 8) {}
	void show() {
		cout << " i = " << i << "  j = " << j;
	}
};

void test4() {
	Derived2 d;
	d.show();
}

int main()
{
	test4();
	/*
	P p;
	Q q;
	R r;
	p.print();
	q.print();
	r.print();
	*/
//	test1();
//	cout << sizeof(derived) << endl;
	return 0;
}