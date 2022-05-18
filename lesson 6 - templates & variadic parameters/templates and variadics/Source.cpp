#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include <iterator>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

#define show(x) cout <<  #x " = " << x << endl;
#define max_(a, b) a > b ? a : b

/*
 Some generic questions
*/

// Test one
void f(int* x, int* y)
{
	*x = (*x) * (--(*y));
}

void test_one()
{
	int a = 10;

	f(&a, &a);

	show(a)
}

// Test two
class A
{

};
class B
{

};

class C
{
	A* a_;
	B* b_;
public:
	C()
	{
		a_ = new A();
		b_ = new B();
	}
	~C()
	{
		delete a_;
		delete b_;
	}

};

void test_two()
{
	C c;
	{
		C c2;
	}
}

// Test three
struct Employee
{
	string email_;
	string firstName_;
	string lastName_;

	Employee(const char* firstName, const char* lastName)
		: firstName_(firstName), lastName_(lastName), email_(firstName_ + "." + lastName_ + "@gmail.com") {}
};

void test_three()
{
	Employee e("David", "Tsaturyan");
	
	show(e.email_)
	show(e.firstName_)
	show(e.lastName_)
}

// i++ and ++i
/*
* Templates
*/
//Templates are a feature of the C++ programming language that allows functions and classes to operate with generic types. 
// This allows a function or class to work on many different data types without being rewritten for each one.

template <typename T>
void update_count(const T& x)
{
	static int count = 0;
	cout << "x = " << x << " count = " << count << endl;
	++count;
	return;
}

int test_forth()
{
	update_count<int>(1);
	cout << endl;
	update_count<int>(1);
	cout << endl;
	update_count<double>(1.1);
	cout << endl;
	return 0;
}

template <typename T>
T _max(T x, T y)
{
	return (x > y) ? x : y;
}

int test_fifth()
{
	cout << _max(3, 7) << std::endl;
	cout << _max(3.0, 7.0) << std::endl;
//	cout << _max(3, 7.0) << std::endl;
	return 0;
}

template <class T>
class Test6
{
private:
	T val;
public:
	static int count;
	Test6() { count++; }
};

template<class T>
int Test6<T>::count = 0;

int test_sixth()
{
	Test6<int> a;
	Test6<int> b;
	Test6<double> c;
	cout << Test6<int>::count << endl;
	cout << Test6<double>::count << endl;
	return 0;
}

template<class T, class U>
class A7 {
	T x;
	U y;
	static int count;
};

int test_seventh() {
	A7<char, char> a;
	A7<int, int> b;
	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	return 0;
}

template<class T, class U, class V = double>
class A8 {
	T x;
	U y;
	V z;
	static int count;
};

int test_nineth()
{
	A8<int, int> a;
	A8<double, double> b;
	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	return 0;
}

template <class T>
T max2(const T& a, const T& b)
{
	return (a > b) ? a : b;
}

template <>
int max2 <int>(const int& a, const int& b)
{
	cout << "max2 <int> Called ";
	return (a > b) ? a : b;
}

void test_tenth()
{
	int a = 10, b = 20;
	cout << max2 <int>(a, b);
}

namespace std
{
	template <>
	void swap<A>(A& a, A& b) noexcept
	{
		cout << "called my swap" << endl;
	}
}

void test_eleventh()
{
	A aa;

	std::swap(aa, aa);
}

template<int n> 
struct funStruct
{
	static const int val = 2 * funStruct<n - 1>::val;
};

template<> 
struct funStruct<0>
{
	static const int val = 1;
};

void test_twelfth()
{
	cout << funStruct<10>::val << endl;
}

// Question: How std sort look like ?
// Two ways: with overloading and without

template <typename T, typename Cmp = greater<T>>
T my_max(const T& a, const T& b, Cmp cmp = greater<T>{})
{
	if (cmp(a, b))
	{
		return a;
	}
	return b;
}

template <typename T>
T my_max2(const T& a, const T& b)
{
	if (greater<T>{}(a, b))
	{
		return a;
	}
	return b;
}

template <typename T, typename Cmp>
T my_max2(const T& a, const T& b, Cmp cmp)
{
	if (cmp(a, b))
	{
		return a;
	}
	return b;
}

void test_thirteenth()
{
	int a = 7;
	int b = 8;
	cout << my_max(a, b) << endl;
	cout << my_max(a, b, [](int a_, int b_) { return a_ < b_; }) << endl;

	cout << my_max2(a, b) << endl;
	cout << my_max2(a, b, [](int a_, int b_) { return a_ < b_; }) << endl;
}

template <typename It, typename Cmp = less<typename iterator_traits<It>::value_type>>
void my_sort(It begin, It end, Cmp cmp = less<typename iterator_traits<It>::value_type>{})
{
	cout << "my_sort: " << cmp(*begin, *end) << endl;
}

template <typename SourceIt, typename DestIt, typename F>
void my_transform(SourceIt begin, SourceIt end, DestIt dest_begin, F f)
{
	while (begin != end)
	{
		*dest_begin++ = f(*begin++);
	}
}

void test_forteenth()
{
	vector<int> v({ 1,2,3,4 });
	vector<int> v2;

	struct plus_one
	{
		int operator()(int a) { return ++a; }
	};

	//transform(v.cbegin(), v.cend(), back_inserter(v2), plus_one());
	my_transform(v.cbegin(), v.cend(), back_inserter(v2), plus_one());
	copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout));
	cout << endl;
	copy(v2.cbegin(), v2.cend(), ostream_iterator<int>(cout));
	cout << endl;
}

// map of <string, val> example
template<typename Value>
using string_map = map<string, Value>;
string_map<int> m; // m is a map<str ing,int>

void test_fifteenth()
{
	int* a = new int(4);
	int* b = new int(5);
	
//	int c = 7, d = 8;
	my_sort(a, b);
	
	delete a;
	delete b;
}

template <typename T, typename Allocator = std::allocator<T>>
class my_vec
{
	using value_type = T;
};

template <typename Key, typename Val, typename Allocator = std::allocator<pair<const Key, Val>>, typename Cmp = less<Key>>
class my_map
{

};

template <typename Key, typename Val, typename Hash = hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = std::allocator<pair<const Key, Val>> >
class unordered_map
{

};

/*
	Variadics
*/

/*
va_start
enables access to variadic function arguments
(function macro)

va_arg
accesses the next variadic function argument
(function macro)

va_copy
makes a copy of the variadic function arguments
(function macro)

va_end
ends traversal of the variadic function arguments
(function macro)

va_list
holds the information needed by va_start, va_arg, va_end, and va_copy
(typedef)
*/

void simple_printf(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	while (*fmt != '\0') // about end of string
	{
		if (*fmt == 'd')
		{
			int i = va_arg(args, int);
			printf("%d\n", i);
		}
		else if (*fmt == 'c')
		{
			int c = va_arg(args, int);
			printf("%c\n", c);
		}
		else if (*fmt == 'f')
		{
			double d = va_arg(args, double);
			printf("%f\n", d);
		}
		++fmt;
	}
	va_end(args);
}

void test_sixteenth()
{
	// C's cout is printf
	// simple printf
	simple_printf("dcff", 3, 'a', 1.999, 42.5);
}

// variadic templates

void print_args()
{}

template <typename FirstArg, typename... Args>
void print_args(FirstArg arg, Args... args)
{
	cout << arg << endl;
	print_args(args...);
}

void test_seventeenth()
{
	print_args(5, 4, 7.5, "ABCD");
}

template <typename... Args>
void print_args2(Args... args)
{	
	((cout << args << endl),...);
}

void test_eighteenth()
{
	print_args(5, 4, 7.5, "ABCD"); // C++17 pack fold expression
}

double sum_all_args() { return 0; }

template <typename Arg, typename... Args>
double sum_all_args(Arg arg, Args... args)
{
	return arg + sum_all_args(args...);
}

void test_nineteenth()
{
	cout << sum_all_args(4, 5.7, 'c' + 4);
}

template <typename... Args>
double sum_all_args2(Args... args)
{
	return (args + ...);
}

void test_twentieth()
{
	cout << sum_all_args2(4, 5.7, 15) << endl;
}

template <typename F, typename... Args>
typename std::result_of<F(Args...)>::type function_wrapper(F f, Args... args)
{
	return f(args...);
}

double sum_args(int a, double b, char c)
{
	return a + b + c;
}

void test_twenty_first()
{
	cout << function_wrapper(sum_args, 4, 5.7, 'c') << endl;
	function_wrapper([](int a, double b, char c) {cout << a << ':' << b << ':' << c <<endl; }, 4, 5.7, 'c');
}


// Class template std::tuple is a fixed - size collection of heterogeneous values.It is a generalization of std::pair

// Variadic template classes
//https://en.cppreference.com/w/cpp/utility/tuple

void tuple_first_example()
{
	tuple t{ 1, 2.0, std::string("hello"), std::string("world")};
	std::cout << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ", " << get<3>(t) << '\n'; // This prints: 1, 2.0, hello, world 
	tuple t2{ 1, 2.0, std::string("hello"), std::string("world")};
	std::cout << std::boolalpha << "tuples are equal : " << (t2 == t) << '\n'; // This prints: tuples are equal: true
}
std::tuple<double, char, std::string> get_student(int id)
{
	if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
	if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
	if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
	throw std::invalid_argument("id");
}

void test_twenty_second()
{
	auto student0 = get_student(0);
	std::cout << "ID: 0, "
		<< "GPA: " << std::get<0>(student0) << ", "
		<< "grade: " << std::get<1>(student0) << ", "
		<< "name: " << std::get<2>(student0) << '\n';

	double gpa1;
	char grade1;
	std::string name1;
	std::tie(gpa1, grade1, name1) = get_student(1);
	std::cout << "ID: 1, "
		<< "GPA: " << gpa1 << ", "
		<< "grade: " << grade1 << ", "
		<< "name: " << name1 << '\n';

	// C++17 structured binding:
	auto [gpa2, grade2, name2] = get_student(2);
	std::cout << "ID: 2, "
		<< "GPA: " << gpa2 << ", "
		<< "grade: " << grade2 << ", "
		<< "name: " << name2 << '\n';
}

template <typename... Types>
class my_tuple
{
	// A tuple is typically implemented as a compile time linked - list.
	// Very hard implementation
	// https://medium.com/@mortificador/implementing-std-tuple-in-c-17-3cc5c6da7277
	
	/*
	template <std::size_t _index, typename T>
	class _tuple_impl
	*/
	/*
	tuple : public _tuple_impl<0, int>, 
		public _tuple_impl<1, double>, 
		public _tuple_impl<2, float>
	*/
};

int main()
{
	test_one();
	//test_two
	//test_three();
	//test_forth();
	//test_fifth();
	//test_sixth();
	//test_seventh();
	//test_nineth();
	//test_tenth();
	//test_eleventh();
	//test_twelfth();
	//thirteenth();
	//test_thirteenth();
	//test_forteenth();
	//test_fifteenth();
	//test_sixteenth();
	//test_seventeenth();
	//test_eighteenth();
	//test_nineteenth();
	//test_twentieth();
	//test_twenty_first();
	//tuple_first_example();
	//test_twenty_second();
	return 0;
}