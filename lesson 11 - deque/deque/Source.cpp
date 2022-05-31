#include "deque_.h"
#include <iostream>
#include <deque>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, deque_<T>& d)
{
	for (auto it = d.begin(); it != d.end(); ++it)
	{
		cout << *it << ' ';
	}
	//cout << endl;
	return os;
}

template<class InputIt1, class InputIt2>
bool _equal(InputIt1 first1, InputIt1 last1,
	InputIt2 first2)
{
	for (; first1 != last1; ++first1, ++first2) {
		if (!(*first1 == *first2)) {
			return false;
		}
	}
	return true;
}

void deque__tests()
{
	deque_<int> d1;
	deque_<int> d2(7);
	deque_<int> d3(100);
	deque_<int> d4(113, 7);

	deque<int> sd1;
	deque<int> sd2(7);
	deque<int> sd3(100);
	deque<int> sd4(113, 7);


	d1.push_front(1);
	d1.push_front(2);
	d1.push_front(3);
	d1.push_front(4);
	d1.push_front(5);
	d1.push_front(6);

	sd1.push_front(1);
	sd1.push_front(2);
	sd1.push_front(3);
	sd1.push_front(4);
	sd1.push_front(5);
	sd1.push_front(6);

	for (int i = 1; i < 4; ++i)
	{
		d1.push_front(i);
		d2.push_front(i);
		d3.push_front(i);
		d4.push_front(i);

		sd1.push_front(i);
		sd2.push_front(i);
		sd3.push_front(i);
		sd4.push_front(i);
	}
	cout << boolalpha;

	cout << _equal(d1.begin(), d1.end(), sd1.begin()) << endl;
	cout << _equal(d2.begin(), d2.end(), sd2.begin()) << endl;
	cout << _equal(d3.begin(), d3.end(), sd3.begin()) << endl;
	cout << _equal(d4.begin(), d4.end(), sd4.begin()) << endl;

	cout << d3 << endl;
	copy(sd3.cbegin(), sd3.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

void deque__tests_print()
{
	deque_<int> d1;
	deque_<int> d2(7);
	deque_<int> d3(100);
	deque_<int> d4(113, 7);

	d1.push_front(1);
	d1.push_front(2);
	d1.push_front(3);
	d1.push_front(4);
	d1.push_front(5);
	cout << d1 << endl;

	cout << d1 << endl;
	cout << d2 << endl;
	cout << d3 << endl;
	cout << d4 << endl;

	cout << d1 << endl;
	d1.push_front(7);
	cout << d1 << endl;

	for (int i = 1; i < 25; ++i)
	{
		d1.push_front(i);
		d2.push_front(i);
		d3.push_front(i);
		d4.push_front(i);
	}


	cout << "\n--------------------------------------------------------------------------\n";
	cout << d1 << endl;
	cout << d2 << endl;
	cout << d3 << endl;
	cout << d4 << endl;
}

int main()
{
	/*
	deque_<int> d1;
	deque_<int> d2(6);
	deque_<int> d3(100);
	*/
	//deque_<int> d3(6, 7);
	//cout << d3;
	deque__tests_print();
	deque__tests();

	
	deque_<int> d3(100);
//	d3.push_front(1);
//	d3.push_front(2);
//	d3.push_front(3);
//	d3.push_front(4);
	cout << d3 << endl;
	
	return 0;
}