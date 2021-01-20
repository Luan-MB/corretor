// GRR20190363 Luan Machado Bernardt
#include "dicionario.h"
#include <locale.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main () {
	
	char **dici;
	int len, i;
	char word[MAX_SIZE];
	char c;

	// Define o locale para que as funcoes da lib "ctype.h" funcionem com chars acentuados e cedilha
	setlocale(LC_CTYPE,"pt_BR.iso88591");
	// Carrega-se o dicionário em dici
	dici = load_dict(&len);
	i = 0;
	// O dicionário está ordenado em ABC...abc...ÁÂ...áâ
	// Reordena-se o dicionário na ordem alfabética ignorando casing
	sort_dict(dici,len);
	
	// Recebe-se chars até encontrar EOF (fim do arquivo)
	while ((c = getchar()) != EOF) {
		// Se c pertencer ao alfabeto, salva-se c em um vetor
		if (isalpha(c)) {
			word[i] = c;
			word[i+1] = '\0';
			i++;
		// Se c nao pertencer ao alfabeto, c é um espaço ou pontuação
		// Logo, terminou-se de ler uma possível palavra
		} else { 
			
			// Se o índice i for maior que 0 significa que há uma palavra no vetor
			if (i != 0) {	
				// Procura-se word no dicionário
				// Se encontrada word é impressa em seu formato original
				// Se não encontrada word é impressa entre colchetes [word]
				if (search_dict(word,dici,len))
					printf("%s",word);
				else
					printf("[%s]",word);
				// Zera-se o índice para que uma nova palavra seja lida
				i = 0;
			}
			// Caracteres de acentuação são impressos na mesma posição original
			printf("%c",c);
			
		}
	}
	// Desaloca-se o dicionario da memoria
	free_dict(dici,(len));
	return 0;
}
