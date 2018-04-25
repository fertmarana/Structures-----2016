/*
NOME: Fernanda Tostes Marana
Numero USP: 4471070
*/
#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "heap.h"

typedef struct ARVORE_BINARIA ARVORE_BINARIA;

struct ARVORE_BINARIA
{
	NO *raiz;
	int tam_tree;
};


NO *criar_raiz_arv(ARVORE_BINARIA *arv, NO *no);
void print_arvore(ARVORE_BINARIA *arv);
ARVORE_BINARIA *criar_arvore();
void apagar_arvore_aux(NO *raiz);
void apagar_arvore(ARVORE_BINARIA **arv);

#endif