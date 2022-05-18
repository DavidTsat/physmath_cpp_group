#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <limits>
#include <random>

using namespace std;

template <typename Cont>
void sort_for_cont(Cont& cont)
{
	sort(cont.begin(), cont.end());
}

template <typename SourceIt, typename DestIt>
DestIt copy_(SourceIt source_begin, SourceIt source_end, DestIt dest_begin)
{
	while (source_begin != source_end)
	{
		*dest_begin++ = *source_begin++;
	}
	return dest_begin;
}

template <typename SourceIt, typename DestIt>
DestIt move_(SourceIt source_begin, SourceIt source_end, DestIt dest_begin)
{
	while (source_begin != source_end)
	{
		*dest_begin++ = move(*source_begin++);
	}
	return dest_begin;
}

template <typename It, typename T>
T accumulate_(It begin, It end, T t)
{
	while (begin != end)
	{
		t += *begin++;
	}
	return t;
}

template <typename It, typename T, typename BinaryOp>
T accumulate_(It begin, It end, T t, BinaryOp op)
{
	while (begin != end)
	{
		t = op(*begin++, t);
	}
	return t;
}

template <typename It>
It adjacent_find_(It begin, It end)
{
	It n_begin = next(begin);
	
	while (n_begin != end)
	{
		if (*begin++ == *n_begin++)
		{
			return --begin;
		}
	//	++begin, ++n_begin;
	}
	return n_begin;
}

template <typename It, typename Eq = std::equal_to<typename std::iterator_traits<It>::value_type> >
It adjacent_find2_(It begin, It end, Eq eq = std::equal_to<typename std::iterator_traits<It>::value_type>{})
{
	It n_begin = next(begin);

	while (n_begin != end)
	{
		if (eq(*begin++, *n_begin++))
		{
			return --begin;
		}
		//	++begin, ++n_begin;
	}
	return n_begin;
}

void test_adjacent_find_()
{
	vector<int> v1({ 1, 2, -5, 4, 4, 3, 5 });
	vector<int> v2({ 1, 2, -5, 4, 3, 5, 7 });

	auto p1 = adjacent_find_(v1.cbegin(), v1.cend());
	auto p2 = adjacent_find_(v2.cbegin(), v2.cend());

	auto p1_std = std::adjacent_find(v1.cbegin(), v1.cend());
	auto p2_std = std::adjacent_find(v2.cbegin(), v2.cend());

	cout << "test_adjacent_find" << endl;

	cout << boolalpha << (p1 == p1_std) << endl;
	cout << boolalpha << (p2 == p2_std) << endl;

	cout << endl;
	auto p1_ = adjacent_find2_(v1.cbegin(), v1.cend());
	auto p2_ = adjacent_find2_(v2.cbegin(), v2.cend());

	cout << boolalpha << (p1_ == p1_std) << endl;
	cout << boolalpha << (p2_ == p2_std) << endl;

}

//std::find_first_of

// std::search
// https://en.cppreference.com/w/cpp/algorithm/search
// QUESTION: time complexity
// ANSWER: At most S*N comparisons where S = std::distance(s_first, s_last) and N = std::distance(first, last).

template<class ForwardIt1, class ForwardIt2>
constexpr ForwardIt1 search_(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last)
{
	while (true) { 
		ForwardIt1 it = first;
		for (ForwardIt2 s_it = s_first; ; ++it, ++s_it) {
			if (s_it == s_last) return first;
			if (it == last)  return last;
			if (!(*it == *s_it)) break;
		}
		++first;
	}
}

template <typename Container>
bool contains(const Container& cont, const std::string& s)
{
	return search_(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}

void test_search_()
{
	string str = "why waste time learning, when ignorance is instantaneous?";
	// str.find() can be used as well
	cout << boolalpha << contains(str, "learning") << endl   // true
	<< contains(str, "lemming") << '\n';  // false
}


template <typename SourceIt, typename DestIt>
DestIt partial_sum_(SourceIt begin, SourceIt end, DestIt dbegin)
{
	if (begin == end) dbegin;

	typename iterator_traits<SourceIt>::value_type t = *begin;

	*dbegin++ = *begin;

	while (++begin != end)
	{
		t += *begin;
		*dbegin++ = t;
	}
	return dbegin;
}

void partial_sum_test()
{
	vector<int> v = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }; // or std::vector<int>v(10, 2);

	cout << "The first 10 even numbers are: \n";
	partial_sum(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
	cout << endl;
	partial_sum_(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
}

template <typename It, typename T>
It lower_bound_(It begin, It end, const T& t)
{
	auto count = distance(begin, end);
	auto step = count / 2;

	while (count > 0)
	{
		It next_begin = next(begin, step);
		
		if (t > *next_begin)
		{
			begin = ++next_begin;
			count -= step + 1;
		}
		else
		{
			count = step;
		}
		step = count / 2;
	}
	return begin;
}

template <typename It, typename T>
It upper_bound_(It begin, It end, const T& t)
{
	auto count = distance(begin, end);
	auto step = count / 2;

	while (count > 0)
	{
		It next_begin = next(begin, step);

		if (t >= *next_begin)
		{
			begin = ++next_begin;
			count -= step + 1;
		}
		else
		{
			count = step;
		}
		step = count / 2;
	}
	return begin;
}

template <typename It, typename T>
It binary_search_(It begin, It end, const T& t)
{
	It p = lower_bound_(begin, end, t);
	if (p == end) return p;
	return *p == t ? p : end;
}

void lower_bound_test()
{
	vector<int> v = { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	partial_sum_(v.begin(), v.end(), v.begin());
	copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));

	auto p  = lower_bound(v.cbegin(), v.cend(), 9);		// 9
	auto p2 = lower_bound(v.cbegin(), v.cend(), 14);	// 15
	auto p3 = lower_bound(v.cbegin(), v.cend(), 140);	// end
	auto p4 = lower_bound(v.cbegin(), v.cend(), -140);	// 1

	cout << endl;
	cout << boolalpha << (*p == 9) << " : " << (*p2 == 15) << " : " << (p3 == v.cend()) << " : " << (*p4 == 1) << endl;

	auto _p  = lower_bound_(v.cbegin(), v.cend(), 9);		// 9
	auto _p2 = lower_bound_(v.cbegin(), v.cend(), 14);	    // 15
	auto _p3 = lower_bound_(v.cbegin(), v.cend(), 140);	    // end
	auto _p4 = lower_bound_(v.cbegin(), v.cend(), -140);	// 1

	cout << endl;
	cout << boolalpha << (*_p == 9) << " : " << (*_p2 == 15) << " : " << (_p3 == v.cend()) << " : " << (*_p4 == 1) << endl;
}

// std::rotate and insertion sort

// homework: implement std::rotate (insertion sort example), std::merge, std::partition, std::next_permutation

// Performs a left rotation on a range of elements.
// Specifically, std::rotate swaps the elements in the range[first, last) in such a way that 
// the element n_first becomes the first element of the new range and n_first - 1 becomes the last element.

template <typename T>
auto print_vec = [](const vector<T>& v) {for (const T& t : v) cout << t << ' '; cout << endl; };

void rotate_test1()
{
	vector<int> v{ 2, 4, 2, 0, 5, 10, 7, 3, 7, 1 };
	rotate(v.begin(), v.begin(), v.end());
	print_vec<int>(v);
	rotate(v.begin(), v.begin() + 1, v.end());
	print_vec<int>(v);
	rotate(v.begin(), v.begin() + 2, v.end());
	print_vec<int>(v);
}

void insertion_sort_test()
{
	vector<int> v{ 2, 4, 2, 0, 5, 10, 7, 3, 7, 1 };
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		auto greater_ = upper_bound_(v.begin(), it, *it);
		rotate(greater_, it, next(it));
	}

	print_vec<int>(v);
}

template <typename It>
void insertion_sort(It begin, It end)
{
	for (auto it = begin; it != end; ++it)
	{
		auto greater_ = upper_bound_(begin, it, *it);
		rotate(greater_, it, next(it));
	}
}

// quick sort
template <typename It, typename Pred>
It find_if_not_(It begin, It end, Pred pred)
{
	for (; begin != end; ++begin)
	{
		if (!pred(*begin))
		{
			return begin;
		}
	}
	return end;
}

void partition_tests1()
{
	vector<int> v1{ 1, 2, 3, 4, 5, 6, 7 };
	vector<int> v2{ 2, 4, 2, 0, 5, 10, 7, 3, 7, 1 };

	partition(v1.begin(), v1.end(), [v1](int a) {return a > *v1.begin(); });
	print_vec<int>(v1);

	partition(v2.begin(), v2.end(), [v2](int a) {return a > *v2.begin(); });
	print_vec<int>(v2);
}

template <typename It, typename Pred>
It partition_(It begin, It end, Pred pred)
{
	begin = find_if_not_(begin, end, pred);
	if (begin == end) return begin;

	for (It it = next(begin); it != end; ++it)
	{
		if (pred(*it))
		{
			iter_swap(begin, it);
			++begin;
		}
	}
	return begin;
}

void partition_tests2()
{
	vector<int> v1{ 1, 2, 3, 4, 5, 6, 7 };
	vector<int> v2{ 2, 4, 2, 0, 5, 10, 7, 3, 7, 1 };

	partition_(v1.begin(), v1.end(), [v1](int a) {return a > *v1.begin(); });
	print_vec<int>(v1);

	partition_(v2.begin(), v2.end(), [v2](int a) {return a > *v2.begin(); });
	print_vec<int>(v2);
}


template <typename It>
void quick_sort_(It begin, It end)
{
	if (distance(begin, end) <= 1) return;

	const typename iterator_traits<It>::value_type pivot_point = *(end-1);

//	It mid_point_it = next(begin, distance(begin, end) / 2);
//	nth_element(begin, mid_point_it, end);

	It mid_point_it = partition_(begin, end-1, [pivot_point](const typename iterator_traits<It>::value_type& v) {return v < pivot_point; });
	//if (mid_point_it == end - 1) return;

	iter_swap(mid_point_it, end - 1);

	quick_sort_(begin, mid_point_it);
	quick_sort_(mid_point_it+1, end);
}

void test_quick_sort()
{
	vector<int> v1{ 1, 2, 3, 4, 5, 6, 7 };
	vector<int> v2{ 2, 4, 2, 0, 5, 10, 7, 3, 7, 1 };
	vector<int> v3{ v1.rbegin(), v1.rend() };
	vector<int> v4{ 20, 4, 21, 0, 5, 6, 74, 3, 7, 1 };

	quick_sort_(v1.begin(), v1.end());
	quick_sort_(v2.begin(), v2.end());
	quick_sort_(v3.begin(), v3.end());
	quick_sort_(v4.begin(), v4.end());

	print_vec<int>(v1);
	print_vec<int>(v2);
	print_vec<int>(v3);
	print_vec<int>(v4);
}

// merge, heap

/*
Пусть дан некоторый отсортированный в неубывающем порядке вектор целых чисел {-8, -5, -3, 0, 1, 4, 4, 5, 7, 9}
Требуется написать алгоритм, который за линейное время вернет отсортированный вектор квадратов элементов входного вектора:
{-8, -5, -3, 0, 1, 4, 4, 5, 7, 9} -> {0, 1, 9, 16, 16, 25, 25, 49, 64, 81}
*/

template <typename SourceIt1, typename SourceIt2, typename DestIt>
void merge_(SourceIt1 sbegin1, SourceIt1 send1, SourceIt2 sbegin2, SourceIt2 send2, DestIt dbegin)
{
	for (; sbegin1 != send1;)
	{
		if (sbegin2 == send2)
		{
			copy(sbegin1, send1, dbegin);
			return;
		}
		if (*sbegin1 < *sbegin2)
		{
			*dbegin++ = *sbegin1++;
		}
		else
		{
			*dbegin++ = *sbegin2++;
		}
	}
	copy(sbegin2, send2, dbegin);
	return;
}

vector<int> square_sort_with_std(vector<int>& v)
{
	vector<int> r;
	r.reserve(v.size());

	/*
	auto it = v.cbegin();

	for (; it != v.cend(); ++it)
	{
		if (*it >= 0)
		{
			break;
		}
	}
	*/

	auto it = find_if(v.cbegin(), v.cend(), [](int x) { return x >= 0; });
	for_each(v.begin(), v.end(), [](int& a) {a *= a; });
	merge_(make_reverse_iterator(it), make_reverse_iterator(v.cbegin()), it, v.cend(), back_inserter(r));
	
	return r;
}

void square_sort_tests()
{
	vector<int> v1 = { -8, -5, -3, 0, 1, 4, 4, 5, 7, 9 };
	vector<int> v2 = { 0, 1, 4 };
	vector<int> v3 = { -5, -3 };
	vector<int> v4;

	vector<int> v1_answer = { 0, 1, 9, 16, 16, 25, 25, 49, 64, 81 };
	vector<int> v2_answer = { 0, 1, 16 };
	vector<int> v3_answer = { 9, 25 };
	vector<int> v4_answer = {};

	vector<vector<int>> inputs = { v1, v2, v3, v4 };
	vector<vector<int>> outputs = { v1_answer, v2_answer, v3_answer, v4_answer };

	for (int i = 0; i < inputs.size(); ++i)
	{
		vector<int> answ = square_sort_with_std(inputs[i]);

		cout << boolalpha << (outputs[i] == answ) << endl;
	}
}

//vector<int> v = { -1,4,0,7,-5,2,6 };

template <typename It>
void merge_sort_(It begin, It end)
{
	if (distance(begin, end) > 1)
	{
		It mid_point = next(begin, distance(begin, end) / 2);
		merge_sort_(begin, mid_point);
		merge_sort_(mid_point, end);

		
		vector<iterator_traits<It>::value_type> vr;
		//vector<iterator_traits<It>::value_type> vr = merge2(begin, mid_point, end);
		merge_(begin, mid_point, mid_point, end, back_inserter(vr));
		copy(vr.cbegin(), vr.cend(), begin);
		
		//merge_(begin, mid_point, mid_point, end, begin); // WHY WE CAN'T ?
	}
}

static std::vector<int> generate_data(size_t size)
{
	using value_type = int;
	// We use static in order to instantiate the random engine
	// and the distribution once only.
	// It may provoke some thread-safety issues.
	static std::uniform_int_distribution<value_type> distribution(
//		-100, 100
		std::numeric_limits<value_type>::min(),
		std::numeric_limits<value_type>::max()
	//	INT_MIN/10000, INT_MAX/ 10000
	);
	static std::default_random_engine generator;

	std::vector<value_type> data(size);
	std::generate(data.begin(), data.end(), []() { return distribution(generator); });
	return data;
}

void test_merge_sort()
{
//	merge_sort_(v.begin(), v.end());
	
	for (int i = 0; i < 10; ++i)
	{
		vector<int> v = generate_data(1000);
		vector<int> v2(v);
//		merge_sort_(v.begin(), v.end());
		//quick_sort_
		quick_sort_(v.begin(), v.end());
	//	insertion_sort(v.begin(), v.end());
		sort(v2.begin(), v2.end());
		cout << boolalpha << (v == v2) << endl;
	//	print_vec<int>(v2);
	//	print_vec<int>(v);
	//	cout << endl;
	}
	
}