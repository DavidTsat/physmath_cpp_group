#include <iostream>
#include <vector>
using namespace std;

class A {
private:
    int x = 7;

protected:
    double d = 7.8;
public:
    char c = 'D';
};

class B1 : public A {
    // implementation inheritance, interface inheritance
    // accessibility visibility
    // x - not accessible
    // d - protected
    // c - public
};

class B2 : protected A {
    // implementation inheritance, interface inheritance
    // accessibility visibility
    // x - not accessible
    // d - protected
    // c - protected
};

class B3 : private A {
    // implementation inheritance, interface inheritance
    // accessibility visibility
    // x - not accessible
    // d - private
    // c - private
};

/*
base class, derived class

class shape

class circle, class rectangle

      shape
     /      \
  circle   rectangle
*/

class shape {
protected:
    float area;
public:
    shape() : area(0.) {}
    float get_area() const { return area; }
    virtual void compute_area() = 0;
    virtual shape* clone() = 0;
    //  void draw() const {}
};

class circle : public shape
{
    float r;
    circle(const circle& c) : r(c.r) {}
public:
    circle(float r_) : r(r_) { }
    void compute_area() override
    {
        area = r * r * 3.14;
    }

    shape* clone() override {
        return new circle(*this);
    }

    pair<float, float> get_circle_center() const
    {
        return { 4.5, 8.9 };
    }
};

class rectangle : public shape
{
    float l, w;
public:
    rectangle(float l_, float w_) : l(l_), w(w_) {}

    void compute_area() override
    {
        area = l * w;
    }

    shape* clone() override {
        return new rectangle(*this);
    }
};

void test7(shape* s)
{
    // "virtual constructor" imitation
    shape* s2 = s->clone();
    s2->compute_area();
    cout << s2->get_area();
}

void test1()
{
    circle c(4);
    c.compute_area();
    cout << c.get_area();
}
/*
void test2()
{
  shape s;
  s.compute_area();
  cout << s.get_area() <<endl;
}
*/

void f(shape* s)
{
    s->compute_area();
    cout << s->get_area() << endl;
}

struct S
{
    // vtable* vptr
    // RTTI  Run type Type Information
    // dynamic_cast
    int c;
    virtual ~S() {}
};

struct D
{
    int* p;
    D() { cout << "D::D()\n"; p = new int[1000]; }
    virtual ~D() { delete[] p; cout << "D::~D()\n"; }
};

struct E : public D
{
    int* p2;
    E() { cout << "E::E()\n"; p2 = new int[1000]; }
    ~E() { delete[] p2; cout << "E::~E()\n"; }
};

void test4()
{
    D* d = new E();
    //...

    delete d;
}


void test3()
{
    cout << sizeof(S) << endl;

    //static type = dynamic type
    // abstract if at least one pure virtual function

  //  shape* s1 = new shape;
    shape* s2 = new circle(4);
    shape* s3 = new rectangle(2, 3);
    ///  vector<shape*> v {s2, s3};
    //  shape s;

    //  f(s1);
    f(s2);
    f(s3);

    // test1();
    // test2();
    cout << endl;
}

class base
{
    int x;
protected:
    virtual void print()
    {
        cout << "base::print()\n";
    }
public:
    base() { print(); }
    virtual ~base() { print(); }
    void base_print() { print(); }
};

class derived : public base {

    void print() override
    {
        cout << "derived::print()\n";
    }
public:

    derived() { print(); }
    ~derived() { print(); }
};

void test5()
{
    base* b = new derived;
    b->base_print();
    derived d;
    delete b;
}

//diamond problem

 /*
      / \
      \ /
*/
struct P
{
    int a[40];
    void f() {}
};

struct Q : virtual public P
{

};

struct R : virtual public P
{

};

struct M : public Q, public R
{
    M() { f(); }// {a[0] = 74;}
};

void test9(shape* s)
{
    //shape* s2 = new circle(9); // derived* -> shape*; implicit cast 
    circle* c = dynamic_cast<circle*> (s); // shape* -> derived*; explicit cast; RTTI
    //dynamic_cast vs static_cast; 
    if (c == nullptr)
        return;
    c->compute_area();
    cout << c->get_area() << endl;

    auto pp = c->get_circle_center();
    cout << pp.first << " : " << pp.second << endl;
}

class AA {
public:
    void show()
    {
        cout << "Hello form A \n";
    }
};

class BB : virtual public AA {
};

class CC : virtual public AA {
};

class DD : public BB, public CC {
};

void test10()
{
    DD d;
    d.show();
}

class Base1 {
public:
    Base1()
    {
        cout << " Base1's constructor called" << endl;
    }
};

class Base2 {
public:
    Base2()
    {
        cout << "Base2's constructor called" << endl;
    }
};


class Derived : public Base1, public Base2 {
public:
    Derived()
    {
        cout << "Derived's constructor called" << endl;
    }
};


void test11()
{
    Derived d;
}


class PP {
public:
    void print() { cout << " Inside P"; }
};

class QQ : public PP {
public:
    void print() { cout << " Inside Q"; }
};

class RR : public QQ { };


void test12()
{
    RR r;
    r.print();
}

class Base3 {
protected:
    int i, j;
public:
    Base3(int _i, int _j) : i(_i), j(_j) { }
};

class Derived3 : public Base3 {
    char c;
public:
    Derived3(int i_, int j_) : Base3(i_, j_), c('D') {}

    void show() {
        cout << " i = " << i << "  j = " << j;
    }
};


void test13()
{
    Derived3 d(14, 48);
    d.show();
}

class K {
public:
    virtual ~K() {}
};
class derived_K : public K {};

void test14()
{
    K* k = new K;

    derived_K* k2 = dynamic_cast<derived_K*>(new K);
    if (k2 == nullptr)
    {
        cout << "nullptr\n";
    }
    else
    {
        cout << "not null\n";
    }
}

int main()
{
    test14();
    //test12();
   // test13();

   // test11();
  //  test10();  

  //  shape* s = new circle(10);
  //  shape* s2 = new rectangle(10, 5);

   // test9(s);
  //  test9(s2);

    /*
    shape* s = new circle(10);
    shape* s2 = new rectangle(10, 5);
    cout << endl;
    test7(s);
    cout << endl;
    test7(s2);
    */
    //  cout << sizeof(M) << endl;

    //  test5();

    //  test5();

      /*
      base::print()
      derived::print()
      base::print() -> derived::print
      derived::print()
      base::print()
      */

      //  test4();
      //  return 0; 
}