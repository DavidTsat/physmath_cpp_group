//Here I will use x as pointer size(because pointer size is implementation defined) and also 4 as sizeof(int)

#include <iostream>
#include <bitset>
#include <map>
#include <any>
#include <algorithm>

using namespace std;

// Read the following types

int* pi; // pointer to int
char** ppc; // pointer to pointer to char
int* ap[15]; // array of 15 pointers to ints
int (*fp)(char*); // pointer to a function taking a char* argument and returning an int value
int(*ptr)[10]; // pointer to an array ouf 10 integers
int* f(char*); // function taking a char* argument; returns a pointer to int

void first_example()
{
	int x = 1 << 31;
	char* c = (char*)&x;
	cout << bitset<32>(x) << endl;
	*(c + 2) = -1;
	cout << x << endl;
	cout << bitset<32>(x) << endl;
}

void second_example()
{
	int c[4] = { 1,2,3,4 };
	for (int i = 0; i < 4; ++i)
	{
		//QUESTION. How may ways can we print c[i] ? 
		cout << c[i] << " : " << *(&c[0] + i) << " : " << *(c + i) << " : " << *(i + c) << " : " << i[c] << endl;
	}

	// array of pointers
	char* arr[3];

	int j = 1;

	char c1 = 'd';
	char* c2 = new char[15]{ 'a' };
	char c3[4] = { 'c', 'd', 'e', 'f' };

	arr[0] = &c1;
	arr[1] = c2;
	arr[2] = c3;

	// what will be the output		//  i			OUTPUT

	for (int i = 0; i < 3; ++i)		//  0			d
	{								//  1			a
		cout << *arr[i] << endl;	//  2			c
	}
	cout << *(*(arr + 2) + 3) << endl; // OUTPUT: f
	delete[] c2;
}

// pointer to void

void third_example()
{
	string s = "David";
	void* p = &s;
	cout << *(static_cast<string*>(p)) << endl;
	cout << *(static_cast<int*>(p)) << endl; // error
}

// 
//void forth_example(); // I will talk about it on next session

void fifth_example()
{
	// 2d array with new

	constexpr int n = 10;
	int** mat = new int* [n];

	for (int i = 0; i < n; ++i)
	{
		mat[i] = new int[n];
		for (int j = 0; j < n; ++j)
		{
			mat[i][j] = j;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for_each(mat[i], mat[i] + n, [](int i) {cout << i << ' '; });
		cout << endl;
	}

	for_each(mat, mat + n, [](int* row) { delete[] row; });

	// Question: What I forgot to delete ? Add the missing line 

	delete[] mat; //missing line
}

void sixth_example()
{
	// pointer to array
	//data_type(*var_name)[size_of_array];

	int arr[] = { 3, 5, 6, 7, 9, 7 };
	int* p = arr;
	int(*ptr)[6] = &arr;

	// QUESTIONS
	cout << "p = " << arr << ", ptr = " << ptr << endl; //OUTPUT:p = /*arr address*/, ptr = /*arr address*/
	cout << "*p = " << *p << ", *ptr = " << *ptr << endl; //OUTPUT:*p = 3, *ptr = /*arr address*/

	cout << "sizeof(p) = " << sizeof(p) << ", sizeof(*p) = " << sizeof(*p) << endl; //OUTPUT:sizeof(p) = x, sizeof(*p) = 4
	cout << "sizeof(ptr) = " << sizeof(ptr) << ", sizeof(*ptr) = " << sizeof(*ptr) << endl; //OUTPUT:sizeof(ptr) = x, sizeof(*ptr) = 24
}

void sum_(int a, int b)
{
	cout << a + b << endl;
}

void sub_(int a, int b)
{
	cout << a - b << endl;
}

// pointer to functions
void seventh_example()
{
	// QUESTION: How can you pass a funtion to another function as a paramater and call it
	//ANSWER: we can pass a function pointer as a paramater
	void (*f) (int, int) = sum_;
	f(7, 8);

	// What is the following type ?
	void (*f_arr[2]) (int, int); //ANSWER: array of pointers to functions, accepting int, int and returning void

	f_arr[0] = sum_;
	f_arr[1] = sub_;

	f_arr[0](8, 9);
	f_arr[1](8, 9);

	//pointer to array of function pointers

	/*
	* step by step
	* *pp							- pointer
	* (*pp)[2]						- pointer to an array
	* (*(*pp)[2])					- pointer to an array of pointers
	* void (*(*pp)[2])(int, int)    - pointer to an array of pointers to function, accepting int, int and returning void
	*/
	void (*(*pp)[2])(int, int) = &f_arr;
	// QUESTION: How to invoke
	((*pp)[0])(4, 15); //this will call sum_
	((*pp)[1])(4, 15); //this will call sub_
}

void eigth_example()
{
	// a simple example with references
	int x = 0;
	int& y = x; y = 5;

	while (x <= 5)
	{
		cout << y++ << " ";
		x++;
	}
	cout << x;
}
/*
Differences between pointers and references
At first. Pointer is a completely separate type which holds addresses, a reference is just another name for a variable.
1. A reference must be initialized when it's declared, but a pointer can be only declared or initialized by a nullptr.
int& q; - error
int* p;  //ok
int* pp; //nullptr
2. Pointers can be re-assigned, references can't
int a = 7;
int b = 8;
int* p = &a;
p = &b;
*p = 14;
b == 14
3.
A pointer variable has its own identity: a distinct, visible memory address and size (4 or 8 byes or another),
int contrary a reference is bound to the object it was assigned and so the address is the same as the object's
memory it was assigned, and the memory occupied by a reference is invisible.
4.
You can have arbitrarily nested pointers to pointers offering extra levels of indirection. References only offer one level of indirection.
5.
Pointers can iterate over an array; you can use ++ to go to the next item that a pointer is pointing to, and + 4 to go to the 5th element. This is no matter what size the object is that the pointer points to.
6.
A pointer needs to be dereferenced with * to access the memory location it points to, whereas a reference can be used directly. A pointer to a class/struct uses -> to access its members whereas a reference uses a ..
7.
References cannot be put into an array, whereas pointers can be (Mentioned by user @litb)
8.
Const references can be bound to temporaries. Pointers cannot (not without some indirection):
int f1(int& a);
int f2(const int& a);
int f_p(cont int* p);
f1(8); error
f2(4); ok
f_p(&5); error
*/

int main()
{
	//first_example();
	//second_example();
	//third_example();
	//forth_example();
	//fifth_example();

	//sixth_example();
	//seventh_example();
	//eigth_example();

	return 0;
}