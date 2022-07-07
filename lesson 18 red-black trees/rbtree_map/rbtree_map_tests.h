#pragma once

#include "rbtree_map.h"
#include <iostream>
#include <iterator>
#include <initializer_list>
#include <assert.h>

using namespace std;

void test1()
{
    rbtree_map<int, string> b1;

    b1[5] = "AAAAAAA";
    b1[5] = "BBBBBBB";
    b1[15] = "CCCCCCCC";
    b1[-7] = "DDDDDDDDDD";
    b1[0] = "EEEEEEE";
    b1[51] = "FFFFFF";
    b1[12] = "GGGGG";
    b1[6] = "HHHHHHHHHH";

    for (rbtree_map<int, string>::iterator it = b1.begin(); it != b1.end(); ++it)
    {
        cout << it->first << " : " << it->second << endl;
    }
}

void test2()
{
    rbtree_map<int, string> b1;

    b1[5] = "AAAAAAA";
    b1[5] = "BBBBBBB";
    b1[15] = "CCCCCCCC";
    b1[-7] = "DDDDDDDDDD";
    b1[0] = "EEEEEEE";
    b1[51] = "FFFFFF";
    b1[12] = "GGGGG";
    b1[6] = "HHHHHHHHHH";

    b1.print_inorder();
    b1.print_preorder();
    b1.print_levelorder();
}

void test3()
{
    rbtree_map<int, string> b1;

    b1[5] = "AAAAAAA";
    b1[5] = "BBBBBBB";
    b1[15] = "CCCCCCCC";
    b1[-7] = "DDDDDDDDDD";
    b1[0] = "EEEEEEE";
    b1[51] = "FFFFFF";
    b1[12] = "GGGGG";
    b1[6] = "HHHHHHHHHH";

    b1.print_inorder();
    b1.print_preorder();
    b1.print_levelorder();

    for (rbtree_map<int, string>::iterator it = b1.begin(); it != b1.end(); ++it)
    {
        cout << it->first << " : " << it->second << endl;
    }

    rbtree_map<int, string> b2(b1);

    b2.print_inorder();
    b2.print_preorder();
    b2.print_levelorder();

}

void test4()
{
    rbtree_map<int, string> b1;

    b1[-7] = "DDDDDDDDDD";
    b1[0] = "EEEEEEE";
    b1[5] = "AAAAAAA";
    b1[5] = "BBBBBBB";
    b1[6] = "HHHHHHHHHH";
    b1[12] = "FFFFFF";
    b1[15] = "GGGGG";
    b1[51] = "HHHHHHHHHH";
    b1[67] = "CCCCCCCC";

    for (rbtree_map<int, string>::iterator it = b1.begin(); it != b1.end(); )
    {
        auto it2 = next(it);
        b1.erase(it);
        b1.print_inorder();
        it = it2;
    }
}

void test5()
{
    rbtree_map<int, string, std::greater<int>> m({ { 14, "abc" }, { 7, "ssd" }, { 1455, "asfsf" }, { 95952, "pfsds" }, { -5, "sdfgsdf" }, { 4859, "sdfsdfsdfsf" } }, std::greater<int>{});
    vector<pair<int, string>> answers = { {95952, "pfsds"}, { 4859, "sdfsdfsdfsf" }, {1455, "asfsf"}, {14, "abc"}, {7, "ssd"},  {-5, "sdfgsdf"} };

    int i = 0;
    for (rbtree_map<int, string, std::greater<int>>::iterator it = m.begin(); it != m.end(); ++it)
    {
        pair<int, string> p = *it;
        assert(answers[i++] == p);
    }
};

void test6()
{
    rbtree_map<int, int> m;
    m.check_is_valid_bst();
}

void test7()
{
    rbtree_map<int, string> m;
    m[5] = "David";
    m[5] = "abc";

    m[12] = "abc12";
    m[18] = "abc132";
    m[2] = "abc15156";
    m[9] = "abc15";
    m[19] = "abc58181";
    m[17] = "abc5151";
    m[13] = "abc4949";
    m[3] = "sdfsabc12";
    m[1] = "ssdfsabc12";

    vector<int> k = { 5, 12, 9, 1, 15, 0 };

    assert(m.is_valid_bst());
    assert(m.size() == 10);
 
    for (int i = 0; i < m.size(); ++i)
    {
        rbtree_map<int, string>::iterator it = m.find(k[i]);
        m.erase(it);
        assert(m.is_valid_bst());
    }
    
}

void test8()
{
    rbtree_map<int, string> m;
    m[5] = "David";
    m[5] = "abc";

    m[12] = "abc12";
    m[18] = "abc132";
    m[2] = "abc15156";
    m[9] = "abc15";
    m[19] = "abc58181";
    m[17] = "abc5151";
    m[13] = "abc4949";
    m[3] = "sdfsabc12";
    m[1] = "ssdfsabc12";

    vector<int> answers = { 1, 2, 3, 5, 9, 12, 13, 17, 18, 19 };
    for (int i = 0; i <= m.size() + 1; ++i)
    {
        auto it = m.kth_element(i);
        if (i == 0 || i > m.size())
            assert(it == decltype(it)(nullptr));
        else
        {
            assert(it->first == answers[i-1]);
        }
    }
}

void test9()
{
    unique_BSTs b;
    vector<int> answers = { 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190 };

    for (int i = 0; i < 20; ++i)
    {
        assert(b.num_of_unique_bsts(i) == answers[i]);
    }
}

void test10()
{
    rbtree_map<int, int> m;
    m.check_zigzag_traversal();
}