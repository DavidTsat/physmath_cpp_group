#include "class_list"
#include <iostream>
#include <assert.h>
#include <iterator>
#include <vector>

using namespace std;

void test1()
{
	_list<int> l(74, 7);
	cout << l.size() << endl;
	_list<int> l2;
	_list<int> l3(1);
}

void test2()
{
	_list<int> l(37, 7);

	for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << ' ';
	}

	cout << endl;

	_list<int> l2(1);

	for (_list<int>::iterator it = l2.begin(); it != l2.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;
}


void test3()
{
	_list<int> l(37, 7);

	assert((l.end() - l.begin()) == 37);
	assert((l.end() - l.begin()) == l.size());
	assert(std::distance(l.begin(), l.end()) == 37);

	cout << (l.end() - l.begin()) << endl;

	_list<int> l2;

	assert((l2.end() - l2.begin()) == 0);
	assert((l2.end() - l2.begin()) == l2.size());
	assert(std::distance(l2.begin(), l2.end()) == 0);
}

void test4()
{
	_list<int> l(37, 7);
	_list<int> l2(14, -5);

	for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;

	l.swap(l2);

	assert(l.size() == 14);
	assert(l2.size() == 37);

	for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;
}

void test5()
{
	_list<int> l(37, 7);
	_list<int> l2(l);

	for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;

	for (_list<int>::iterator it = l2.begin(); it != l2.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;
}

void test6()
{
	_list<int> l(37, 7);
	_list<int> l2(move(l));

	assert(l.size() == 0);
	assert(distance(l.cbegin(), l.cend()) == 0);

	assert(l2.size() == 37);
	assert(distance(l2.cbegin(), l2.cend()) == 37);

	for (_list<int>::iterator it = l2.begin(); it != l2.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;
}

struct A
{
	int c;
	static int k;
	static int q;

	A(int cc = 8) : c(cc) {}
	A(const A& a) : c(a.c) { ++q; }
	A(A&& a) noexcept : c(a.c) {}
	~A() { ++k; }
};

int A::k = 0;
int A::q = 0;

void test7()
{
	_list<A> l(37, 7);
	_list<A> l2(41, 14);

	//  cout << A::k <<endl;
	 // cout << A::q <<endl;

	int initial_k = A::k;
	int initial_q = A::q;
	cout << endl;

	l2 = l;

	//assert(A::k == initial_k + 41); // for tail I create additional A, and A::k == initial_k + 42
	assert(A::q == initial_q + 37);
	//  cout << l2.size() <<endl;
	//  cout << A::k <<endl;
	//  cout << A::q <<endl;

	  /*
	  for (_list<A>::iterator it = l2.begin(); it != l2.end(); ++it)
	  {
		cout << (*it).c << ' ';
	  }
	  */
	  // assert(l2.size() == 37);
	   //assert(A::k == 41);
}

void test8()
{
	_list<A> l(37, 7);
	_list<A> l2(41, 14);
	int initial_q = A::q;
	l2 = move(l);
	assert(A::q == initial_q);

	for (_list<A>::iterator it = l2.begin(); it != l2.end(); ++it)
	{
		cout << (*it).c << ' ';
	}
}

void test9()
{
	_list<int> l;
	for (int i = 0; i < 10; ++i)
	{
		l.push_back(i);
	}

	cout << l.size() << endl;
	cout << std::distance(l.cbegin(), l.cend()) << endl;

	for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << ' ';
	}
}

void test10()
{
	_list<int> l;
	for (int i = 0; i < 10; ++i)
	{
		l.push_back(i);
	}
	for (int i = 0; i < 10; ++i)
	{
		l.pop_back();
	}
	cout << l.size() << endl;
	for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << ' ';
	}
}

void test11()
{
	_list<int> l;
	for (int i = 0; i < 10; ++i)
	{
		l.push_back(i);
	}

	auto it = l.begin();
	for (int i = 0; i < 10; ++i)
	{
		l.insert(++it, i);
	}

	//  l.insert(--l.end(), 15);

	for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl << l.size() << endl;
	/*
	for (int i = 0; i < 10; i+=2)
	{
	}
	*/
}


void test12()
{
	_list<int> l;

	for (int i = 0; i < 10; ++i)
	{
		l.push_back(i);
	}

	l.remove_if([](int val) { return !(val & 1); });
	//   l.remove_if1([](int val){ return val == 0;});

	for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << ' ';
	}
}

void test13()
{
	_list<int> l1;
	_list<int> l2;
	_list<int> l3(1);

	for (int i = 0; i < 10; ++i)
	{
		l1.push_back(i);
	}

	l1.reverse();
	l2.reverse();
	l3.reverse();

	for (_list<int>::iterator it = l1.begin(); it != l1.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;
	for (_list<int>::iterator it = l2.begin(); it != l2.end(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;
	for (_list<int>::iterator it = l3.begin(); it != l3.end(); ++it)
	{
		cout << *it << ' ';
	}
}

void test14()
{
	_list<int> l;
	for (int i = 0; i < 100; ++i)
	{
		l.push_back(i);
		assert(l.size() == i + 1);
		assert(std::distance(l.cbegin(), l.cend()) == i + 1);
	}
	l.reverse();
	int i = 99;
	for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		assert(i-- == *it);
	}
}

void problem1_test1()
{
	/*
	Input: l1 = [2, 4, 3], l2 = [5, 6, 4]
	Output : [7, 0, 8]
	Explanation : 342 + 465 = 807.
	*/
	vector<int> answers = { 7,0,8 };

	_list<int> l1;
	_list<int> l2;

	l1.push_back(2);
	l1.push_back(4);
	l1.push_back(3);

	l2.push_back(5);
	l2.push_back(6);
	l2.push_back(4);

	problem1_solution s;

	_list<int> r = s.addTwoNumbers(l1, l2);

	assert(r.size() == answers.size());

	int i = 0;
	for (auto it = r.cbegin(); it != r.cend(); ++it)
	{
		assert(*it == answers[i++]);
		//      cout << *it << ' ';
	}
	cout << "problem1_test1 passed" << endl;
}

void problem1_test2()
{
	/*
	Input: l1 = [0], l2 = [0]
	Output: [0]
	*/
	vector<int> answers = { 0 };
	_list<int> l1;
	_list<int> l2;

	l1.push_back(0);
	l2.push_back(0);

	problem1_solution s;

	_list<int> r = s.addTwoNumbers(l1, l2);

	assert(r.size() == answers.size());

	int i = 0;
	for (auto it = r.cbegin(); it != r.cend(); ++it)
	{
		assert(*it == answers[i++]);
		//     cout << *it << ' ';
	}
	cout << "problem1_test2 passed" << endl;
}

void problem1_test3()
{
	/*
	Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
	Output: [8,9,9,9,0,0,0,1]
	*/
	vector<int> answers = { 8,9,9,9,0,0,0,1 };
	_list<int> l1;
	_list<int> l2;

	for (int i = 0; i < 7; ++i)
	{
		l1.push_back(9);
	}
	for (int i = 0; i < 4; ++i)
	{
		l2.push_back(9);
	}

	problem1_solution s;

	_list<int> r = s.addTwoNumbers(l1, l2);

	assert(r.size() == answers.size());

	int i = 0;
	for (auto it = r.cbegin(); it != r.cend(); ++it)
	{
		assert(*it == answers[i++]);
		//   cout << *it << ' ';
	}
	cout << "problem1_test3 passed" << endl;
}

void problem2_test1()
{
	/*
	Input: list1 = [1,2,4], list2 = [1,3,4, 8]
	Output: [1,1,2,3,4,4,8]
	*/
	vector<int> answers = { 1,1,2,3,4,4,8 };
	_list<int> l1;
	_list<int> l2;

	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(4);

	l2.push_back(1);
	l2.push_back(3);
	l2.push_back(4);
	l2.push_back(8);

	problem2_solution s;
	_list<int> r = s.mergeTwoLists(l1, l2);

	assert(r.size() == answers.size());

	int i = 0;
	for (auto it = r.cbegin(); it != r.cend(); ++it)
	{
		assert(*it == answers[i++]);
		//     cout << *it << ' ';
	}

	cout << "problem2_test1 passed" << endl;
}

void problem2_test2()
{
	/*
	Input: list1 = [], list2 = []
	Output: []
	*/
	vector<int> answers = { };
	_list<int> l1;
	_list<int> l2;


	problem2_solution s;
	_list<int> r = s.mergeTwoLists(l1, l2);

	assert(r.size() == answers.size());

	int i = 0;
	for (auto it = r.cbegin(); it != r.cend(); ++it)
	{
		assert(*it == answers[i++]);
		//    cout << *it << ' ';
	}

	cout << "problem2_test2 passed" << endl;
}

void problem2_test3()
{
	/*
	Input: list1 = [], list2 = [1]
	Output: [1]
	*/
	vector<int> answers = { 1 };
	_list<int> l1;
	_list<int> l2;

	l2.push_back(1);

	problem2_solution s;
	_list<int> r = s.mergeTwoLists(l1, l2);

	assert(r.size() == answers.size());

	int i = 0;
	for (auto it = r.cbegin(); it != r.cend(); ++it)
	{
		assert(*it == answers[i++]);
		//    cout << *it << ' ';
	}

	cout << "problem2_test3 passed" << endl;
}

void problem3_test1()
{
	/*
	Input:  [1,2,3,3,4,4,5,5]
	Output: [1,2]
	*/
	vector<int> answers = { 1, 2 };
	_list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(3);
	l.push_back(4);
	l.push_back(4);
	l.push_back(5);
	l.push_back(5);

	l.deleteDuplicates();

	assert(l.size() == answers.size());

	int i = 0;
	for (auto it = l.cbegin(); it != l.cend(); ++it)
	{
		assert(*it == answers[i++]);
		//    cout << *it << ' ';
	}

	//  testing "prev" pointers with reversed list
	i = answers.size() - 1;
	l.reverse();
	for (auto it = l.cbegin(); it != l.cend(); ++it)
	{
		assert(*it == answers[i--]);
		//    cout << *it << ' ';
	}

	cout << "\nproblem3_test1 passed" << endl;
}

void problem3_test2()
{
	/*
	Input:  [1,1,1,2,3]
	Output: [2,3]
	*/
	vector<int> answers = { 2,3 };
	_list<int> l;
	l.push_back(1);
	l.push_back(1);
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	l.deleteDuplicates();

	assert(l.size() == answers.size());

	int i = 0;
	for (auto it = l.cbegin(); it != l.cend(); ++it)
	{
		assert(*it == answers[i++]);
		//       cout << *it << ' ';
	}

	//  testing "prev" pointers with reversed list
	i = answers.size() - 1;
	l.reverse();
	for (auto it = l.cbegin(); it != l.cend(); ++it)
	{
		assert(*it == answers[i--]);
		//     cout << *it << ' ';
	}

	cout << "\nproblem3_test2 passed" << endl;
}

void problem3_test3()
{
	/*
	Input:  [1,1,1,2,3,3,3,3,3]
	Output: [2]
	*/
	vector<int> answers = { 2 };
	_list<int> l;
	l.push_back(1);
	l.push_back(1);
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(3);
	l.push_back(3);
	l.push_back(3);
	l.push_back(3);

	l.deleteDuplicates();

	assert(l.size() == answers.size());

	int i = 0;
	for (auto it = l.cbegin(); it != l.cend(); ++it)
	{
		assert(*it == answers[i++]);
		//   cout << *it << ' ';
	}

	//  testing "prev" pointers with reversed list
	i = answers.size() - 1;
	l.reverse();
	for (auto it = l.cbegin(); it != l.cend(); ++it)
	{
		assert(*it == answers[i--]);
		//   cout << *it << ' ';
	}

	cout << "\nproblem3_test3 passed" << endl;
}

int main() {

	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();
	test12();


	test13();
	test14();

	problem1_test1();
	problem1_test2();
	problem1_test3();


	problem2_test1();
	problem2_test2();
	problem2_test3();

	problem3_test1();
	problem3_test2();
	problem3_test3();

}