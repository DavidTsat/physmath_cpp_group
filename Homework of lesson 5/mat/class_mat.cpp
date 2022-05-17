#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

template <typename T>
class mat
{
	size_t M = 0;
	size_t N = 0;

	T** v = nullptr;

	constexpr static short dx[]{ 0, 1, 0, -1 }, dy[]{ 1, 0, -1, 0 };
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

	mat& operator=(const mat& other)
	{
		mat temp(other);
		swap_(*this, temp);
	}

	mat(mat&& other) noexcept
	{
		swap_(*this, other);
	}

	mat& operator=(mat&& other)
	{
		M = 0;
		N = 0;
		v = nullptr;
		swap_(*this, other);
	}

	template <typename F>
	friend void swap_(mat<F>&, mat<F>&);

	T*& operator[](size_t i)
	{
		return v[i];
	}

	const T* operator[](size_t i) const
	{
		return v[i];
	}

	constexpr pair<size_t, size_t> size() const
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

	template <typename F>
	friend ostream& operator<<(ostream&, const mat<F>&);

	/*
	* Algorithmic Problems
	*/

	template <typename F>
	friend mat<F> generate_spiral_mat(int);

	template <typename F>
	friend mat<F> mat_mul(const mat<F>&, const mat<F>&);

	vector<int> spiral_order() const
	{
		int inside = 0, mxinsideM = M - 1, mxinsideN = N - 1, ind = 0, x, y,
			layercnt = 2 * (N - 2) + 2 * M, cnt;
		if (N == 1 || M == 1)
			layercnt = N * M;
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

	int max_square() const
	{
		if (!is_same<T, char>::value)
			throw logic_error("incorrect type! ");
		size_t ans = 0, layer, k;
		bool go;
		for (size_t i = 0; i < M; ++i)
			for (size_t j = 0; j < N; ++j)
				if (v[i][j] == '1') {
					layer = 1;
					go = true;
					while (i + layer - 1 < M && j + layer - 1 < N) {
						for (k = i; k < i + layer; ++k)
							if (v[k][j + layer - 1] != '1') {
								go = false;
								break;
							}
						if (!go)
							break;
						for (k = j + layer - 2; k >= j; --k)
							if (v[i + layer - 1][k] != '1') {
								go = false;
								break;
							}
						if (!go)
							break;
						ans = max(ans, layer);
						++layer;
					}
				}
		return ans * ans;
	}

	int num_islands()
	{
		size_t x, y;
		int ans = 0;
		queue<pair<size_t, size_t>> q;
		for (size_t i = 0; i < M; ++i)
			for (size_t j = 0; j < N; ++j)
				if (v[i][j] == '1') {
					++ans;
					v[i][j] = '0';
					q.push(make_pair(i, j));
					while (!q.empty())
					{
						x = q.front().first;
						y = q.front().second;
						q.pop();
						for (size_t ind = 0; ind < 4; ++ind)
							if (x + dx[ind] < M && x + dx[ind] >= 0 && \
								y + dy[ind] < N && y + dy[ind] >= 0 && \
								v[x + dx[ind]][y + dy[ind]] == '1')
							{
								v[x + dx[ind]][y + dy[ind]] = '0';
								q.push(make_pair(x + dx[ind], y + dy[ind]));
							}
					}
				}
		return ans;
	}
};

template <typename F>
mat<F> generate_spiral_mat(int n)
{
	mat<F> mt(n, n);
	int nsqr = n * n, cnt = 0, x = 0, y = 0, i = 0;
	while (++cnt <= nsqr) {
		mt[x][y] = cnt;
		if (x + mat<F>::dx[i] >= n || x + mat<F>::dx[i] < 0 || \
			y + mat<F>::dy[i] >= n || y + mat<F>::dy[i] < 0 || mt[x + mat<F>::dx[i]][y + mat<F>::dy[i]]) {
			if (++i > 3)
				i = 0;
		}
		x += mat<F>::dx[i];
		y += mat<F>::dy[i];
	}
	return mt;
}

template <typename F>
mat<F> mat_mul(const mat<F>& m1, const mat<F>& m2)
{
	if (m1.N != m2.M)
		throw logic_error("Bad shapes! ");
	mat<F> ans(m1.M, m2.N);
	for (size_t i = 0; i < m1.M; ++i)
		for (size_t j = 0; j < m2.N; ++j)
			for (size_t k = 0; k < m1.N; ++k)
				ans[i][j] += m1[i][k] * m2[k][j];
	return ans;
}

template <typename F>
ostream& operator<<(ostream& os, const mat<F>& m)
{
	for_each_n(m.v, m.M, [&m, &os](const F* ptr) {
		for_each_n(ptr, m.N, [&os](const F& elem) { os << elem << ' '; });
		os << '\n';
		});
	return os;
}

template <typename F>
void swap_(mat<F>& m1, mat<F>& m2)
{
	swap(m1.M, m2.M);
	swap(m1.N, m2.N);
	swap(m1.v, m2.v);
}
