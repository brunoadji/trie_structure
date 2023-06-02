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
        if(node->children[i] != NULL){
            //printf("Filho encontrado em %d \n", i);
            return 0;
        }
        //printf("Filho nao encontardo em %d \n", i);
    }
    printf("Sem filhos! \n");
    return 1;
}

int isNotRelevant(Trie* node) {
    return (noChildren(node) && !node->isTerminal);
}

Trie* freeNode(Trie* node) {
    free(node);
    node = NULL;
    return node;
}

Trie* triRemoveRecursion(Trie* root, char* key, int index, int* success) {
    //checking if node exists
    if(root != NULL) {
        //found the node
        if(key[index] == '\0') {
            if(root->isTerminal) {
                //printf("is terminal\n");
                *success = 1;
                root->isTerminal = 0;
                //if node isn't relevant anymore, delete it.
                if(isNotRelevant(root)){
                    printf("Removendo no %c", key[index]);
                    root = freeNode(root);
                }
            }
        } else {
            int i = getIndex(key[index]);
            root->children[i] = triRemoveRecursion(root->children[i], key, index+1, success);
            //if one child from node have been deleted
            if(root->children[i] == NULL) {
                if(isNotRelevant(root)){
                    printf("Removendo no %c", key[index]);
                    root = freeNode(root);
                }
            }
        }
    }
    return root;
}

int triRemove(char* key) {
    int success = 0;
    root = triRemoveRecursion(root, key, 0, &success);
    return success;
}

int triSearchRecursion(Trie* root, char* word, float value, int index){
    if(root == NULL) return 0; //checa se node existe
    if(root->isTerminal == 1 && word[index] == '\0') return 1; //condicao para palavra existir
    int i = getIndex(word[index]); //atualiza index
    //printf("Procurando letra %c\n", word[index]);
    //printf("%d\n", root->isTerminal);
    //printf("%f\n", root->value);
    return triSearchRecursion(root->children[i], word, value, index+1); //avança para proxima letra
}

int triSearch(char* word, float value){
    if(triSearchRecursion(root, word, value, 0) != NULL) return 1;
    return 0;
}

int main() {
    root = createNode('\0');
    //triInsert("Flu", 3);
    triInsert("car", 42);
    triInsert("cat", 7);
    printf("%d\n", triSearch("Flu", 3));
    printf("%d\n", triSearch("car", 42));
    printf("%d\n", triSearch("cat", 7));
    printf("%d\n", triSearch("cool", 1024));
    triRemove("car");
    printf("%d\n", triSearch("car", 42));
}