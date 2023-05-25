//characters allowed: abcdefghijklmnopqrstuvwxyz0123456789_
//amount of characters allowed
#include <stdio.h>
#include <stdlib.h>
#define SIZE 37

typedef struct TrieNode {
    struct TrieNode* children[SIZE];
    float value;
    int isTerminal;
} Trie;

//declaring global variable for root
Trie* root;

//return index for hash map (order: numeric, alphabet, underline)
int getIndex(char key) {
    if(key == '_') return 36;
    if(key < 'a') return key - '0';
    else return key - 'a' + 10;
}

Trie* createNode() {
    Trie* newNode = (Trie*) malloc(sizeof(Trie));
    newNode->isTerminal = 0;
    newNode->value = 0;

    //starting all children as NULL
    for(int i = 0; i < SIZE; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

Trie* triInsertRecursion(Trie* root, char* word, float value, int index) {
    //if doesn't have any other character (end of string) will just update the value
    if(word[index+1] == '\0') {
        if(!root->isTerminal)
            root->value = value;
        else return 0;
    } else {
        int i = getIndex(word[index]);
        if(root->children[i] == NULL) {
            root->children[i] = createNode();
        }
        root->children[i] = triInsertRecursion(root, word, value, index+1);
    }
    return root;
}

int triInsert(char* word, float value) {
    if(triInsertRecursion(root, word, value, 0) != NULL) return 1;
    return 0;
}

int noChildren(Trie* node) {
    for(int i = 0; i < SIZE; i++) {
        if(node->children[i] != NULL)
            return 0;
    }
    return 1;
}

void main() {
    root = createNode('\0');
}