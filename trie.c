//characters allowed: abcdefghijklmnopqrstuvwxyz0123456789_
//amount of characters allowed
#include <stdio.h>
#include <stdlib.h>
#define SIZE 37

typedef struct TrieNode {
    struct TrieNode* children[SIZE];
    float value;
    char key;
    int isLeaf;
} Trie;

Trie* createNode(char key) {
    Trie* newNode = (Trie*) malloc(sizeof(Trie));
    newNode->isLeaf = 1;
    newNode->key = key;
    newNode->value = -1;

    //starting all children as NULL
    for(int i = 0; i < SIZE; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

Trie* triInsertRecursion(Trie* root, char* word, float value, int index) {
    //if doesn't have any other character (end of string) will just update the value
    if(word[index+1] == '\0') {
        root->value = value;
    } else {
        for(int i = 0; i < SIZE; i++) {
            if(root->children[i]->key == word[index]) {
                root->children[i] = triInsertRecursion(root->children[i], word, value, index+1);
            } else if(root->children[i] == NULL) {
                root->children[i] = createNode(word[index]);
                root->isLeaf = 0;
                root->children[i] = triInsertRecursion(root->children[i], word, value, index+1);
            }
        }
    }
    return root;
}

Trie* triInsert(Trie* root, char* word, float value) {
    return triInsertRecursion(root, word, value, 0);
}

int isLeaf(Trie* node) {
    for(int i = 0; i < SIZE; i++) {
        if(node->children[i] != NULL)
            return 0;
    }
    return 1;
}

void main() {
    printf("Hello world!");
    Trie* root = createNode('\0');
    root = triInsert(root, "hello", 1.0);
    printf("Hello world!");
}