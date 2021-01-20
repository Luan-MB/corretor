// GRR20190363 Luan Machado Bernardt
#ifndef __DICIONARIO__
#define __DICIONARIO__

// Definição de tamanho máximo de palavra, definido como 50 pois é suficiente para receber qualquer palavra portuguesa
#define MAX_SIZE 50

// Função responsável por carregar o dicionario em memória e devolver o tamanho (len) do mesmo
char **load_dict (int *len); 

// Função necessária para o funcionamento do qsort, recebe duas palavras (word1 e word2) no formato const void
int word_compare_dict (const void *word1, const void *word2);

// Função que recebe o dicionario (dict) e seu tamanho (len) para que o mesmo seja ordenado por meio de qsort
void sort_dict (char **dict, int len);

// Função de busca binária que procura uma palavra (word) no dicionario (dict) com dado tamanho (len) alocado em memória
int search_dict (char *word, char **dict, int len);

// Função que desaloca da memória o dicionario (dict) de dado tamanho (len)
void free_dict (char **dict, int len);

#endif
