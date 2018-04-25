/*
NOME: Fernanda Tostes Marana
Numero USP: 4471070
*/
#ifndef ITEM_H
#define ITEM_H

#include <stdlib.h>
#include <stdio.h>

typedef struct ITEM ITEM;

struct ITEM
{
	int frequencia;
	char simbolo;
};

ITEM *criar_item(int frequencia, char simbolo);
void apagar_item(ITEM **item);
void print_item(ITEM *item);

#endif