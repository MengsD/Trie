/**
 * @file Trie.h
 * @author Mengsu Ding<dingmengsu@ict.ac.cn> and Shimin Chen<chensm@ict.ac.cn>
 * @version 0.0
 *
 * @section LICENSE
 * Copyright (c) 2016 Mengsu Ding, Shimin Chen. All Rights Reserved.
 * 
 * @section DESCRIPTION
 * 
 * An implementation for Trie, which is used in sorting lists of K-V pairs.
 * Each byte of key is sorted respectively while inserting into the Trie.
 * It can handle keys with various types, including string, double, int.
 * In the Trie, the root node doesn't hold data. 
 * Each node in the trie has the following attibutions:
 *  - branch : length is 256.         
 *  - key    : key stored in the node (could be NULL)
 *  - value  : value stored in the node ( could be NULL)
 *
 * We don't discard values that map to the same key. All of those values are 
 * stored in a list, where a head pointer points to the first value, and a tail
 * pointer points to the last value.
 *
 */ 

#ifndef _TRIE_H_
#define _TRIE_H_

const int num_byte = 256; // length of branch 

class Pair {
public:
    int   klen;           // length of key
    int   vlen;           // length of vlen;
    char* key;            // key
    char* value;          // value

    explicit Pair(char* _key, const int _klen, char* _value, const int _vlen);
    virtual ~Pair();
};

class List {
protected:
    struct Node {
        const Pair* p_pair;    // pointer to K-V pair
        Node* next;      // pointer to the next node

        /**
         * Constructor. 
         * @param data point to a K-V pair
         */
        Node(const Pair* data);
   
        /** Destructor. */
        virtual ~Node ();
    };

private:
    Node* p_head;    // point to the first element
    Node* p_tail;    // point to the last element
    int   num_value; // #value in the list

public:
    /** Constructor. */
    List();

    /** Destructor. */
    virtual ~List();
    
    /** 
     * Insert data into the tail of list. 
     * @param data point to K-V pair to insert
     */
    void insert(const Pair* const data) ;

    /** Destroy the list, which is called to destroy the list. */
    void destroy();

    /** Return number of values in the list. */
    int count() const;

    /** Output the list . */
    void output();

//    Node* head() { return p_head; }

    /** List iterator. */
//    bool hasNext();
    
    /** Return pointer to the next value. */
//    void* next();
};    

class Trie {  
public:  
    struct TrieNode{  
        List*       data;              // record list of values which maps to the same key
        TrieNode*   branch[num_byte];  // pointer to branches for the node 
        /** Constructor. */
        TrieNode();   
    };  

    TrieNode* p_root;                  // point to root node

public:  
    /** Constructor. */
    Trie();  

    /** Destructor. */
    virtual ~Trie();  

    /** Return the root node. */ 
    TrieNode* root() { return p_root; }

    /** 
     * Search for values. 
     * @param key point to key to search
     * @param len length of key
     * @return pointer to list of values, return NULL if key isn't found.
     */
    List* search(const char* key, const int len) const; 

    /**
     * Insert a K-V pair into the Trie. 
     * @param pair point to a K-V pair to insert
     */
    void insert(const Pair* pair);  

    /** Traverse the Trie in preorder. */ 
    void traverse(TrieNode* p_node);

    /** Destroy the trie, which is called to destroy the list. */
    void destroy(TrieNode* p_node);

//    void preOrder(TrieNode* p_node);
};

#endif 
