//Here I will use x as pointer size(because pointer size is implementation defined) and also 4 as sizeof(int)

#include <iostream>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define R 10
#define C R<<1

// first question
void first_question()
{
	int(*p)[R][C] = { 0 };
	// What is the type of p ? // pointer to 2d array of ints
	// What will be the outputs ? sizeof(int)*
	cout << sizeof(p) << endl; //x
	cout << sizeof(*p) << endl; // 800
	cout << sizeof(**p) << endl; // 80
	// What will be the output 
	cout << (*p)[0][15] << endl; // nothing, p is pointing to nullptr
	// Please define a correct value and initialize p with that value, so that the example above is correct
	int arr[R][C] = {};
	p = &arr;
}

// second question
void f2(int* p)
{
	static int q = 10;
	p = &q;
}

void second_question()
{
	int r = 20;
	int* p = &r;
	f2(p);
	// What will be the output
	cout << *p << endl; // 20
	// How can we ... ? two ways
	/* if you meant changing pointer value inside function, then we can
	* pass reference to function. void f2(int*& p)
	* pass pointer to pointer. void f2(int** p) and then change pointer value by dereferencing p
	*/
}

//third example
void third_example()
{
	// What is happening here, what will be the output and some more questions on this code snippet
	int a[5] = { 1,2,3,4,5 }; //creating array of ints
	int* p = (int*)(&a + 1); // no idea

	cout << *(a + 1) << endl; // 2
	cout << *(p - 1) << endl;
}

void forth_example()
{
	const char* c[] = { "ABCD", "EF", "GHI", "JKLMN" }; //array of pointers to const char
	const char** cp[] = { c + 3, c + 2, c + 1, c }; //array of pointers to pointers to const char
	const char*** cpp = cp; //pointer to pointer to pointer to const char

	cout << sizeof(c) << endl; // 4*x
	cout << *cp[1] << endl; // address of "GHI"
	cout << **++cpp << endl; // address of "GHI"
	cout << ***cpp << endl; // JKLMN

	cout << *(--(*++cpp)) + 3 << endl; //this is maximum that I have done: address of "EF" + 3
	cout << (*cpp[-2] + 3) << endl; //no idea

	cout << (cpp[-1][-1] + 1) << endl; //no idea
}

// fifth example
void f5(char** str_ref)
{
	str_ref++;
}

int fifth_example()
{
	char* str = new char[100];
	strcpy_s(str, 100, "test_string");
	f5(&str);
	puts(str); // same as cout, but puts is a C function not C++
	delete[] str;
	return 0;
}

// sixth example
void f6(const char**);

void sixth_example()
{
	const char* argv[] = { "abc", "def", "ghi", "jkl", "mno", "pqr" };
	f6(argv);
}

void f6(const char** p)
{
	const char* t;
	t = (p += sizeof(int))[-1]; //assume sizeof(int) == 4
	//how can we know p+4?
	cout << t << endl;
	cout << &t[1] << endl;
}

// seventh example
void seventh_example()
{
	int a[][3] = { 1, 2, 3, 4, 5, 6 };

	int(*ptr)[3] = a;
	// Before trying to guess the output
	// try to imagine or better draw the 2-d array a and ptr
	// then answer the questions
	cout << (*ptr)[1] << ':' << (*ptr)[2] << endl; //OUTPUT: 2:3
	++ptr;
	cout << (*ptr)[1] << ':' << (*ptr)[2] << endl; //OUTPUT: 5:6

}

//eight example
void eigth_example()
{
	int* ptr = new int[5];
	int* p = ptr;
	for (int i = 0; i < 5; i++)
		*(ptr + i) = i;

	cout << *ptr++ << ' ';
	cout << (*ptr)++ << ' ';
	cout << *ptr << ' ';
	cout << *++ptr << ' ';
	cout << ++ * ptr << ' ';
	//OUTPUT: 0 1 2 2 3 
	cout << endl;
	delete[] p;
}


void sum_(int a, int b)
{
	cout << a + b << endl;
}

void sub_(int a, int b)
{
	cout << a - b << endl;
}


constexpr inline int f_(int a, char c)
{
	return a + '0' + c;
}

constexpr inline int g_(int a, char c)
{
	return a + '0' - c;
}

void nineth_example()
{
	// A task 
	// You have functions f_ and g_
	// 1. Create an array of function pointers with two elements, assign f_ and g_ to the 0th and first elements and call them with some arguments
	// 2. Create a pointer to an array of pointers assign the address of the array of the previous example to our pointer and again call both of the functions
	// hint: you can look at the seventh_example of pointer_practice project
	// 
	//...
	int (*p[2])(int, char) = { f_, g_ };
	int (*(*ptr)[2])(int, char) = &p; //in previous example there is no array of pointers
	(*ptr)[0](0, '0');
	(*ptr)[1](1, '1');
}

int main()
{
	//first_question();
	//second_question();
	//third_example();
	//forth_example();
	//fifth_example();
	//sixth_example();
	//seventh_example();
//	eigth_example();

	//nineth_example();

	return 0;
}