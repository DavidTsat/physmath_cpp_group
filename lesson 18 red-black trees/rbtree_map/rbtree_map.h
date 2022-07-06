#pragma once
#include <iostream>
#include <functional>
#include <utility>
#include <queue>

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

        node(const value_type& entry_, color c_ = color::RED, node* parent_ = nullptr, node* left_ = nullptr, node* right_ = nullptr) : entry(entry_), c(c_), parent(parent_),
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
public:
    rbtree_map(Compare cmp_ = Compare()) : root(nullptr), cmp(cmp_), sz(0) {}

    rbtree_map(const rbtree_map& other) : root(nullptr), cmp(other.cmp), sz(other.sz) {
        if (sz == 0)
            return;
        // 
        // BS Tree -> red black BS Tree -> std::map

        // TODO to make this O(n)

        level_traversal(other.root, [this](node* p) {this->operator[](p->entry.first) = p->entry.second; });
        //   inorder_traversal(other.root, [this](node* p){this->operator[](p->entry.first) = p->entry.second;});
    }

    rbtree_map(rbtree_map&& other) noexcept {}

    rbtree_map& operator=(const rbtree_map& other) {}

    rbtree_map& operator=(rbtree_map&& other) noexcept {}

    ~rbtree_map() noexcept
    {
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

    class iterator : public  std::iterator<std::bidirectional_iterator_tag, value_type>{
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
            return it != other.it;
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

    void erase(iterator it)
    {
        node* z = (node*)it;
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

#ifdef debug_mode
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

#endif 
};

template<typename K, typename T, typename C>
typename rbtree_map<K, T, C>::node* rbtree_map<K, T, C>::nil = new node(value_type(), color::BLACK, nullptr, nullptr, nullptr);