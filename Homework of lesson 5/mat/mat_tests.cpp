#include <iostream>
#include <vector>
#include <algorithm>
#include "mat.h"

using namespace std;

#define all(a) a.begin(), a.end()
#define c_all(a) a.cbegin(), a.cend()

void spiral_order_tests()
{
	vector<vector<int>> v1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	vector<vector<int>> v2 = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
	vector<vector<int>> v3 = { {1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25} };

	vector<int> v1_answ = { 1, 2, 3, 6, 9, 8, 7, 4, 5 };
	vector<int> v2_answ = { 1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7 };
	vector<int> v3_answ = { 1,2,3,4,5,10,15,20,25,24,23,22,21,16,11,6,7,8,9,14,19,18,17,12,13 };

	vector<vector<vector<int>>> inputs = { v1, v2, v3 };
	vector<vector<int>> outputs = { v1_answ, v2_answ, v3_answ };

	for (int i = 0; i < 3; ++i)
	{
		mat<int> m(inputs[i]);
		vector<int> answ = m.spiral_order();
		cout << boolalpha << (answ == outputs[i]) << endl;
	}
}

void spiral_mat_tests()
{
	int v1 = 3;
	int v2 = 1;

	vector<vector<int>> v1_answ = { {1, 2, 3}, {8, 9, 4}, {7, 6, 5} };
	vector<vector<int>> v2_answ = { {1} };

	vector<int> inputs = { v1, v2 };
	vector<vector<vector<int>>> outputs = { v1_answ, v2_answ };

	for (int i = 0; i < 2; ++i)
	{
		mat<int> m = generate_spiral_mat<int>(inputs[i]); // FOR THIS TO WORK PROPERLY WE MUST HAVE A CORRECTLY IMPLEMENTED COPY CONSTRUCTOR
		vector<vector<int>> answ = m.to_vec_of_vec();
		cout << boolalpha << (answ == outputs[i]) << endl;
	}

}

void rotate_tests()
{
	vector<vector<int>> v1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	vector<vector<int>> v2 = { {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16} };
	vector<vector<int>> v3 = { {1} };

	vector<vector<int>> v1_answ = { {7, 4, 1}, {8, 5, 2}, {9, 6, 3} };
	vector<vector<int>> v2_answ = { {15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11} };
	vector<vector<int>> v3_answ = { {1} };

	vector<vector<vector<int>>> inputs = { v1, v2, v3 };
	vector<vector<vector<int>>> outputs = { v1_answ, v2_answ, v3_answ };

	for (int i = 0; i < 3; ++i)
	{
		mat<int> m(inputs[i]);
		m.rotate();
		vector<vector<int>> answ = m.to_vec_of_vec();
		cout << boolalpha << (answ == outputs[i]) << endl;
	}
}

void max_square_tests()
{
	vector<vector<char>> m1 = { {'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'} }; // 4
	vector<vector<char>> m2 = { {'1', '1', '1', '0', '0'}, {'1', '1', '1', '0', '0'}, {'1', '1', '1', '1', '1'}, {'0', '1', '1', '1', '1'}, {'0', '1', '1', '1', '1'}, {'0', '1', '1', '1', '1'} }; // 16
	vector<vector<char>> m3 = { {'1', '0', '1', '1', '0', '1'}, {'1', '1', '1', '1', '1', '1'}, {'0', '1', '1', '0', '1', '1'}, {'1', '1', '1', '0', '1', '0'}, {'0', '1', '1', '1', '1', '1'}, {'1', '1', '0', '1', '1', '1'} }; // 4
	vector<vector<char>> m4 = { {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'0', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'0', '1', '0', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1'}, {'0', '1', '1', '0', '1', '1', '0', '1', '0', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '0', '1'}, {'0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '0', '0', '1', '1', '0', '1', '1', '0', '1', '0', '1', '0', '1'}, {'1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '0', '1', '0', '1', '1', '0', '1', '0', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1'}, {'1', '1', '1', '0', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1'}, {'1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1'}, {'1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '0', '0', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1'}, {'1', '1', '0', '0', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '0', '1', '0', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '0', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1'}, {'1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '0', '1', '1', '1', '0', '1', '1', '0', '1', '1'}, {'1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1'}, {'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1'}, {'1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1'}, {'0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '0', '0', '1', '1', '1', '1', '0', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0'}, {'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1'}, {'1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '0', '1', '0', '1', '0', '0'}, {'0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '0', '0', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '0', '1'} }; // 64
	vector<vector<char>> m5 = { {'1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1'}, {'1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1', '0'}, {'1', '0', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '1', '0', '1'}, {'1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1'}, {'1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '0', '0', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1'} };  // 25
	vector<vector<char>> m6 = { {'0', '1', '0', '1', '0', '1', '0', '1', '1', '0', '1', '1', '0', '1', '0'}, {'0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '0'}, {'0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1'}, {'1', '0', '1', '1', '0', '1', '0', '0', '1', '1', '1', '0', '0', '0', '1'}, {'0', '1', '0', '1', '1', '1', '0', '1', '0', '1', '1', '0', '0', '1', '1'}, {'1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '0'}, {'0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0'}, {'0', '1', '1', '1', '0', '1', '0', '0', '0', '0', '1', '1', '1', '1', '1'}, {'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '0', '1', '1'}, {'0', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '1', '1', '0', '0', '0', '1', '1', '1', '0', '1', '0', '0', '1', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1'}, {'1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1'}, {'1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1'} }; // 9

	vector<vector<vector<char>>> inputs = { m1, m2, m3, m4, m5, m6 };
	vector<int> outputs = { 4, 16, 4, 64, 25, 9 };


	for (int i = 0; i < 6; ++i)
	{
		mat<char> m(inputs[i]);
		int answ = m.max_square();

		cout << boolalpha << (answ == outputs[i]) << endl;
	}

	mat<int> m_wrong_type({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
	try
	{
		m_wrong_type.max_square(); // with wrong type
	}
	catch (const logic_error& e)
	{
		//	cout << e.what() << endl;
		cout << boolalpha << true << endl;
	}
}

void num_islands_tests()
{
	vector<vector<char>> m1 = { {'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'} };
	vector<vector<char>> m2 = { {'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'} };

	vector<vector<vector<char>>> inputs = { m1, m2 };
	vector<int> outputs = { 1, 3 };

	for (int i = 0; i < 2; ++i)
	{
		mat<char> m(inputs[i]);
		int answ = m.num_islands();

		cout << boolalpha << (answ == outputs[i]) << endl;
	}

	mat<int> m_wrong_type({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
	try
	{
		m_wrong_type.num_islands(); // with wrong type
	}
	catch (const logic_error& e)
	{
		//	cout << e.what() << endl;
		cout << boolalpha << true << endl;
	}
}

void mat_mul_tests()
{
	vector<vector<int>> m1 = { {1,2,3}, {4,5,6}, {7,8,9}, {0,1,2}, {-1,4,5} };
	vector<vector<int>> m2 = { {1,4,5,7},{0,2,3,1},{1,2,-1,4} };
	vector<vector<int>> m_answ = { {4,14,8,21},{10,38,29,57},{16,62,50,93},{2,6,1,9},{4,14,2,17} };

	mat<int> answ = mat_mul(mat<int>(m1), mat<int>(m2));

	cout << boolalpha << (answ.to_vec_of_vec() == m_answ) << endl;

	try
	{
		mat_mul(mat<int>(m1), mat<int>(m1)); // with wrong sizes
	}
	catch (const logic_error& e)
	{
		//	cout << e.what() << endl;
		cout << boolalpha << true << endl;
	}
}

void run_tests()
{
	cout << "running spiral_order_tests" << endl;
	spiral_order_tests();
	cout << endl << "running spiral_mat_tests " << endl;
	spiral_mat_tests();
	cout << endl << "running rotate_tests" << endl;
	rotate_tests();
	cout << endl << "running max_square_tests" << endl;
	max_square_tests();
	cout << endl << "running num_islands_tests" << endl;
	num_islands_tests();
	cout << endl << "running mat_mul_tests" << endl;
	mat_mul_tests();
}

int main()
{
	run_tests();

	return 0;
}