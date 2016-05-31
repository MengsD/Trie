#include "Trie.h"  
#include <cstring>

#include <cstdio>
#include <iostream>
using std::cout;
using std::endl;

Pair::Pair(char* _key, const int _klen, char* _value, const int _vlen) 
    : klen(_klen), vlen(_vlen)
{
    key = new char[klen];
    memcpy(key, _key, klen);
    value = new char[vlen];
    memcpy(value, _value, vlen);
}

Pair::~Pair()
{
    delete key;
    delete value;
}


List::Node::Node(const Pair* data) : p_pair(data), next(NULL) { }
        
List::Node::~Node () {

    if (p_pair != NULL) {
        delete p_pair;
        p_pair = NULL;
    }
}

List::List() : p_head(NULL), p_tail(NULL), num_value(0) { }
    
List::~List() { 
    destroy(); 
}

void List::destroy() {
    Node* p_current = p_head;
    while (p_current != NULL) {
        Node* p_node = p_current;
        p_current    = p_current->next;
        if (p_node != NULL) {
            delete p_node;
            p_node = NULL;
        }
    }
}
        
int List::count() const {
    return num_value;
}

void List::output() {
    Node* p_current = p_head;
    while (p_current != NULL) {
        cout << *(int*)p_current->p_pair->key << " " << *(int*)p_current->p_pair->value << endl;
        p_current = p_current->next;
    }
}

void List::insert(const Pair* const data)  
{
    Node* s = new Node(data);
	if (p_head == NULL) { 
		p_head = s;
        p_tail = s;
    }
    else  {
        p_tail->next = s;
        p_tail = p_tail->next;
        p_tail->next = NULL;
    }
    ++num_value;
}

Trie::TrieNode::TrieNode() : data(NULL) {  
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
    // Iterate the key from high byte to the low byte
    // for non-string type
    int  key_idx = 0;   
    TrieNode* p_loc = p_root;     // start from root 
    key = key+len-1;
    while( p_loc !=NULL && key_idx < len) {       
        int idx = *key >= 0 ? *key : *key+256;
        p_loc = p_loc->branch[idx];       
        --key;    
        ++key_idx;
    }    
    if ( p_loc != NULL && p_loc->data != NULL ) 
        return p_loc->data;       
    return NULL;
}  

void Trie::insert(const Pair* pair) {     
    // Iterate the key from high byte to the low byte
    // for non-string type
    const char* key = pair->key;
    const int klen = pair->klen;
    int key_idx = 0;
    key = key + pair->klen-1;

    // 1. initiate root for the first time to insert
    if ( p_root == NULL ) 
        p_root = new TrieNode;   

    // 2. find a branch to insert 
    TrieNode* p_loc = p_root;    
    while( p_loc != NULL && key_idx < klen) {         
        // create a branch if it doesn't exist 
        int idx = *key >= 0 ? *key : *key+256;
        if( p_loc->branch[idx] == NULL ) {
            p_loc->branch[idx] = new TrieNode;     
        }
  
        // jump to the branch   
        p_loc = p_loc->branch[idx];         
        //++key;       // next byte 
        --key;
        ++key_idx;
    }     

    // 3. insert value if it doesn't exist
    if (p_loc->data == NULL) 
        p_loc->data = new List();
    p_loc->data->insert(pair);
}  

void Trie::traverse(TrieNode* p_node)
{
    if (p_node != p_root && p_node->data != NULL) {
        p_node->data->output();
    }
    for (int i = 0; i < num_byte; ++i) {
        if (p_node->branch[i] == NULL)
            continue;
//        cout << "branch " << i << endl;
        traverse(p_node->branch[i]);
    } 
}

void Trie::destroy(TrieNode* p_node)
{
    if (p_node != p_root && p_node->data != NULL) {
        delete p_node->data;
        p_node->data = NULL;
    }
    for (int i = 0; i < num_byte; ++i) {
        if (p_node->branch[i] == NULL)
            continue;
        destroy(p_node->branch[i]);
    } 
}

/*
void Trie::preOrder(TrieNode* p_node)
{
    cout << endl << "==== PreOrder ===== " << endl;
    stack<TrieNode*> stack;
    int j = 0;
    
    if (p_node == NULL)     // empty tree
        return; 

//    for (int i = 0; i < num_byte;) {
//        for (int j = i+1; j < num_byte; ++j) {
    int i = 0, j = 0;
    
    while ( !stack.empty() || j < num_byte) {

    while (p_node != NULL) {
        stack.push(p_node);
        if (p_node->data != NULL) 
            p_node->data->output();
        p_node = p_node->branch[i];
        printf("p_node = %p\n", p_node);
    }

    if (!stack.empty()) {
        cout << "stack isn't null" << endl;
        p_node = stack.top();
        stack.pop();
        // iterate right
        p_node = p_node->branch[i+1];
            if (p_node == NULL)
                continue;
//            if (p_node->branch[i] == NULL) 
                continue;
        }
        printf("p_node = %p\n", p_node);
//        for (int j = 0; j < num_byte; ++j) {

            cout << "j = " << j << endl; 
            p_node = p_node->branch[i];
//        }
    }
    else 
        ++i;
    }
}
*/
/** NOTICE: Wrong. */
/*
void Trie::preOrder(TrieNode* pNode)  
{  
      stack<TrieNode*> stack;  
      stack.push(pNode);  
      TrieNode *lpNode;  
      
      while(!stack.empty())  
      {  
          lpNode = stack.top();  
          stack.pop();  
      
          if (lpNode->data != NULL)
             lpNode->data->output();
            
          for (int i=0 ;i<num_byte; i++)  
          {  
              if (pNode->branch[i] != NULL) 
                stack.push(pNode->branch[i]);  
          }  
      }  
    }  
*/
