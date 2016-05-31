#include "Trie.h"
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main()
{     
    Trie t;     

    ifstream in("./input");
    int key, value;
    while (in >> key >> value) {
        Pair* node = new Pair((char*)&key, sizeof(int), (char*)&value, sizeof(int));
        t.insert(node);
    }
    in.close();
    t.traverse(t.root());
    return 0;
}  

