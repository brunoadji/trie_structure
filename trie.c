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
    //if its end of word
    if(word[index] == '\0') {
        if(!root->isTerminal) {
            root->value = value;
            root->isTerminal = 1;
        }
        else return 0;
    } else {
        int i = getIndex(word[index]);
        if(root->children[i] == NULL) {
            root->children[i] = createNode();
        }
        root->children[i] = triInsertRecursion(root->children[i], word, value, index+1);
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

int isNotRelevant(Trie* node) {
    return (noChildren(node) && !node->isTerminal);
}

Trie* freeNode(Trie* node) {
    if(isNotRelevant(node)) {
        free(node);
        node = NULL;
    }
    return node;
}

Trie* freeTrie(Trie* node) {
    if(node != NULL) {
        node->isTerminal = 0;
        for(int i = 0; i < SIZE; i++) {
            node->children[i] = freeTrie(node->children[i]);
        }
        node = freeNode(node);
    }
    return node;
}

void cleanTrie() {
    root = freeTrie(root);
    root = createNode();
}

Trie* triRemoveRecursion(Trie* root, char* key, int index, int* success) {
    //checking if node exists
    if(root != NULL) {
        //found the node
        if(key[index] == '\0') {
            if(root->isTerminal) {
                *success = 1;
                root->isTerminal = 0;
                //if node isn't relevant anymore, delete it.
                root = freeNode(root);
            }
        } else {
            int i = getIndex(key[index]);
            root->children[i] = triRemoveRecursion(root->children[i], key, index+1, success);
            //if one child from node have been deleted
            if(root->children[i] == NULL) {
                root = freeNode(root);
            }
        }
    }
    return root;
}


//if didn't removed any key return 0, otherwise return 1
int triRemove(char* key) {
    int success = 0;
    root = triRemoveRecursion(root, key, 0, &success);
    return success;
}

Trie* triSearchRecursion(Trie* root, char* word, int index){
    //check if node exists
    if(root != NULL) {
        // check if we found what we want
        if(word[index] == '\0') {
            return root;
        }
        int i = getIndex(word[index]); //update index
        return triSearchRecursion(root->children[i], word, index+1); //keep going recursion :)
    }
    return NULL;
}

int triSearch(char* word, float* value){
    Trie* find;
    find = triSearchRecursion(root, word, 0);
    if(find != NULL) {
        if(!find->isTerminal) return 0;
        *value = find->value;
        return 1;
    }
    return 0;
}

int triUpdate(char* word, float newValue) {
    Trie* find = triSearchRecursion(root, word, 0);
    if(!find) return 0;
    find->value = newValue;
    return 1;
}

int main() {
    root = createNode();
    triInsert("car", 42);
    triInsert("tri", 7.0);
    float value;
    printf("%d\n", triSearch("tri", &value)); //Deve printar 1
    printf("%f\n", value); //Deve printar 7.0
    printf("%d\n", triSearch("ca", &value)); //Deve printar 0
    printf("%f\n", value); //Deve printar 7.0
    triUpdate("tri", 8.0);
    printf("%d\n", triSearch("tri", &value)); //Deve printar 1
    printf("%f\n", value); //Deve printar 8.0
    triRemove("tri");
    printf("%d\n", triSearch("tri", &value)); //Deve printar 0
    printf("%f\n", value); //Deve printar 8.0
    printf("%d\n", triSearch("car", &value)); //Deve printar 1
    printf("%f\n", value); //Deve printar 42.0
}

/*
    Expected results:
    1
    7.0
    0
    7.0
    1
    8.0
    0
    8.0
    1
    42.0
*/