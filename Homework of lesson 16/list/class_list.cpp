#include <type_traits>
#include <iterator>
#include <stdexcept>
#include <functional>

template<typename T>
class _list;

namespace _for_impl {
	template<typename T, bool Is_const>
	class _list_iterator_base;

	template<typename T>
	struct _list_node {
		T val;
		_list_node* prev, * next;

		_list_node() : prev(nullptr), next(nullptr) {}

		_list_node(const T& value, _list_node* p) : val(value), prev(p) {
			if (p)
				p->next = this;
		}

		_list_node(const T& value, _list_node* p, _list_node* n) : val(value), prev(p), next(n) {
			if (p)
				p->next = this;
			if (n)
				n->prev = this;
		}

		template<bool b>
		operator _list_iterator_base<T, b>() {
			_list_iterator_base<T, b> it(this);
			return it;
		}
	};

	template<typename T, bool Is_const>
	class _list_iterator_base {
		friend class _list<T>;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = typename std::conditional<Is_const, const T, T>::type;
		using pointer = value_type*;
		using reference = value_type&;

		_list_node<T>* it;
		_list_iterator_base() : it(nullptr) {}

		_list_iterator_base(_list_node<T>* It) : it(It) {}

		operator _list_iterator_base<T, true>() {
			return _list_iterator_base<T, true>(it);
		}

		value_type& operator*() const {
			if (it->next == nullptr)
				throw std::runtime_error("error: attempt to dereference a past - the - end iterator.");
			return it->val;
		}

		value_type* operator->() const {
			if (it->next == nullptr)
				throw std::runtime_error("error: attempt to dereference a past - the - end iterator.");
			return &it->val;
		}

		_list_iterator_base& operator++() {
			it = it->next;
			return *this;
		}

		_list_iterator_base operator++(int) {
			it = it->next;
			return it->prev;
		}

		_list_iterator_base& operator--() {
			it = it->prev;
			return *this;
		}

		_list_iterator_base operator--(int) {
			it = it->prev;
			return it->next;
		}

		template<bool b>
		bool operator==(_list_iterator_base<T, b> other) const noexcept {
			return it == other.it;
		}

		template<bool b>
		bool operator!=(_list_iterator_base<T, b> other) const noexcept {
			return it != other.it;
		}
	};

	template<typename T, bool b1, bool b2>
	typename _list<T>::size_type operator-(_list_iterator_base<T, b1> first, _list_iterator_base<T, b2> last)
	{
		typename _list<T>::size_type ans = 0;
		while (first != last) {
			++last;
			++ans;
		}
		return ans;
	}
};

template<typename T>
class _list {
public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = T&;
	using const_reference = const T&;
	using iterator = _for_impl::_list_iterator_base<T, false>;
	using const_iterator = _for_impl::_list_iterator_base<T, true>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
private:
	using node = _for_impl::_list_node<T>;

	size_t _size;
	node* head;
	node* tail;

public:
	_list(size_type sz = 0u, const T& value = T()) : head(new node), tail(head) {
		insert(cend(), sz, value);
	}

	_list(const _list& other) : head(new node), tail(head) {
		insert(cend(), other.cbegin(), other.cend());
	}

	_list(_list&& other) : _size(other._size), head(other.head), tail(other.tail) {
		other._size = 0;
		other.head = other.tail = new node;
	}

	_list& operator=(const _list& other) {
		if (this != &other) {
			_list temp(other);
			swap(temp);
		}
		return *this;
	}

	_list& operator=(_list&& other) {
		swap(other);
		other.clear();
		return *this;
	}

	~_list() {
		erase(cbegin(), cend());
		delete tail;
	}

	void assign(size_type count, const T& value)
	{
		_for_impl::_list_node<T>* it = head;
		for (size_type i = 0; i < std::min(count, _size); ++i, it = it->next)
			it->val = value;
		resize(count, value);
	}

	template<typename InputIt>
	void assign(InputIt first, InputIt last)
	{
		_for_impl::_list_node<T>* it = head;
		for (size_type i = 0; i < _size && first != last; ++i, it = it->next) {
			it->val = *first;
			++first;
		}
		if (first != last)
			insert(cend(), first, last);
	}

	void assign(std::initializer_list<T> ilist)
	{
		assign(ilist.begin(), ilist.end());
	}

	reference front() const { return head->val; }

	reference back() const { return tail->prev->val; }

	iterator begin() noexcept { return head; }

	const_iterator begin() const noexcept { return head; }

	const_iterator cbegin() const noexcept { return head; }

	iterator end() noexcept { return tail; }

	const_iterator end() const noexcept { return tail; }

	const_iterator cend() const noexcept { return tail; }

	reverse_iterator rbegin() noexcept { return iterator(tail); }

	const_reverse_iterator rbegin() const noexcept { return const_iterator(tail); }

	const_reverse_iterator crbegin() const noexcept { return const_iterator(tail); }

	reverse_iterator rend() noexcept { return iterator(head); }

	const_reverse_iterator rend() const noexcept { return const_iterator(head); }

	const_reverse_iterator crend() const noexcept { return const_iterator(head); }

	bool empty() const noexcept { return _size == 0; }

	size_type size() const noexcept { return _size; }

	void clear()
	{
		erase(head, tail);
		_size = 0;
		head = tail;
		tail->prev = nullptr;
	}

private:
	void put_node(node* pos, node* new_node)
	{
		new_node->prev = pos->prev;
		if (pos != head)
			pos->prev->next = new_node;
		else
			head = new_node;
		new_node->next = pos;
		pos->prev = new_node;
		++_size;
	}

	void put_range(node* pos, node* first, node* last) // last is included
	{
		first->prev = pos->prev;
		if (pos != head)
			pos->prev->next = first;
		else
			head = first;
		last->next = pos;
		pos->prev = last;
		while (first->next) {
			first = first->next;
			++_size;
		}
	}

	void take_node(node* pos)
	{
		if (pos != head)
			pos->prev->next = pos->next;
		else
			head = pos->next;
		pos->next->prev = pos->prev;
		--_size;
	}

	void take_range(node* first, node* last)
	{
		if (first != head)
			first->prev->next = last;
		else
			head = last;
		last->prev = first->prev;
		while (first != last) {
			first = first->next;
			--_size;
		}
	}

public:
	iterator insert(const_iterator pos, const_reference value)
	{
		++_size;
		node* ans = new node(value, pos.it->prev, pos.it);
		if (pos.it == head)
			head = ans;
		return ans;
	}

	iterator insert(const_iterator pos, size_type count, const_reference value)
	{
		if (count == 0)
			return pos.it;
		node* ans(new node(value, pos.it->prev));
		pos.it->prev = ans;
		_size += count;
		while (--count)
			pos.it->prev = new node(value, pos.it->prev);
		pos.it->prev->next = pos.it;
		if (pos.it == head)
			head = ans;
		return ans;
	}

	template<typename InputIt>
	iterator insert(const_iterator pos, InputIt first, InputIt last)
	{
		if (first == last)
			return pos.it;
		node* ans(new node(*first, pos.it->prev));
		pos.it->prev = ans;
		++_size;
		while (++first != last) {
			pos.it->prev = new node(*first, pos.it->prev);
			++_size;
		}
		pos.it->prev->next = pos.it;
		if (pos.it == head)
			head = ans;
		return ans;
	}

	iterator insert(const_iterator pos, std::initializer_list<T> ilist)
	{
		return insert(pos, ilist.begin(), ilist.end());
	}

	iterator erase(const_iterator pos)
	{
		node* ans = pos.it->next;
		take_node(pos.it);
		delete pos.it;
		return ans;
	}

	iterator erase(const_iterator first, const_iterator last)
	{
		if (first == last)
			return last.it;
		take_range(first.it, last.it);
		while (first != last) {
			node* elem(first.it);
			++first;
			delete elem;
		}
		return last.it;
	}

	void push_back(const_reference value)
	{
		insert(cend(), value);
	}

	void pop_back()
	{
		erase(--cend());
	}

	void push_front(const_reference value)
	{

		insert(cbegin(), value);
	}

	void pop_front()
	{
		erase(cbegin());
	}

	void resize(size_type count, const_reference value = value_type())
	{
		if (count < _size) {
			node* it(tail);
			for (size_type i = 0; i < _size - count; ++i, it = it->prev);
			erase(it, tail);
		}
		else
			insert(tail, count - _size, value);
	}

	void swap(_list& other)
	{
		std::swap(_size, other._size);
		std::swap(head, other.head);
		std::swap(tail, other.tail);
	}

private:
	void reverse_recursive(node* first, node* last)
	{
		if (first == last)
			return;
		if (first->next != last && first->next)
			reverse_recursive(first->next, last->prev);
		if (first->prev)
			first->prev->next = last;
		else
			head = last;
		if (first->next == last) {
			last->next->prev = first;
			first->next = last->next;
			last->prev = first->prev;
			first->prev = last;
			last->next = first;
		}
		else {
			first->next->prev = last;
			last->prev->next = first;
			last->next->prev = first;
			std::swap(first->prev, last->prev);
			std::swap(first->next, last->next);
		}
	}

	void reverse_iterative()
	{
		if (_size == 0)
			return;
		head->prev = head->next;
		head->next = tail;
		for (node* it = head->prev; it != tail; it = it->prev)
			std::swap(it->prev, it->next);
		std::swap(head, tail);
		head = head->prev;
		head->prev = nullptr;
		tail->next->prev = tail;
		tail = tail->next;
	}

private:
	template <typename Compare>
	void merge_segments(node* first1, size_type sz1, node* first2, size_type sz2, Compare comp)
	{

		size_type count1 = 0, count2 = 0;
		while (count1 != sz1 && count2 != sz2)
			if (comp(first2->val, first1->val)) {
				first2 = first2->next;
				++count2;
				splice(first1, *this, first2->prev);
			}
			else {
				first1 = first1->next;
				++count1;
			}
	}

public:
	template <class Compare = std::less<T>>
	void merge(_list& other, Compare comp = std::less<T>())
	{
		if (this == &other)
			return;
		node* first(head), * first2(other.head), * last(tail), * last2(other.tail);
		while (first != last && first2 != last2)
			if (comp(first2->val, first->val)) {
				first2 = first2->next;
				splice(first, other, first2->prev);
			}
			else
				first = first->next;
		if (first == last && first2 != last2)
			splice(last, other, first2, last2);
	}

	void splice(const_iterator pos, _list& other)
	{
		splice(pos, other.begin(), other.end());
	}

	void splice(const_iterator pos, _list& other, const_iterator it)
	{
		other.take_node(it.it);
		put_node(pos.it, it.it);
	}

	void splice(const_iterator pos, _list& other, const_iterator first, const_iterator last)
	{
		if (first == last)
			return;
		node* last_prev = last.it->prev;
		other.take_range(first.it, last.it);
		put_range(pos.it, first.it, last_prev);
	}

	size_type remove(const_reference value)
	{
		return remove_if([value](const_reference val) { return val == value; });
	}

	template<typename UnaryPredicate>
	size_type remove_if(UnaryPredicate p)
	{
		size_type ans = 0;
		for (node* it = head; it != tail;)
			if (p(it->val)) {
				it = erase(it).it;
				++ans;
			}
			else
				it = it->next;
		_size -= ans;
		return ans;
	}

	void reverse()
	{
		/*
		if (_size == 0)
			return;
		reverse_recursive(head, tail->prev);
		*/
		reverse_iterative();
	}

private:
	template<typename Pred>
	size_type remove_duplicates(Pred p, bool for_unique)
	{
		if (_size == 0)
			return 0u;
		size_type ans = 0;
		node* it = head->next, * first;
		while (true)
		{
			first = it;
			while (it != tail && p(it->prev->val, it->val)) {
				it = it->next;
				++ans;
			}
			if (first != it)
				if (for_unique)
					erase(first, it);
				else
					erase(first->prev, it);
			if (it == tail)
				break;
			it = it->next;
		}
		return ans;
	}

public:
	template<typename BinaryPredicate = std::equal_to<T>>
	size_type unique(BinaryPredicate p = std::equal_to<T>())
	{
		return remove_duplicates(p, true);
	}

	void deleteDuplicates();

	template<typename Compare = std::less<T>>
	void sort(Compare comp = std::less<T>())
	{
		if (_size < 2)
			return;
		//merge_sort
		node* it = head;
		while (it->next && it->next->next)
		{
			if (comp(it->next->val, it->val))
				splice(it, *this, it->next);
			else
				it = it->next;
			it = it->next;
		}
		size_type seg_size = 4, i;
		iterator next_half, next_seg;
		while (seg_size >> 1 < _size)
		{
			it = head;
			for (i = 0; i < _size / seg_size; ++i)
			{
				next_half = std::next(iterator(it), seg_size >> 1);
				next_seg = std::next(next_half, seg_size >> 1);
				merge_segments(it, seg_size >> 1, next_half.it, seg_size >> 1, comp);
				it = next_seg.it;
			}
			if ((_size % seg_size) > (seg_size >> 1)) {
				next_half = std::next(iterator(it), seg_size >> 1);
				merge_segments(it, seg_size >> 1, next_half.it,
					(_size % seg_size) - (seg_size >> 1), comp);
			}
			seg_size <<= 1;
		}
	}
};

class problem1_solution
{
public:

	_list<int> addTwoNumbers(_list<int>& l1, _list<int>& l2)
	{
		short carry = 0;
		_list<int> r;
		_list<int>::iterator it1 = l1.begin(), it2 = l2.begin();
		while (it1 != l1.end() && it2 != l2.end()) {
			r.push_back((carry + *it1 + *it2) % 10);
			carry = (carry + *it1 + *it2) / 10;
			++it1; ++it2;
		}
		while (it1 != l1.end()) {
			r.push_back((carry + *it1) % 10);
			carry = (carry + *it1) / 10;
			++it1;
		}
		while (it2 != l2.end()) {
			r.push_back((carry + *it2) % 10);
			carry = (carry + *it2) / 10;
			++it2;
		}
		if (carry)
			r.push_back(carry);
		return r;
	}
};

// Problem 2
class problem2_solution
{
public:
	_list<int> mergeTwoLists(const _list<int>& l1, const _list<int>& l2) {
		_list<int> r(l1), r2(l2);

		r.merge(r2);

		return r;
	}
};

template <typename T>
void _list<T>::deleteDuplicates()
{
	remove_duplicates(std::equal_to<T>(), false);
}
