#pragma once
#include "_stack.h"
#include <string>

using namespace std;

class SolutionParentheses {
public:
    bool isValid(string s) {
      //TODO
    }
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class BSTIterator {
private:
    //TODO

public:
    BSTIterator(TreeNode* root) {
        //TODO
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        //TODO
    }

    /** @return the next smallest number */
    int next() {
        //TODO
    }
};

class SolutionCalculator {
public:
    int calculate(string ss) {
        //TODO
    }
};

#include <queue>

class SolutionGame {

public:
    int findTheWinner(int n, int k) {
       //TODO
    }
};