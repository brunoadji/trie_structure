//characters allowed: abcdefghijklmnopqrstuvwxyz0123456789_
//amount of characters allowed
#define SIZE 37

typedef struct TrieNode {
    struct TrieNode* children[SIZE];
    float value;
    char* key;
    int isLeaf;
} Trie;

int trie_busca(Trie* no, char* word){
	//if(no == NULL)
		//return 0; //retorna 0 se nó vazio
	struct Trie* aux = no;
	for(int i = 0; word[i]!='\0'; i++){ //for para mover posiçao da string
		int letra = word[i] - 'a'; //armazena o valor da posicao
		if(aux->children[letra] == NULL) //checa se no existe
			return 0;
		aux = aux->children[letra]; //move para filho
	}
	if(aux != NULL && aux->isLeaf == 1) //retorna se no é folha
		return 1;
	return 0;
}