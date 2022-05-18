#include <iostream>
#include <cstdarg>
using namespace std;


int a = 4;
int b = 50;

//#define max_(a, b) a > b ? a : b
#define max_(a, b) (a > b ? a : b)
//#define max_(x, y) (((x) > (y)) ? (x) : (y))
#define max2_(a, b)  \
   { decltype (a) _a = (a); \
       decltype (b) _b = (b); \
     max_elem = _a > _b ? _a : _b; }


// FIRST PROBLEM: Why the following doesn't compile in context cout << max_(a, b) << endl;? (need to add parenthesis) 
// #define max_(a, b) a > b ? a : b
// The first fix

// SECOND PROBLEM:
void second_example()
{
	cout << max_(a, ++b) << endl; // a > ++b ? a : ++b
	cout << max_(b++, a) << endl; // a > b++ ? a : b++
	cout << b << endl; // 54
}

//FIXIND the ++ issue
void third_example()
{
	int max_elem;
	max2_(a, ++b)
	cout << max_elem << endl; // 51
	cout << b << endl; // 51
	max2_(b++, a)
	cout << max_elem << endl; // 52
	cout << b << endl; // 52
}

// QUESTION: how to create a macro for computing square 

// create a macro to call a function: first parameter is the function name and others are the arguments

#define call_function(f, ...) f(__VA_ARGS__);

void g(int a, double b)
{
	cout << a + b << endl;
}

void forth_example()
{
	call_function(g, 5, 14.7);
}

// about Variadic arguments 
// va_start  - enables access to variadic function arguments
// va_arg    - accesses the next variadic function argument
// va_copy   - makes a copy of the variadic function arguments
// va_end    - ends traversal of the variadic function arguments
// va_list   - holds the information needed by va_start, va_arg, va_end, and va_copy

double add_nums(int count, ...)
{
	double res = 0;
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; ++i)
	{
		res += va_arg(args, double);
	}
	va_end(args);
	return res;
}

void fifth_example()
{
	cout << add_nums(4, 0., -1., 4., 5.7) << endl;
}

// QUESTION: 
// compute average with a variadic template function: example average(5, 7.1, 4.8, -2.2, 0.6, 1.3) == 5.8


//The "#" operator can be used in function - like macros to convert the parameter into a string.
#define simple_str(x) #x

void sixth_example()
{
	string s = simple_str(David);
	cout << simple_str(David) << endl;
}

// an example of bad usage
#define my_name David

void seventh_example()
{
	cout << simple_str(my_name) << endl; // we expect David but it prints my_name
}

// fix previous example
#define to_str(x) simple_str(x)

void eight_example()
{
	cout << to_str(my_name) << endl; 
	cout << to_str(Arman) << endl;
}

// ## - token concatenation
struct command
{
	const char* name;
	void (*function)(int);
};

void quit_command(int)
{
	// quit the program
	cout << "quit the program" << endl;
}
void help_command(int)
{
	// open help menu
	cout << "open help menu" << endl;
}

#define COMMAND(name) {#name, name##_command}
void nineth_example()
{
	command c[2] = { { "quit", quit_command }, { "help", help_command } /*,...*/ };
	command c2[2] = { COMMAND(quit), COMMAND(help) };
	c2[0].function(7);
	c2[1].function(8);
}

# define MinTime   10
# define MaxTime   210 
# define TimeCount 50

// second example with ##.
#define bad_average(x) \
(((Max##x) - (Min##x)) / (x##Count))

void tenth_example()
{
	cout << bad_average(Time) << endl;
}

#define TIME Time

/*
* Solution
#define concat_helper(x, y) x##y
#define concat(x, y) concat_helper(x, y)

#define good_average(x) \
(((concat(Max,x)) - (concat(Min, x))) / concat(x,Count))
*/

void eleventh_example()
{
	cout << bad_average(Time) << endl; // HOMEWORK: Fix this issue
//	cout << good_average(TIME) << endl; // solution
}

int main()
{
//	second_example();
//	third_example();
//	forth_example();
//	fifth_example();
//	seventh_example();
//	eight_example();
//	nineth_example();
//	tenth_example();
	eleventh_example();

	return 0;
}

