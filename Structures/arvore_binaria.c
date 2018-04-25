/*
NOME: Fernanda Tostes Marana
Numero USP: 4471070
*/
#include <stdlib.h>
#include <stdio.h>
#include "arvore_binaria.h"




ARVORE_BINARIA *criar_arvore(){
	ARVORE_BINARIA *arv = (ARVORE_BINARIA*)malloc(sizeof(ARVORE_BINARIA));
	if(arv != NULL){
		arv->raiz = NULL;
	}
return arv;
}

void print_arvore(ARVORE_BINARIA *arv){
	if(arv != NULL){
		print_no(TREE_PRINT, arv->raiz);
	}
	return;
}

NO *criar_raiz_arv(ARVORE_BINARIA *arv, NO *no){
	arv->raiz = (NO*)malloc(sizeof(NO));
	if(arv->raiz != NULL){
		arv->raiz = no;
	}
	return arv->raiz;
}

void apagar_arvore_aux(NO *raiz){
	if(raiz != NULL){
		apagar_arvore_aux(raiz->filhoesq_arv);
		apagar_arvore_aux(raiz->filhodir_arv);
		apagar_item(&(raiz)->item);
		free(raiz);
	}
}

void apagar_arvore(ARVORE_BINARIA **arv){
	apagar_arvore_aux((*arv)->raiz);
	free(*arv);
	(*arv) = NULL;
}