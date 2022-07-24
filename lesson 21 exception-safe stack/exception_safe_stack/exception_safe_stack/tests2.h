#pragma once
#include "solutions.h"
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

void _test1()
{
	vector<string> v = { "()", "()[]{}", "(]", "()()()(){{{}{{}{}}}}", "", "()()()(){{{}{{}{}}}]" };
	vector<bool> answers = { true, true, false, true, true, false };
	SolutionParentheses s;

	for (int i = 0; i < v.size(); ++i)
	{
		assert(s.isValid(v[i]) == answers[i]);
	}
}

void _test2()
{
	/*
	*		7
	*	   / \ 
	*     3  15
	*       /  \
	*      9   20
	*/
	/*
	["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
	[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
	Output
	[null, 3, 7, true, 9, true, 15, true, 20, false]

	bSTIterator.next();    // return 3
	bSTIterator.next();    // return 7
	bSTIterator.hasNext(); // return True
	bSTIterator.next();    // return 9
	bSTIterator.hasNext(); // return True
	bSTIterator.next();    // return 15
	bSTIterator.hasNext(); // return True
	bSTIterator.next();    // return 20
	bSTIterator.hasNext(); // return False
	*/
	TreeNode* root = new TreeNode(7, new TreeNode(3), new TreeNode(15, new TreeNode(9), new TreeNode(20)));
	BSTIterator* iter = new BSTIterator(root);

	assert(iter->next() == 3);
	assert(iter->next() == 7);
	assert(iter->hasNext() == true);
	assert(iter->next() == 9);
	assert(iter->hasNext() == true);
	assert(iter->next() == 15);
	assert(iter->hasNext() == true);
	assert(iter->next() == 20);
	assert(iter->hasNext() == false);

	delete iter;
}

void _test3()
{
	vector<string> v = { "3+2*2", " 3/2 ", " 3+5 / 2 ", "1787+2136/3/2*2", "1*2*3*4*5*6*7*8*9*10", "2*3*4" };
	vector<int> answers = { 7, 1, 5, 2499, 3628800, 24 };
	SolutionCalculator s;

	for (int i = 0; i < v.size(); ++i)
	{
		assert(answers[i] == s.calculate(v[i]));
	}
}

void _test4()
{
	SolutionGame s;
	assert(s.findTheWinner(5, 2) == 3);
	assert(s.findTheWinner(6, 5) == 1);
	assert(s.findTheWinner(5, 4) == 1);
}