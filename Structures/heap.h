/*
NOME: Fernanda Tostes Marana
Numero USP: 4471070
*/
#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include "item.h"

#define FILHO_ESQ 0
#define FILHO_DIR 1

#define HEAP_PRINT 0
#define TREE_PRINT 1


typedef struct heap_dinamica HEAP;
typedef struct arvore_binaria ARVORE;
typedef struct NO NO;

struct NO{
	ITEM *item;
	NO *filhoesq_heap;
	NO *filhodir_heap;
	NO *filhoesq_arv;
	NO *filhodir_arv;
	NO *pai_heap;
	NO *pai_arv;
};

struct heap_dinamica
{
	NO *raiz;
	int tam;
};

void swap_1(NO *no);
int tamanho_heap(HEAP *heap);
void print_no(int tipo, NO *no);
void print_heap(HEAP *heap);
NO *criar_no(ITEM *item);
HEAP *criar_heap();
void apagar_no(NO **no);
void apagar_heap_aux(NO *raiz);
void apagar_heap(HEAP **heap);
NO *criar_raiz(HEAP *heap, ITEM* item);
int *transforma_em_binario(int *tam, int num);
NO* inserir_filho_no(int filho, NO *no, ITEM *item);
void fix_up(HEAP *heap, NO *aux);
int enfileirar(HEAP *heap, NO *no);
void swap_right (HEAP *heap, NO *raiz);
void swap_left (HEAP *heap, NO *raiz);
void fix_down(HEAP *heap, NO *raiz);
NO* desenfileirar(HEAP *heap);


#endif