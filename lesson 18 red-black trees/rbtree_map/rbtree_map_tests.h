#pragma once

#include "rbtree_map.h"
#include <iostream>
#include <iterator>

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
