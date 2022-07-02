#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
    using key_iter = unordered_map<int, list<pair<int, int>>::iterator>::iterator;

    int cap, curr_size = 0;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> keys;
public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key)
    {
        key_iter k = keys.find(key);
        if (k == keys.end())
            return -1;
        cache.push_back(*k->second);
        cache.erase(k->second);
        keys[key] = --cache.end();
        return cache.back().second;
    }

    void put(int key, int value)
    {
        key_iter k = keys.find(key);
        if (k != keys.end())
            cache.erase(k->second);
        else if (curr_size < cap)
            ++curr_size;
        else {
            keys.erase(cache.front().first);
            cache.pop_front();
        }
        cache.push_back(make_pair(key, value));
        keys[key] = --cache.end();
    }
};
