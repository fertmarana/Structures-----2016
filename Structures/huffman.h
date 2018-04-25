/*
NOME: Fernanda Tostes Marana
Numero USP: 4471070
*/
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "item.h"
#include "heap.h"
#include "arvore_binaria.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define TAM 256
#define NR_SIMBOLOS 256

typedef struct huffman HUFFMAN;
struct huffman {
	ARVORE_BINARIA *arvore;
	char tabela[NR_SIMBOLOS][TAM];
};

HUFFMAN *criarTabelaHuffman();
void liberarTabelaHuffman(HUFFMAN **huffman);

void contagem_frequencia(int *freq, char *msg);
int compactarHuffman(char* msg,char **comp,HUFFMAN *huffman);
char* descompactarHuffman(char* comp,int size, HUFFMAN *huffman);


#endif