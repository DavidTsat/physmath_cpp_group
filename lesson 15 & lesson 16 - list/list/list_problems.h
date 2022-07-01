#pragma once
#include "_list.h"
#include <vector>
#include <assert.h>
#include <iterator>

using namespace std;

// Problem 1

class problem1_solution 
{
public:

    _list<int> addTwoNumbers(_list<int>& l1, _list<int>& l2) 
    {
        _list<int> r;
        // TODO
        return r;
    }
};

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

// Problem 2
class problem2_solution
{
public:
    _list<int> mergeTwoLists(const _list<int>& l1, const _list<int>& l2) {
        _list<int> r;

        // TODO

        return r;
    }
};

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

template <typename T>
void _list<T>::deleteDuplicates()
{
    // TODO
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

    cout << "\nproblem2_test2 passed" << endl;
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

    cout << "\nproblem2_test2 passed" << endl;
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