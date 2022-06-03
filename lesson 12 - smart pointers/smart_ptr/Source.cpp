#include <iostream>
#include <memory>
#include <functional>
#include <vector>

using namespace std;

// unique_ptr<T, D = default_deleter<T>>, shared_ptr<T>

struct A
{
    int a;
    char c;
    bool b;

    explicit A(int cc = 0) : a(cc) { cout << "A()\n"; }
    A(const A& aa) : a(aa.a) { cout << "A(const A& aa)\n"; }
    A(int aa, char cc, bool bb) : a(aa), c(cc), b(bb) { cout << "A(int aa, char cc, bool bb)\n"; }
    ~A() { cout << "~A()\n"; }
    // explicit operator int() const {
    //   return a;
    // }
};

void h(int a)
{
    cout << a;
}

void h2()
{
    A a(8, 'c', false);
    //  h((int) a);

    A a2(8);

}

void func(int* ptr)
{
    cout << "function pointer for custom deleter\n";
    delete ptr;
}

void f1()
{
    unique_ptr<int> p1(new int(7));

    //  unique_ptr<int> p22(p1);

    cout << *p1 << endl;

    //std::function
    unique_ptr<int, std::function<void(int*)>> p2(new int(7), [](int* p) { cout << "custom delete\n"; delete p; });

    cout << sizeof(p1) << endl; // sizeof(void*)
    cout << sizeof(p2) << endl;

    // unique_ptr<int[], std::function<void(int*)>> p3(new int[10], [](int* p){ cout << "custom delete\n"; delete[] p;});

    unique_ptr<int, void(*)(int*)> p4(new int(0), func);
    cout << sizeof(p4) << endl;
}

template<typename T, typename Deleter = default_delete<T>>
class unique_ptr_ {
    T* ptr;
    Deleter del;
};

void f2()
{
    shared_ptr<int> p1(new int(7));
    shared_ptr<int> p2(p1);

    cout << *p1 << endl;
    cout << p1.use_count() << endl;

    cout << sizeof(p1) << endl;
    shared_ptr<A> p3(new A(9), [](A* p) { cout << "custom delete A\n"; delete p; });
    cout << sizeof(p3) << endl;

    unique_ptr<int> p1_(new int(7));

    shared_ptr<int> pp(move(p1_));
}

void f3()
{
    //shared_ptr<int> p1 = make_shared<int>(8);

    /*
    int* pp = new int(7); //raw pointer
    shared_ptr<int> p1(pp);
    shared_ptr<int> p2(pp);
    delete pp;

    cout << p1.use_count() << " : " << p2.use_count() <<endl;
    */
}


template<typename T>
class _shared_ptr {
    T* ptr;
    size_t* counter;
public:
    _shared_ptr(T* p)
    {
        ptr = p;
        counter = new size_t(1);
    };

    _shared_ptr(const _shared_ptr& other)
    {
        ptr = other.ptr;
        counter = other.counter;
        ++* counter;
    }
    /*
      _shared_ptr(_unique_ptr&&)
      {

      }
    */
    _shared_ptr& operator=(const _shared_ptr& other)
    {
        ~_shared_ptr();
        ptr = other.ptr;
        counter = other.counter;
        ++* counter;
    }

    ~_shared_ptr()
    {
        if (*counter == 1) {
            cout << "del\n";
            delete ptr;
            delete counter;
        }
        else
            --* counter;
    }

    size_t use_count() const
    {
        return *counter;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T* get() const {
        return ptr;
    }
};

void f5()
{
    _shared_ptr<int> p1(new int(7));
    _shared_ptr<int> p2(p1);
    cout << *p1 << endl;
    cout << p1.use_count() << " : " << p2.use_count() << endl;
}

// make_unique, make_shared

// control_block

void f7()
{
    //  int* pp = new int(7);
    shared_ptr<int> s1 = make_shared<int>(7);
    shared_ptr<int> s2(s1);

    //raw point
}

void f8(shared_ptr<int> a, shared_ptr<int> b)
{

}
void f9()
{
    f8(shared_ptr<int>(new int(7)), shared_ptr<int>(new int(8)));
    // vs
    f8(make_shared<int>(7), make_shared<int>(8));
}

template<typename T>
class _shared_ptr_
{
    template<typename Q>
    struct control_block
    {
        size_t ref_count;
        //   size_t weak_count;
        std::function<void(Q*)> custom_deleter;
        //control_block(...)
    };

    T* ptr;
    control_block<T>* c_ptr;
};

//template <typename... Args>
//make_shared(Args...) - TODO
//{
//void* p = operator new(control_block<T> + sizeof(T))
//new (p) control_block(...)
//new(control_block(p) + 1)T(args...);
//}

void f6()
{
    // _shared_ptr<int> p1(new int(7),[](int*){/*...*/});

}

//push_back vs emplace_back
/*
template <typename...Args>
void _emplace_back(Args&&... args)
{
  new (p+size_used) T(args...);
}
*/

void f10()
{
    vector<A> v;
    //  v.push_back(A(7, 'c', true));
    v.emplace_back(7, 'c', true);
}

//C-style () static_cast<>
// static_cast, dynamic_cast, reinterpret_cast, const_cast

struct AA
{
    int a;
    string b;
};
struct BB
{
    char c;
};

void f11()
{
    A aa = static_cast<A>(7);
    //  int* b = static_cast<int*>(&aa);
    int* b = reinterpret_cast<int*>(&aa);
    cout << *b;
}

void f12()
{
    AA a{ 7, "ABC" };
    BB b{ 'c' };

    BB* aa_p = reinterpret_cast<BB*>(&a);
    //cout << aa_p << endl;
}

class S {
public:
    S(int c) {
        topSecretValue = c;
    }
    bool b;
    int i;
    string s;
private:
    int topSecretValue;//
};

void f13()
{
    S s(78);

    class S_ {
    public:
        S_(int c) {
            topSecretValue = c;
        }
        bool b;
        int i;
        string s;
        int topSecretValue;//
    };
    S_* obj = reinterpret_cast<S_*>(&s);
    cout << obj->topSecretValue << '\n';
}

void f14(const int* p)
{
    /*
    int a = 7;
    const int& aa = a;
    */
    int* b = const_cast<int*>(p);
    *b = 8;
    /*
    cout << a << endl;
    cout << aa << endl;
    cout << b << endl;
    */
}

template<typename T>
void t(T a, T b) = delete;

void t(int a, int b)
{
    cout << a << " : " << b;
}

void tt()
{
    t(7, 5);
    // t('c', 'a');
    // t(7.5, 8.1);
}

struct Q
{
    mutable int a;
    mutable int b;

    void f() const
    {
        // a = 7;
        b = 7;
    }
};

struct X
{
    //...
    ~X() noexcept
    {
        //...
    //    throw 7;
    }
};

int main() {
    try
    {
        //stack unwinding
        X x;
        //...
        throw 74;
        //...
    }
    catch (int c) //abort
    {
        cout << c;
    }

    //  f1();
    //  f2();
    //  f3();
    //  f5();
    //  f10();

      //f11();
     // f13();
      /*
      int a = 7;
      const int b = 9;

      f14(&a);
      cout << a <<endl;

      f14(&b);
      cout << b <<endl;
      */
    std::cout << "Hello World!\n";
}