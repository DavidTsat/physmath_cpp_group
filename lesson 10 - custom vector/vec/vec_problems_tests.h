#pragma once
#include "vec.h"
#include <vector>
#include <iostream>

using namespace std;

void unique_paths_with_obstacles_tests()
{
    sol_unique_paths_with_obstacles s;

    vector<vector<int>> v1 = { {0,0,0},{0,1,0},{0,0,0} };
    vector<vector<int>> v2 = { {0,0,0,0},{0,0,1,0},{0,0,0,0} };
    vector<vector<int>> v3 = { {0,0}, {0,0} };
    vector<vector<int>> v4 = { {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0} };
    vector<vector<int>> v5 = { {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0} };
    vector<vector<int>> v6 = { {0} };
    vector<vector<int>> v7 = { {1,0} };
    vector<vector<int>> v8 = { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} };

    vector<vector<vector<int>>> inputs = { v1, v2, v3, v4, v5, v6, v7, v8 };
    vector<int> outputs = {2,4,2,15,70,1,0,0};

    for (int i = 0; i < inputs.size(); ++i)
    {
        vec<vec<int>> v;
        v.reserve(inputs[i].size());

        for (int j = 0; j < inputs[i].size(); ++j)
        {
            v.push_back(inputs[i][j]);
        }
        int r = s.unique_paths_with_obstacles(v);
        cout << boolalpha << (r == outputs[i]) << endl;
    }
}