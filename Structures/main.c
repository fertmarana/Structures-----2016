/*
NOME: Fernanda Tostes Marana
Numero USP: 4471070
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "heap.h"
#include "arvore_binaria.h"
#include "huffman.h"

int main(int argc, char *argv[]){
	
	int i;
	char *text, *textCompac, *textDescompac;
	text = (char *)malloc(10001 * sizeof(char));
	HUFFMAN *tabela = criarTabelaHuffman();//cria a tabela de huffman

	//le o texto que sera compactado
	for(i = 0; (text[i] = getchar()) != '\n' && i < 10000; ++i);
	text[i] = '\0';
	//printf("%s\n", text);
	
			
	//compacta o texto e modifica a tabela
	int sizeCompac = compactarHuffman(text, &textCompac, tabela);
	//printf("compactou\n");
	//descompacta o texto baseado na tabela criada
	textDescompac = descompactarHuffman(textCompac, sizeCompac, tabela);
	//printf("descompactou\n");
	//imprime o tamanho do texto original
	printf("%d\n",(int)strlen(text));
	//imprime o tamanho do texto compactado
	printf("%d\n",sizeCompac/8 +2);
	//imprime o texto descompactado
	printf("%s\n",textDescompac);

	//libera a memoria alocada para a tabela de Huffman
	liberarTabelaHuffman(&tabela);
	free(text);
	free(textCompac);
	free(textDescompac);

  	return 0;
}

