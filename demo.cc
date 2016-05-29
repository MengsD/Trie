#include "Trie.h"

#include <iostream>

using namespace std;

int main(){     
    Trie t;     
    int a[4] = {1, 2, 3, 4};
    struct Pair node1 = {4, 4, (char*)&a[3], (char*)&a[0]};  
    struct Pair node2 = {4, 4, (char*)&a[2], (char*)&a[1]};  
    struct Pair node3 = {4, 4, (char*)&a[0], (char*)&a[3]};  
    struct Pair node4 = {4, 4, (char*)&a[0], (char*)&a[2]};  
    struct Pair node5 = {4, 4, (char*)&a[0], (char*)&a[1]};  

    cout << " ======== INSERT =========" << endl;
    t.insert(&node1);
    t.insert(&node2);
    t.insert(&node3);

    t.insert(&node4);
    t.insert(&node5);

    cout << "\n ====  Search: k=1 ===== " << endl; 
    List* result = t.search((char*)&a[0], 4);
    if (result != NULL) 
        result->output();
    else 
        cout << "Not found!" << endl;

    cout << "\n ====  Search: k=2 ===== " << endl; 
    result = t.search((char*)&a[1], 4);
    if (result != NULL) 
        result->output();
    else 
        cout << "Not found!" << endl;

    cout << "\n ===== OUTPUT ===== " << endl;
    t.traverse(t.root());
}  

