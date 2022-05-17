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
		for (size_t i = 0; i < M; ++i) {
			v[i] = new T[N];
			copy_n(v2[i].begin(), N, v[i]);
		}
	}

	mat(size_t m, size_t n) : M(m), N(n), v(new T* [M])
	{
		for (size_t i = 0; i < M; ++i)
			v[i] = new T[N]{};
	}

	mat(const mat<T>& m2) : M(m2.M), N(m2.N), v(new T* [M])
	{
		for (size_t i = 0; i < M; ++i) {
			v[i] = new T[N];
			copy_n(m2[i], N, v[i]);
		}
	}

	~mat()
	{
		for_each_n(v, M, [](T* ptr) { delete[] ptr; });
		delete[] v;
	}


	T*& operator[](size_t i)
	{
		return v[i];
	}

	const T* operator[](size_t i) const
	{
		return v[i];
	}

	pair<size_t, size_t> size() const
	{
		return make_pair(M, N);
	}

	vector<vector<T>> to_vec_of_vec() const
	{
		vector<vector<T>> vec(M);
		for (size_t i = 0; i < M; ++i)
			vec[i].assign(v[i], v[i] + N);
		return vec;
	}

	vector<int> spiral_order() const
	{
		int inside = 0, mxinsideM = M - 1, mxinsideN = N - 1, ind = 0, x, y,
			layercnt = 2 * (N - 2) + 2 * M, cnt;
		if (N == 1 || M == 1)
			layercnt = N * M;
		short dx[]{ 0, 1, 0, -1 }, dy[]{ 1, 0, -1, 0 };
		vector<int> ans;
		while (inside <= mxinsideN && inside <= mxinsideM) {
			cnt = 0; x = inside; y = inside; ind = 0;
			while (++cnt <= layercnt) {
				ans.push_back(v[x][y]);
				if (x + dx[ind] > mxinsideM || x + dx[ind] < inside || \
					y + dy[ind] > mxinsideN || y + dy[ind] < inside)
					if (++ind > 3)
						ind = 0;
				x += dx[ind];
				y += dy[ind];
			}
			if (N == M && mxinsideM - inside == 2)
				layercnt = 1;
			else
				layercnt -= 8;
			++inside; --mxinsideM; --mxinsideN;
		}
		return ans;
	}

	void rotate()
	{
		int layer = N, first, last, i;
		T temp;
		while (layer > 0) {
			first = (N - layer) >> 1;
			last = layer + first - 1;
			for (i = 0; i < last - first; ++i) {
				temp = v[first][first + i];
				swap(temp, v[first + i][last]);
				swap(temp, v[last][last - i]);
				swap(temp, v[last - i][first]);
				v[first][first + i] = temp;
			}
			layer -= 2;
		}
	}

	template <typename T>
	friend ostream& operator<<(ostream& os, const mat<T>& m)
	{
		for_each_n(v, N, [](const T* ptr) {
			for_each_n(ptr, N, [](const T& elem) { cout << elem << ' '; });
			cout << '\n';
			});
	}
};

template <typename T>
mat<T> generate_spiral_mat(int n)
{
	mat<T> mt(n, n);
	int nsqr = n * n, cnt = 0, x = 0, y = 0, i = 0;
	short dx[]{ 0, 1, 0, -1 }, dy[]{ 1, 0, -1, 0 };
	while (++cnt <= nsqr) {
		mt[x][y] = cnt;
		if (x + dx[i] >= n || x + dx[i] < 0 || \
			y + dy[i] >= n || y + dy[i] < 0 || mt[x + dx[i]][y + dy[i]]) {
			if (++i > 3)
				i = 0;
		}
		x += dx[i];
		y += dy[i];
	}
	return mt;
}
