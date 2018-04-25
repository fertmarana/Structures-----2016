#include <stdlib.h>
#include <stdio.h>

typedef struct ITEM ITEM;

struct ITEM
{
	int frequencia;
	char simbolo;
};

ITEM *criar_item(int frequencia, char simbolo){
	ITEM *item = (ITEM*)malloc(sizeof(ITEM));

	if(item != NULL){
		item->frequencia = frequencia;
		item->simbolo = simbolo;
	}

return item;
}

void apagar_item(ITEM **item){
if(*item != NULL && item != NULL){
		free(*item);
		*item= NULL;
	}
	return;
}

void print_item(ITEM *item){
	if(item != NULL){
		printf("frequencia: %d\n", item->frequencia);
		printf("simbolo: %c\n", item->simbolo);
	}
	return;
}