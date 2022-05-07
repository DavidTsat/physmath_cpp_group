#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(a) a.cbegin(), a.cend()

template <typename T>
class mat
{
	size_t M;
	size_t N;

	T** v;
public:

	mat(const vector<vector<T>>& v2) : M(v2.size()), N(v2[0].size()), v(new T* [M])
	{
		// TODO
	}

	mat(size_t m, size_t n) : M(m), N(n), v(new T* [M])
	{
		// TODO
	}

	mat(const mat<T>& m2) : M(m2.M), N(m2.N), v(new T* [M])
	{
		// TODO
	}

	~mat()
	{
		// TODO
	}


	T*& operator[](size_t i)
	{
		// TODO
	}

	const T* operator[](size_t i) const
	{
		// TODO
	}

	pair<size_t, size_t> size() const
	{
		// TODO
	}

	vector<vector<T>> to_vec_of_vec() const
	{
		// TODO
	}

	vector<int> spiral_order() const
	{
		// TODO
	}

	void rotate()
	{
		// TODO
	}

	template <typename T>
	friend ostream& operator<<(ostream& os, const mat<T>& m)
	{
		// TODO
	}
};

template <typename T>
mat<T> generate_spiral_mat(int n)
{
	// TODO
}


void spiral_order_tests()
{
	vector<vector<int>> v1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	vector<vector<int>> v2 = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };

	vector<int> v1_answ = { 1, 2, 3, 6, 9, 8, 7, 4, 5 };
	vector<int> v2_answ = { 1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7 };

	vector<vector<vector<int>>> inputs = { v1, v2 };
	vector<vector<int>> outputs = { v1_answ, v2_answ };

	for (int i = 0; i < 2; ++i)
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

void run_tests()
{
	cout << "running spiral_order_tests" << endl;
	spiral_order_tests();
	cout << endl << "running spiral_mat_tests " << endl;
	spiral_mat_tests();
	cout << endl << "running rotate_tests" << endl;
	rotate_tests();
}
int main()
{
	run_tests();

	return 0;
}