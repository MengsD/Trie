#include "Trie.h"  
#include <cstring>

#include <iostream>
using std::cout;
using std::endl;

List::Node::Node(const void* data, const int len) {
    p_value = new char[len];
    memcpy(p_value, data, len); 
    next = NULL;
}
        
List::Node::~Node () {
    if (p_value != NULL) {
        delete (char*)p_value;
        p_value = NULL;
    }
}

List::List() : p_head(NULL), p_tail(NULL) { }
    
List::~List() { 
    destroy(); 
}
/*
bool List::hasNext()
{
//    if (p_
}
void* List::next()
{
//    return 
}*/

void List::destroy() {
    Node* p_current = p_head;
    while (p_current != NULL) {
        Node* p_node = p_current;
        p_current    = p_current->next;
        delete p_node;
        p_node = NULL;
    }
}

void List::output() {
    Node* p_current = p_head;
    while (p_current != NULL) {
        cout << "value = " << *(int*)p_current->p_value << endl;
        p_current = p_current->next;
    }
}

void List::insert(const void* data, const int len) 
{
    Node* s = new Node(data, len);
	if (p_head == NULL) { 
		p_head = s;
        p_tail = s;
    }
    else  {
        p_tail->next = s;
        p_tail = p_tail->next;
        p_tail->next = NULL;
    }
}

Trie::TrieNode::TrieNode() : count(0), key(NULL), data(NULL) {  
    for (int i = 0; i < num_byte; ++i)   
        branch[i] = NULL;
}  

Trie::Trie():p_root(NULL) { }  

Trie::~Trie(){
    if (p_root != NULL) {
        destroy(p_root);
        delete p_root;
        p_root = NULL;
    }
}  

List* Trie::search(const char* key, const int len) const 
{    
    int  key_idx = 0;   
    TrieNode* p_loc = p_root;     // start from root 
    // iterate each byte for the key
    while( p_loc !=NULL && key_idx < len) {       
        p_loc = p_loc->branch[*key];       
        key++;    
        ++key_idx;
    }    
    if ( p_loc != NULL && p_loc->data != NULL ) 
        return p_loc->data;       
    return NULL;
}  

void Trie::insert(const Pair* pair) {     
//    cout << "insert key" << key << endl;
    const char* key = pair->key;
    const int klen = pair->klen;
    int key_idx = 0;

    // 1. initiate root for the first time to insert
    if ( p_root == NULL ) 
        p_root = new TrieNode;   

    // 2. find a branch to insert 
    TrieNode* p_loc = p_root;    
    while( p_loc != NULL && key_idx < klen) {         
        // create a branch if it doesn't exist 
        if( p_loc->branch[*key] == NULL )              
            p_loc->branch[*key] = new TrieNode;     
  
        // jump to the branch   
        p_loc = p_loc->branch[*key];         
        ++key;       // next byte 
        ++key_idx;
    }     

    // 3. insert value if it doesn't exist
    if (p_loc->data == NULL) 
        p_loc->data = new List();
    p_loc->data->insert(pair->value, pair->vlen);
    p_loc->key = (void*)(key-key_idx);
    ++p_loc->count;
}  

void Trie::traverse(TrieNode* p_node)
{
    if (p_node != p_root && p_node->data != NULL) {
        cout << "key = " << *(int*)p_node->key <<  " count = " << p_node->count << endl; 
        p_node->data->output();
    }
    for (int i = 0; i < num_byte; ++i) {
        if (p_node->branch[i] == NULL)
            continue;
        traverse(p_node->branch[i]);
    } 
}

void Trie::destroy(TrieNode* p_node)
{
    if (p_node != p_root && p_node->data != NULL) {
        delete p_node->data;
    }
    for (int i = 0; i < num_byte ++i) {
        if (p_node->branch[i] == NULL)
            continue;
        destroy(p_node->branch[i]);
    } 
}
