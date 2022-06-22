#include <iostream>

using namespace std;

//void average(int arr[12])
void average(int arr[])
{
	cout << "average" << endl;

//	cout << sizeof(arr) << endl;
}

void f1()
{
	int arr_[] = { 1,2,3,4,5,6 };
	cout << sizeof(arr_) << endl;
	cout << sizeof(arr_) / sizeof(arr_[0]) << endl;
	average(arr_);
}

void average2(int(&arr)[6])
{
	cout << "average2\n";
	cout << sizeof(arr) << endl;
}

void f2()
{
	int arr_[] = { 1,2,3,4,5,6 };
	average2(arr_);
}

template <size_t N>
void average3(int(&arr)[N])
{
	cout << "average3\n";
	cout << sizeof(arr) << endl;
}

void f3()
{
	int arr_[] = { 1,2,3,4,5,6,7 };
	average3(arr_);
}

void f4()
{
	int* arr_ = new int[14];
	//average3(arr_);
}

int main()
{
	//f1();
	//f2();
	f3();
	return 0;
}