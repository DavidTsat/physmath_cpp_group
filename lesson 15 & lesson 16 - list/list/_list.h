#pragma once 

#include <iostream>
#include <assert.h>
#include <iterator>

using namespace std;

template <typename T>
class _list
{
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using diff_type = ptrdiff_t;


private:
    struct node
    {
        value_type val;
        node* prev_;
        node* next_;

        node(const_reference v, node* p, node* n) : val(v), prev_(p), next_(n) {}
    };

    size_type size_;
    node* head;
    node* tail;


private:
    void reverse_iterative()
    {
       // TODO
    }

    void reverse_recursive(node* p)
    {
        // TODO
    }
public:
    class iterator : public std::iterator<std::bidirectional_iterator_tag, value_type>
    {
        node* it;
    public:
        iterator(node* it_) : it(it_) { }
        value_type& operator*()
        {
            return it->val;
        }
        value_type* operator->()
        {
            return &it->val;
        }
        iterator operator++()
        {
            it = it->next_;
            return *this;
        }
        iterator operator--()
        {
            it = it->prev_;
            return *this;
        }
        diff_type operator-(iterator it2)
        {
            diff_type cnt = 0;
            while (it2.it != it) {
                ++it2;
                cnt++;
            }
            return cnt;
        }
        bool operator==(iterator it2) const noexcept
        {
            return it2.it == it;
        }
        bool operator!=(iterator it2) const noexcept
        {
            return it2.it != it;
        }
        operator node* ()
        {
            return it;
        }
    };

    _list(size_type n = 0, const_reference v = value_type{}) : size_(n), head(nullptr), tail(nullptr)
    {
        if (n == 0) return;
        head = new node(v, nullptr, nullptr);
        --n;
        node* head1 = head;
        for (size_type i = 0; i < n; ++i)
        {
            head1->next_ = new node(v, head1, nullptr);
            head1 = head1->next_;
        }
        tail = head1;
    }
    iterator begin() {
        return head;
    }
    iterator end() {
        return nullptr;
    }

    const iterator cbegin() const {
        return head;
    }
    const iterator cend() const {
        return nullptr;
    }

    _list(const _list& l) : size_(l.size_), head(nullptr), tail(nullptr)
    {
        if (!size_) return;
        head = new node(l.head->val, nullptr, nullptr);
        node* head1 = head;

        auto it1 = l.cbegin();
        for (++it1; it1 != l.cend(); ++it1) {
            head1->next_ = new node(*it1, head1, nullptr);
            head1 = head1->next_;
        }
        tail = head1;
    }

    _list(_list&& l) noexcept : size_(0), head(nullptr), tail(nullptr)
    {
        this->swap(l);
    }

    _list& operator=(const _list& l1) {
        _list l2(l1);
        this->swap(l2);
        return *this;
    }

    _list& operator=(_list&& l1) noexcept {
        this->swap(l1);
        return *this;
    }

    ~_list()
    {
        if (size_ == 0) return;

        node* nod = head->next_;
        while (nod != tail->next_)
        {
            delete nod->prev_;
            nod = nod->next_;
        }
        delete tail;
    }

    void push_back(const_reference a) {
        node* p = new node(a, nullptr, nullptr);
        ++size_;
        if (size_ == 1) {
            head = p;
            tail = p;
            /*
            head  = nullptr;
            tail  = nullptr;
            size_ = 0;
            *this = _list(1, a);
            */
        }
        else {
            tail->next_ = p;
            p->prev_ = tail;
            tail = p;
        }
    }

    void push_front(const_reference a) {

    }

    void pop_back() {
        if (!size_) return;
        --size_;
        if (size_ == 0) {
            delete tail;
            head = tail = nullptr;
        }
        else
        {
            tail = tail->prev_;
            delete tail->next_;
            tail->next_ = nullptr;
        }
    }

    void insert(_list::iterator it, const_reference v)
    {
        node* temp = new node(v, (node*)it, ((node*)it)->next_);
        if (((node*)it)->next_)
            ((node*)it)->next_->prev_ = temp;
        ((node*)it)->next_ = temp;
        ++size_;
    }

    void pop_front() {

    }

    template <typename Pred>
    void remove_if(Pred p) {
        for (node* it = head; it != nullptr;) {
            if (p(it->val)) {
                node* pp = it;
                if (it->prev_)
                    it->prev_->next_ = it->next_;
                if (it->next_)
                    it->next_->prev_ = it->prev_;

                if (head == it)
                    head = it->next_;
                if (tail == it)
                    tail = it->prev_;
                it = it->next_;
                delete pp;
                --size_;
            }
            else
                it = it->next_;
        }
    }

    void reverse()
    {
        // TODO
        // 
        //reverse_iterative();
        //reverse_recursive(head);
    }

    void swap(_list& l1) noexcept
    {
        std::swap(l1.head, head);
        std::swap(l1.tail, tail);
        std::swap(l1.size_, size_);
    }

    size_type size() const {
        return size_;
    }

    void deleteDuplicates();
};

void test1()
{
    _list<int> l(74, 7);
    cout << l.size() << endl;
    _list<int> l2;
    _list<int> l3(1);
}

void test2()
{
    _list<int> l(37, 7);

    for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << ' ';
    }

    cout << endl;

    _list<int> l2(1);

    for (_list<int>::iterator it = l2.begin(); it != l2.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

void test3()
{
    _list<int> l(37, 7);

    assert((l.end() - l.begin()) == 37);
    assert((l.end() - l.begin()) == l.size());
    assert(std::distance(l.begin(), l.end()) == 37);

    cout << (l.end() - l.begin()) << endl;

    _list<int> l2;

    assert((l2.end() - l2.begin()) == 0);
    assert((l2.end() - l2.begin()) == l2.size());
    assert(std::distance(l2.begin(), l2.end()) == 0);
}

void test4()
{
    _list<int> l(37, 7);
    _list<int> l2(14, -5);

    for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;

    l.swap(l2);

    assert(l.size() == 14);
    assert(l2.size() == 37);

    for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

void test5()
{
    _list<int> l(37, 7);
    _list<int> l2(l);

    for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;

    for (_list<int>::iterator it = l2.begin(); it != l2.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

void test6()
{
    _list<int> l(37, 7);
    _list<int> l2(move(l));

    assert(l.size() == 0);
    assert(distance(l.cbegin(), l.cend()) == 0);

    assert(l2.size() == 37);
    assert(distance(l2.cbegin(), l2.cend()) == 37);

    for (_list<int>::iterator it = l2.begin(); it != l2.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

struct A
{
    int c;
    static int k;
    static int q;

    A(int cc = 8) : c(cc) {}
    A(const A& a) : c(a.c) { ++q; }
    A(A&& a) noexcept : c(a.c) {}
    ~A() { ++k; }
};

int A::k = 0;
int A::q = 0;

void test7()
{
    _list<A> l(37, 7);
    _list<A> l2(41, 14);

    //  cout << A::k <<endl;
     // cout << A::q <<endl;

    int initial_k = A::k;
    int initial_q = A::q;
    cout << endl;

    l2 = l;

    assert(A::k == initial_k + 41);
    assert(A::q == initial_q + 37);
    //  cout << l2.size() <<endl;
    //  cout << A::k <<endl;
    //  cout << A::q <<endl;

      /*
      for (_list<A>::iterator it = l2.begin(); it != l2.end(); ++it)
      {
        cout << (*it).c << ' ';
      }
      */
      // assert(l2.size() == 37);
       //assert(A::k == 41);
}

void test8()
{
    _list<A> l(37, 7);
    _list<A> l2(41, 14);
    int initial_q = A::q;
    l2 = move(l);
    assert(A::q == initial_q);

    for (_list<A>::iterator it = l2.begin(); it != l2.end(); ++it)
    {
        cout << (*it).c << ' ';
    }
}

void test9()
{
    _list<int> l;
    for (int i = 0; i < 10; ++i)
    {
        l.push_back(i);
    }

    cout << l.size() << endl;
    cout << std::distance(l.cbegin(), l.cend()) << endl;

    for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << ' ';
    }
}

void test10()
{
    _list<int> l;
    for (int i = 0; i < 10; ++i)
    {
        l.push_back(i);
    }
    for (int i = 0; i < 10; ++i)
    {
        l.pop_back();
    }
    cout << l.size() << endl;
    for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << ' ';
    }
}

void test11()
{
    _list<int> l;
    for (int i = 0; i < 10; ++i)
    {
        l.push_back(i);
    }

    auto it = l.begin();
    for (int i = 0; i < 10; ++i)
    {
        l.insert(++it, i);
    }

    //  l.insert(--l.end(), 15);

    for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl << l.size() << endl;
    /*
    for (int i = 0; i < 10; i+=2)
    {

    }
    */
}


void test12()
{
    _list<int> l;

    for (int i = 0; i < 10; ++i)
    {
        l.push_back(i);
    }

    l.remove_if([](int val) { return !(val & 1); });
    //   l.remove_if1([](int val){ return val == 0;});

    for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << ' ';
    }
}

void test13()
{
    _list<int> l1;
    _list<int> l2;
    _list<int> l3(1);

    for (int i = 0; i < 10; ++i)
    {
        l1.push_back(i);
    }

    l1.reverse();
    l2.reverse();
    l3.reverse();

    for (_list<int>::iterator it = l1.begin(); it != l1.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
    for (_list<int>::iterator it = l2.begin(); it != l2.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
    for (_list<int>::iterator it = l3.begin(); it != l3.end(); ++it)
    {
        cout << *it << ' ';
    }
}

void test14()
{
    _list<int> l;
    for (int i = 0; i < 100; ++i)
    {
        l.push_back(i);
        assert(l.size() == i + 1);
        assert(std::distance(l.cbegin(), l.cend()) == i + 1);
    }
    l.reverse();
    int i = 99;
    for (_list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        assert(i-- == *it);
    }
}