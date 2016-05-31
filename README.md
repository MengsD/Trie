# Trie

An implementation for Trie, which is used in sorting lists of K-V pairs. Each byte of key is sorted respectively while inserting into the Trie.
It can handle keys with various types, including string, double, int.
In the Trie, the root node doesn't hold data. 
Each node in the trie has the following attibutions:
   - branch : length is 256.         
   - key    : key stored in the node (could be NULL)
   - value  : value stored in the node ( could be NULL)
 
We don't discard values that map to the same key. All of those values are 
stored in a list, where a head pointer points to the first value, and a tail
pointer points to the last value.
