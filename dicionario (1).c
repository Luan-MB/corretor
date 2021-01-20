// GRR20190363 Luan Machado Bernardt
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"

#define STEP 10000

// FUnção que carrega o dicionario em memória e retorna um ponteiro
char **load_dict (int *len) {

	// Procura o arquivo do dicionario em seu lugar padrão
	// Senão encontrar, tenta-se abrir no mesmo diretório
	FILE *arq = fopen("/usr/share/dict/brazilian","r");
	if (!arq) {
		arq = fopen("brazilian","r");
		if(!arq) {
			perror("Não foi possível abrir o arquivo");
			return NULL;
		}
	}

	char **words;
	char input[MAX_SIZE];
	int wlen;
        int tam;
        int i = 0;

	// Aloca inicialmente STEP espaços para elementos do vetor
	tam = STEP;
	words = malloc (tam * sizeof(char *));

	// Enquanto não for o fim do arquivo realizam-se as seguintes ações
	while (!feof(arq)) {
		// Aloca-se mais espaço sempre que o indice i for igual ao tamanho pré-alocado
		if (i == tam) {
			tam += STEP;
			words = realloc (words, tam * sizeof(char *));
		}
		
		// Lê de STDIN uma palavra (input) com tamanho máximo (MAX_SIZE)
		// Calcula-se o tamanho de input, alocando o tamanho exato no elemento de indice i
		// Trata-se o input, retirando '\n' e acrescentando '\0' ao final do mesmo
		// Copia-se input no elemento de indice i do dicionario
		fgets(input,MAX_SIZE,arq);
		wlen = strlen(input);
		words[i] = malloc (wlen * sizeof(char));
		input[wlen-1] = '\0';
		strcpy(words[i],input);
		i++;
	}
	*len = i;
	// Fecha-se o arquivo
	fclose(arq);
	return words;
}
// Função necessária para realizar a comparação no qsort
// Recebe dois elementos const void e faz o casting para um vetor de caracteres
// Retorna o resultado da comparação insensível a case entre as duas strings
int word_compare_dict (const void* word1, const void* word2) {

	char *w1 = *(char**)word1;
	char *w2 = *(char**)word2;

	return strcasecmp(w1,w2);
}
// Função que utiliza a função qsort para reordenar dict de tamanho len
// Compara por meio da função word_compare_dict
void sort_dict (char **dict, int len) {

	qsort(dict,len,sizeof(char *),word_compare_dict);
}

// Função que procura dada palavra (word) em dict e retorna 1 se encontrou e 0 se não
int search_dict (char *word, char **dict, int len) {

	int fim = len-1;
	int meio;
	int ini = 0;
	
	// Algoritmo de busca binaria
	while (ini<=fim) {
		meio = (ini + fim)/2;
		if (strcasecmp(word,dict[meio]) < 0)
			fim = meio -1;
		else if (strcasecmp(word,dict[meio]) > 0)
			ini = meio +1;
		else return 1;
	}
	return 0;
}

// Função que desaloca todas as palavras da memória
// Aponta dict para NULL
void free_dict (char **dict, int len) {

	int i;

	for (i=0;i<len;i++)
		free(dict[i]);
	free(dict);
	dict = NULL;
}
