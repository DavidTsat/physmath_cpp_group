#pragma once
#include <iostream>
#include <functional>
#include <utility>
#include <queue>
#include <initializer_list>
#include <assert.h>
#include <deque>

#define debug_mode

using namespace std;
/*
          12
      /    \
     5      18
  / \    /  \
 2   9  15  19
       /  \
      13  17
*/

/*
+ RED
* BLACK

    *5
   /  \
  +-7+ +15+
 /  \  / \
*0 *6 *12 *51
            \
           +78+

nil
*/

/*
    1
     \
      2
       \
        3
         \
          4
*/

/*
1. RED or BLACK
2. root is BLACK
3. each leaf(nil) is BLACK
4. if node is RED, then its child is BLACK
5. same amount of BLACK nodes

2log(n)

*/

template<typename K, typename T, typename Compare = std::less<K>>
class rbtree_map {
public:
    using key_type = K;
    using mapped_type = T;
    using value_type = pair<const K, T>;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using key_compare = Compare;
private:
    enum class color { RED, BLACK };
    struct node {
        value_type entry;
        color c;
        node* parent, * left, * right;

        node(const value_type& entry_, color c_ = color::RED, node* parent_ = nullptr, node* left_ = nil, node* right_ = nil) : entry(entry_), c(c_), parent(parent_),
            left(left_), right(right_) {}
    };

    node* root;
    static node* nil;
    Compare cmp;
    size_type sz;

private:
    static node* get_min(node* p)
    {
        while (p->left != nil)
            p = p->left;
        return p;
    }

    template <typename F>
    void inorder_traversal(node* p, F f)
    {
        /*
        left subtree, root, right subtree
        */
        if (p == nil)
            return;
        if (p->left)
            inorder_traversal(p->left, f);

        f(p);
        if (p->right)
            inorder_traversal(p->right, f);
    }

    template <typename F>
    void preorder_traversal(node* p, F f)
    {
        /*
        root, left subtree, right subtree
        */
        if (p == nil)
            return;

        f(p);
        if (p->left)
            preorder_traversal(p->left, f);
        if (p->right)
            preorder_traversal(p->right, f);
    }

    template <typename F>
    void postorder_traversal(node* p, F f)
    {
        /*
        root, left subtree, right subtree
        */
        if (p == nil)
            return;

        if (p->left)
            postorder_traversal(p->left, f);
        if (p->right)
            postorder_traversal(p->right, f);
        f(p);
    }

    template <typename F>
    void level_traversal(node* p_, F f)
    {
        /*
        BFS
        */
        queue<node*> q;
        q.push(p_);

        while (!q.empty()) {
            node* p = q.front();
            q.pop();
            f(p);
            if (p->left != nil)
                q.push(p->left);
            if (p->right != nil)
                q.push(p->right);
        }
    }

    void left_rotate(node* x)
    {
        node* y = x->right;
        x->right = y->left;
        if (y->left != nil)
            y->left->parent = x;
        if (x == root)
            root = y;
        else {
            if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
        }
        y->parent = x->parent;
        y->left = x;
        x->parent = y;
    }
    void right_rotate(node* y)
    {
        /*        |               left_rotate(x)           |
                  y               <--------------          x
                 / \              -------------->         / \
                x   c (subtree)   right_rotate(y)        a   y
               / \                                          / \
    (subtree) a   b (subtree)                              b   c
        */
        node* x = y->left;
        y->left = x->right;
        if (x->right != nil)
            x->right->parent = y;
        if (y == root)
            root = x;
        else
            if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
        x->parent = y->parent;
        x->right = y;
        y->parent = x;
    }

    void insert_fixup(node* z)
    {
        // + RED
        // * BLACK
        // z == 4

        /*      *11*
                /  \
               +2+ *14*
              /  \   \
             *1* *7* +15+
                 / \
               +5+ +8+ y
              /
            +4+ z
        */

        while (z->parent->c == color::RED)
        {
            // z->parent->parent->c == color::BLACK
            if (z->parent == z->parent->parent->left)
            {
                node* y = z->parent->parent->right; // дядя
                if (y->c == color::RED)
                {
                    /*      *11*
                            /  \
                           +2+ *14* y
                          /  \   \
                         *1* +7+z +15+
                             / \
                           *5* *8*
                          /
                        +4+
                    */
                    y->c = color::BLACK;
                    (z->parent)->c = color::BLACK;
                    (z->parent)->parent->c = color::RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right)
                    {
                        // left_rotate
                        // right_rotate

                /*      *11*           left_rotate(z->p)        *11*
                        /  \           -------------------->    /  \
                       +2+ *14* y                             +7+ *14* y
                      /  \   \                                /  \   \
                     *1* +7+z +15+                          +2+z *8* +15+
                         / \                                /  \
                       *5* *8*                             *1*  *5*
                      /                                         /
                    +4+                                        +4+
                */
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->c = color::BLACK;
                    z->parent->parent->c = color::RED;
                    /*       +11+                                          *7*
                             /  \        right_rotate(z->p->p)           /     \
                          *7*  *14* y                                  +2+     +11+
                          /  \    \                                   /  \     /  \
                        +2+z *8* +15+                               *1*  *5* *8* *14*
                        /  \                                        /              \
                      *1*  *5*                                    +4+             +15+
                      /
                    +4+
                    */
                    right_rotate(z->parent->parent);
                }
            }
            else
            {
                node* y = z->parent->parent->left; // дядя
                if (y->c == color::RED)
                {
                    y->c = color::BLACK;
                    (z->parent)->c = color::BLACK;
                    (z->parent)->parent->c = color::RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->c = color::BLACK;
                    z->parent->parent->c = color::RED;
                    left_rotate(z->parent->parent);
                }
            }
            if (z == root)
                break;
        }
        root->c = color::BLACK;
    }

    void transplant(node* a, node* b) {
        if (a == root)
            root = b;
        else if (a->parent->left == a)
            a->parent->left = b;
        else
            a->parent->right = b;
        if (b != nil)
            b->parent = a->parent;
    }

#ifdef debug_mode
    bool validate_btree(node* p)
    {
        if (p == nil)
            return true;

        key_type max_k = numeric_limits<key_type>::min();
        key_type min_k = numeric_limits<key_type>::max();

        preorder_traversal(p->left, [this, &max_k, &min_k](node* x) { if (cmp(x->entry.first, min_k)) min_k = x->entry.first; if (!cmp(x->entry.first, max_k)) max_k = x->entry.first; });

        if (!cmp(max_k, p->entry.first))
        {
            return false;
        }

        max_k = numeric_limits<key_type>::min();
        min_k = numeric_limits<key_type>::max();

        preorder_traversal(p->right, [this, &max_k, &min_k](node* x) { if (cmp(x->entry.first, min_k)) min_k = x->entry.first; if (!cmp(x->entry.first, max_k)) max_k = x->entry.first; });

        if (cmp(min_k, p->entry.first))
        {
            return false;
        }

        return validate_btree(p->right) && validate_btree(p->right);
    }

    vector<pair<node*, bool>> bad_bst_examples()
    {
        /*
        *		    2		true
        *		   / \
        *		  1	  3
        */

        /*		    5		false
        *		   / \
        *		  1   4
        *			 / \
        *			3   6
        */

        /*			5		false
        *		   / \
        *		  4   6
        *			 / \
        *           3   7
        */

        // no need to use parent nodes
        node* ex1 = new node({ 2, 2 }, color::BLACK, nullptr, new node({ 1, 1 }, color::BLACK), new node({ 3, 3 }, color::BLACK));
        node* ex2 = new node({ 5, 5 }, color::BLACK, nullptr, new node({ 1, 1 }, color::BLACK), new node({ 4, 4 }, color::BLACK, nullptr, new node({ 3, 3 }, color::BLACK), new node({ 6, 6 }, color::BLACK)));
        node* ex3 = new node({ 5, 5 }, color::BLACK, nullptr, new node({ 4, 4 }, color::BLACK, nullptr, new node({ 6, 6 }, color::BLACK, nullptr, new node({ 3, 3 }, color::BLACK, nullptr, new node({ 7,7 }, color::BLACK)))));

        vector<pair<node*, bool>> r = { {ex1, true}, {ex2, false}, {ex3, false} };
        return r;
    }
#endif 
public:
    rbtree_map(Compare cmp_ = Compare()) : root(nullptr), cmp(cmp_), sz(0) {}

    rbtree_map(const rbtree_map& other) : root(nullptr), cmp(other.cmp), sz(0) {
        if (other.sz == 0)
            return;
        // 
        // BS Tree -> red black BS Tree -> std::map

        // TODO to make this O(n)

        level_traversal(other.root, [this](node* p) {this->operator[](p->entry.first) = p->entry.second; });
        //   inorder_traversal(other.root, [this](node* p){this->operator[](p->entry.first) = p->entry.second;});
    }

    template <typename Comp>
    rbtree_map(std::initializer_list<value_type> init, const Comp& comp = Compare()) : cmp(comp), sz(0)
    {
        for (const value_type& v : init)
        {
            this->operator[](v.first) = v.second;
        }
    }


    rbtree_map(rbtree_map&& other) noexcept
    {
        // TODO
    }

    rbtree_map& operator=(const rbtree_map& other)
    {
        // TODO
    }

    rbtree_map& operator=(rbtree_map&& other) noexcept
    {
        // TODO
    }

    ~rbtree_map() noexcept
    {
        if (root)
            postorder_traversal(root, [](node* p) { delete p; });
    }

    reference operator[](const key_type& key)
    {
        if (!root) {
            ++sz;
            root = new node(make_pair(key, mapped_type()), color::BLACK, nullptr, nil, nil);
            return root->entry.second;
        }
        node* p = root;
        node* prev = nullptr;
        while (p != nil)
        {
            prev = p;
            //if (!cmp(key, p->entry.first)  && !cmp(p->entry.first, key))
            if (cmp(key, p->entry.first))
                p = p->left;
            else if (cmp(p->entry.first, key))
                p = p->right;
            else
                return p->entry.second;
        }
        // insert
        ++sz;
        p = new node(make_pair(key, mapped_type()), color::RED, prev, nil, nil);
        if (cmp(prev->entry.first, key))
            prev->right = p;
        else
            prev->left = p;

        insert_fixup(p);
        return p->entry.second;
    }

    class iterator : public  std::iterator<std::bidirectional_iterator_tag, value_type> {
        node* it;

        node* successor(node* p)
        {
            if (it->right != nil)
                return get_min(it->right);
            node* parent_it = it->parent;
            while (parent_it && parent_it->right == it) {
                parent_it = parent_it->parent;
                it = it->parent;
            }
            return parent_it;
        }
        node* predecessor(node* p)
        {
            //TODO
            return p;
        }
    public:
        iterator(node* it_) : it(it_) {}

        value_type& operator*() {
            return it->entry;
        }

        value_type* operator->() {
            return &it->entry;
        }

        iterator& operator++() { //++it
            it = successor(it);
            return *this;
        }

        iterator operator++(int) { //it++
          // QUESTION
            iterator old_it = it;
            it = successor(it);
            return old_it;
        }

        iterator& operator--() { //++it
            it = predecessor(it); //TODO
            return *this;
        }
        bool operator==(iterator other) const {
            return it == other.it;
        }

        bool operator!=(iterator other) const {
            return it != other.it;
        }

        operator node* ()
        {
            return it;
        }
    };

    iterator begin()
    {
        return get_min(root);
    }

    iterator end()
    {
        return nullptr;
    }

    iterator find_recursive(node* p, const key_type& k)
    {
        if (p == nullptr || (!cmp(p->entry.first, k) && !cmp(k, p->entry.first)))
        {
            return p;
        }

        if (cmp(k, p->entry.first))
            return find_recursive(p->left, k);
        else
            return find_recursive(p->right, k);
    }

    iterator find(const key_type& k)
    {
        return find_recursive(root, k);
    }

    void erase(iterator it)
    {
        node* z = (node*)it;
        if (z == nullptr || z == nil)
            return;
        // transplant
        if (z->left == nil)
            transplant(z, z->right);
        else if (z->right == nil)
            transplant(z, z->left);
        else
        {
            node* y = get_min(z->right);
            if (y == z->right)
            {
                /*    q
                      |
                      z
                    /   \
                   l     r == y
                  / \     \
                           x
            */
                transplant(z, y);
                y->left = z->left;
                z->left->parent = y;
            }
            else
            {
                /*
                      q
                      |
                      z
                    /   \
                   l     r
                  / \   / \
                      ...
                       y
                      / \
                     NIL x
                        / \
                */
                transplant(y, y->right);
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->right = z->right;
                y->right->parent = y;
            }
        }
        --sz;
        delete z;
    }

    size_type size() const
    {
        return sz;
    }

    iterator kth_element(size_type k)
    {
        size_type i = 1;
        iterator it(nullptr);
        kth_element(root, k, i, it);
        return it;
    }

#ifdef debug_mode

    void kth_element(node* r, size_type k, size_type& i, iterator& it)
    {
        if (r == nil)
        {
            return;
        }

        kth_element(r->left, k, i, it);
        if (k == i)
            it = r;

        ++i;
        kth_element(r->right, k, i, it);
    }

    void print_inorder()
    {
        inorder_traversal(root, [](node* it) {cout << it->entry.first << ' ' << it->entry.second << '\n'; });
        cout << endl;
    }

    void print_preorder()
    {
        preorder_traversal(root, [](node* it) {cout << it->entry.first << ' ' << it->entry.second << '\n'; });
        cout << endl;
    }
    void print_levelorder()
    {
        level_traversal(root, [](node* it) {cout << it->entry.first << ' ' << it->entry.second << '\n'; });
        cout << endl;
    }

    bool is_valid_bst()
    {
        return validate_btree(root);
    }

    void check_is_valid_bst()
    {
        vector<pair<node*, bool>> v = bad_bst_examples();

        for (pair<node*, bool> p : v)
        {
            bool b = validate_btree(p.first);
            assert(b == p.second);
        }
    }

    pair<vector<node*>, vector<vector<vector<value_type>>>> zigzag_traversal_examples() const
    {
        /*
        
        1.    
            3                     {{3}, {20,9}, {15,4}}
           / \
          9   20
             /  \
            15   4

        2.
            1                     {{{1}}}

        3.
            1                     {{1}, {3,2}, {4,5}}
           / \ 
          2   3
         /     \
        4       5

        */
        node* r1 = new node({ 3, 5 }, color::BLACK, nullptr, new node({ 9, 14 }, color::BLACK), new node({ 20, 7 }, color::BLACK, nullptr, new node({ 15, 4 }, color::BLACK), new node({ 7,5 }, color::BLACK)));
        vector<vector<value_type>> v1 = {{ {3,5} }, { {20,7}, {9,14} }, { {15,4}, {7,5} }};

        node* r2 = new node({ 1, 4 }, color::BLACK);
        vector<vector<value_type>> v2 = { {{1, 4}} };

        node* r3 = new node({ 1, 1 }, color::BLACK, nullptr, new node({ 2, 4 }, color::BLACK, nullptr, new node({ 4, 4 }, color::BLACK), nil), new node({ 3, 3 }, color::BLACK, nullptr, nil, new node({ 5,14 }, color::BLACK)));
        vector<vector<value_type>> v3 = { {{1,1}}, {{3,3}, {2,4}}, {{4,4}, {5,14}} };

     //   pair<vector<node*>, vector<vector<vector<value_type>>>> p { {r1, r2, r3}, { v1, v2, v3 }};
 
        return { {r1, r2, r3}, { v1, v2, v3 } };
    }

    void bfs(queue<pair<node*, int>>& q, vector<deque<value_type>>& r) 
    {
        if (q.empty())
        {
            return;
        }

        pair<node*, int> t = q.front();
        q.pop();

        if (r.size() < t.second)
        {
            r.push_back({ t.first->entry });
        }
        else
        {
            if (t.second % 2 == 0)
            {
             //   const value_type vv;
              //  r[t.second - 1].insert(r[t.second - 1].begin(), 5);
             //   r[t.second - 1].insert(r[t.second - 1].begin(), t.first->entry);
                r[t.second - 1].push_front(t.first->entry);
            }
            else
            {
                r[t.second - 1].push_back(t.first->entry);
            }
        }

        if (t.first->left != nil)
        {
            q.push({ t.first->left, t.second + 1 });
        }
        if (t.first->right != nil)
        {
            q.push({ t.first->right, t.second + 1 });
        }


        return bfs(q, r);
    }

    vector<vector<value_type>> zigzag_traversal(node* p)
    {
        vector<deque<value_type>> r1;

        queue<pair<node*, int>> q;

        q.push({ p,1 });

        bfs(q, r1);

        vector<vector<value_type>> r;

        for (auto& vv : r1)
        {
            vector<value_type> vt;
            for (auto& a : vv)
                vt.push_back(a);
            r.push_back(vt);
        }
        return r;
    }

    void check_zigzag_traversal()
    {
        pair<vector<node*>, vector<vector<vector<value_type>>>> v = zigzag_traversal_examples();

        for (int i = 0; i < v.second.size(); ++i)
        {
            vector<vector<value_type>> out = zigzag_traversal(v.first[i]);
            assert(out == v.second[i]);
        }
    }
#endif

};

template<typename K, typename T, typename C>
typename rbtree_map<K, T, C>::node* rbtree_map<K, T, C>::nil = new node(value_type(), color::BLACK, nullptr, nullptr, nullptr);

class unique_BSTs {
    vector<int> v;
    int num_trees(int n)
    {
        if (n == 0 || n == 1)
        {
            return 1;
        }

        if (v[n - 1] != -1)
        {
            return v[n - 1];
        }

        int s = 0;
        for (int i = 1; i <= n; ++i)
        {
            s += num_trees(i - 1) * num_trees(n - i);
        }
        v[n - 1] = s;

        return s;
    }

public:
    int num_of_unique_bsts(int n) {

        v = vector<int>(n, -1);
        int k = num_trees(n);

        return k;
    }
};