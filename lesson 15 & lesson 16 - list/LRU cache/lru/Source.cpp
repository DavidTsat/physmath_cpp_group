#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity)  
    {

    }

    int get(int key) 
    {
     
    }

    void put(int key, int value) 
    {
      
    }
};

void test1()
{
    vector<int> answer = { -1, 1, -1, -1, 3, 4 };

    vector<int> outputs;

    LRUCache* obj = new LRUCache(2);
    
    outputs.push_back(obj->get(2));
    obj->put(1, 1);
    obj->put(2, 2);
    
    outputs.push_back(obj->get(1));
    obj->put(3, 3);
    
    outputs.push_back(obj->get(2));

    obj->put(4, 4);
    outputs.push_back(obj->get(1));
    outputs.push_back(obj->get(3));
    outputs.push_back(obj->get(4));

    delete obj;

    assert(answer == outputs);
    cout << "test1 passed\n";
    /*
    for (int i : outputs)
    {
        cout << i << ' ';
    }
    cout << endl;
    */
}

void test2()
{
    vector<int> answer = { 0, -1, -1, 3, 4 };

    vector<int> outputs;

    LRUCache* obj = new LRUCache(2);
    obj->put(1, 0);
    obj->put(2, 2);
    outputs.push_back(obj->get(1));
    obj->put(3, 3);
    outputs.push_back(obj->get(2));
    obj->put(4, 4);
    outputs.push_back(obj->get(1));
    outputs.push_back(obj->get(3));
    outputs.push_back(obj->get(4));

    delete obj;

    assert(answer == outputs);
    cout << "test2 passed\n";
    /*
    for (int i : outputs)
    {
        cout << i << ' ';
    }
    cout << endl;
    */
}

void test3()
{
    vector<int> answer = { -1 };

    vector<int> outputs;

    LRUCache* obj = new LRUCache(1);
    outputs.push_back(obj->get(0));

    delete obj;

    assert(answer == outputs);
    cout << "test3 passed\n";
    /*
    for (int i : outputs)
    {
        cout << i << ' ';
    }
    cout << endl;
    */
}

void test4()
{
    vector<int> answer = { -1, -1, 2, 6 };
    
    vector<int> outputs;

    LRUCache* obj = new LRUCache(2);

    outputs.push_back(obj->get(2));
    obj->put(2, 6);
    outputs.push_back(obj->get(1));
    obj->put(1, 5);
    obj->put(1, 2);
    outputs.push_back(obj->get(1));
    outputs.push_back(obj->get(2));

    assert(answer == outputs);
    cout << "test4 passed\n";
    /*
    for (int i : outputs)
    {
        cout << i << ' ';
    }
    cout << endl;
    */
}

void test5()
{
    vector<int> answer = { -1, 3 };

    vector<int> outputs;

    LRUCache* obj = new LRUCache(2);
    obj->put(2, 1);
    obj->put(1, 1);
    obj->put(2, 3);
    obj->put(4, 1);
    outputs.push_back(obj->get(1));
    outputs.push_back(obj->get(2));
    assert(answer == outputs);
    cout << "test5 passed\n";
    /*
    for (int i : outputs)
    {
        cout << i << ' ';
    }
    cout << endl;
    */
}

void test6()
{
    vector<int> answer = { -1, 19, 17, -1, -1, -1, 5, -1, 12, 3, 5, 5 };
    vector<int> outputs;

    LRUCache* obj = new LRUCache(10);
    obj->put(10, 13);
    obj->put(3, 17);
    obj->put(6, 11);
    obj->put(10, 5);
    obj->put(9, 10);
    outputs.push_back(obj->get(13));
    obj->put(2, 19);
    outputs.push_back(obj->get(2));
    outputs.push_back(obj->get(3));
    obj->put(5, 25);
    outputs.push_back(obj->get(8));
    obj->put(9, 22);
    obj->put(5, 5);
    obj->put(1, 30);
    outputs.push_back(obj->get(11));
    obj->put(9, 12);
    outputs.push_back(obj->get(7));
    outputs.push_back(obj->get(5));
    outputs.push_back(obj->get(8));
    outputs.push_back(obj->get(9));
    obj->put(4, 30);
    obj->put(9, 3);
    outputs.push_back(obj->get(9));
    outputs.push_back(obj->get(10));
    outputs.push_back(obj->get(10));

    assert(answer == outputs);
    cout << "test6 passed\n";
    /*
    for (int i : outputs)
    {
        cout << i << ' ';
    }
    cout << endl;
    */
}

int main()
{ 
    
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    return 0;
}