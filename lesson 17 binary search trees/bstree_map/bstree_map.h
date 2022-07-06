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
     5
   /  \
  -7   15
 /  \  / \
0   6 12 51
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

// std::map 

template<typename K, typename T, typename Compare = std::less<K>>
class bstree_map {
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
    struct node {
        value_type entry;
        node* parent, * left, * right;

        node(const value_type& entry_, node* parent_ = nullptr, node* left_ = nullptr, node* right_ = nullptr) : entry(entry_), parent(parent_),
            left(left_), right(right_) {}
    };

    node* root;
    Compare cmp;
    size_type sz;

private:
    static node* get_min(node* p)
    {
        while (p->left)
            p = p->left;
        return p;
    }

    template <typename F>
    void inorder_traversal(node* p, F f)
    {
        /*
        left subtree, root, right subtree
        */
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
            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
        }
    }
public:
    bstree_map(Compare cmp_ = Compare()) : root(nullptr), cmp(cmp_), sz(0) {}

    bstree_map(const bstree_map& other) : root(nullptr), cmp(other.cmp), sz(other.sz) {
        if (sz == 0)
            return;
        // 
        // BS Tree -> red black BS Tree -> std::map

        // TODO to make this O(n)

        level_traversal(other.root, [this](node* p) {this->operator[](p->entry.first) = p->entry.second; });
        //   inorder_traversal(other.root, [this](node* p){this->operator[](p->entry.first) = p->entry.second;});
    }

    bstree_map(bstree_map&& other) noexcept {}

    bstree_map& operator=(const bstree_map& other) {}

    bstree_map& operator=(bstree_map&& other) noexcept {}

    ~bstree_map() noexcept
    {
        postorder_traversal(root, [](node* p) { delete p; });
    }

    reference operator[](const key_type& key)
    {
        if (!root) {
            ++sz;
            root = new node(make_pair(key, mapped_type()));
            return root->entry.second;
        }
        node* p = root;
        node* prev = nullptr;
        while (p)
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
        ++sz;
        p = new node(make_pair(key, mapped_type()), prev);
        if (cmp(prev->entry.first, key))
            prev->right = p;
        else
            prev->left = p;
        return p->entry.second;
    }

    class iterator {
        node* it;

        node* successor(node* p)
        {
            if (it->right)
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

        bool operator==(iterator other) const {
            return it != other.it;
        }

        bool operator!=(iterator other) const {
            return it != other.it;
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


