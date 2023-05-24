//characters allowed: abcdefghijklmnopqrstuvwxyz0123456789_
//amount of characters allowed
#define SIZE 37

typedef struct TrieNode {
    struct TrieNode* children[SIZE];
    float value;
    char* key;
    int isLeaf;
} Trie;