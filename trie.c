//characters allowed: abcdefghijklmnopqrstuvwxyz0123456789_
//amount of characters allowed
#include <stdio.h>;
#include <stdlib.h>;
#define SIZE 37

typedef struct TrieNode {
    struct TrieNode* children[SIZE];
    float value;
    char* key;
    int isLeaf;
} Trie;

Trie* triInsert(Trie* root, char* key, float value, int index) {
    for(int i = 0; i < SIZE; i++) {
        if(root->children[i] == key[index]) {

        } else if(root->children[i] == NULL) {

        }
    }
    return root;
}

Trie* createNode(char* key, float value) {
    Trie* newNode = (Trie*) malloc(sizeof(Trie));
    newNode->isLeaf = 1;
    newNode->key = key;
    newNode->value = value;

    //starting all children as NULL
    for(int i = 0; i < SIZE; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

void main() {
    printf("%d", 1==0);
}