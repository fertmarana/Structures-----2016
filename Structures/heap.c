/*
NOME: Fernanda Tostes Marana
Numero USP: 4471070
*/
#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "heap.h"

#define FILHO_ESQ 0
#define FILHO_DIR 1

#define HEAP_PRINT 0
#define TREE_PRINT 1

void print_no(int tipo, NO *no){
	if(no != NULL){
		print_item(no->item);

		if(tipo == HEAP_PRINT){
			print_no(HEAP_PRINT,no->filhoesq_heap);
			print_no(HEAP_PRINT, no->filhodir_heap);
		
		} else if (tipo == TREE_PRINT){
			print_no(TREE_PRINT,no->filhoesq_arv);
			printf("printou da esquerda\n");
			print_no(TREE_PRINT, no->filhodir_arv);
			printf("printou da direita\n");
		}
	printf("retornou\n");
		


	}	
	return;
}


void print_heap(HEAP *heap){
	if(heap != NULL){
		print_no(HEAP_PRINT, heap->raiz);
	}
	return;
}

NO *criar_no(ITEM *item){
	NO *no = (NO *)malloc(sizeof(NO));

	if(no != NULL){
		no->filhoesq_heap = NULL;
		no->filhodir_heap = NULL;
		no->filhoesq_arv = NULL;
		no->filhodir_arv = NULL;
		no->pai_heap = NULL;
		no->item = item;
	}

	return no;
}

HEAP *criar_heap(){
	HEAP *heap = (HEAP*)malloc(sizeof(HEAP));

	if(heap!=NULL){
		heap->raiz = NULL;
		heap->tam = 0;
	}
	return heap;
}

void apagar_no(NO **no){
	if(*no != NULL && no != NULL){
		apagar_item(&(*no)->item);
		free((*no)->filhodir_arv);
		(*no)->filhodir_arv = NULL;
		free((*no)->filhoesq_arv);
		(*no)->filhoesq_arv = NULL;
		free((*no)->filhodir_heap);
		(*no)->filhodir_heap = NULL;
		free((*no)->filhoesq_heap);
		(*no)->filhoesq_heap = NULL;
		free(*no);
		*no = NULL;
	}
	return;
}

void apagar_heap_aux(NO *raiz){
	if(raiz != NULL){
		apagar_heap_aux(raiz->filhoesq_arv);
		apagar_heap_aux(raiz->filhodir_arv);
		apagar_no(&raiz);
	}
}

void apagar_heap(HEAP **heap){
	apagar_heap_aux((*heap)->raiz);
	free(*heap);
	*heap = NULL;
}

//funcao que recebem um numero que sera convertido em binario e cada 1 e 0 deste sera colocado num vetor
int *transforma_em_binario(int *tam, int num){
	int i = 0;
	int *vetor = (int*)calloc(100,sizeof(int));

	int *resto=(int*)calloc(100,sizeof(int));

	do{

		resto[i]= (int)num%2;
		num/=2;
	
		i++;
	} while(num != 0);
	*tam = i;
	
	for(int j = 0; j<i; j++){
		vetor[j] = resto[i-j-1];
	}
	return vetor;
}


NO *criar_raiz_heap(HEAP *heap, NO *no){
	if(heap != NULL){
		heap->raiz = no;
	return heap->raiz;
	}
return NULL;
}


//Funcao responsavel por inserir o filho da direita e da esquerda
NO* inserir_filho(int filho, NO *no, NO *pnovo){
	
		if(filho == FILHO_ESQ){
			no->filhoesq_heap= pnovo;
			pnovo->pai_heap = no;
		} else{
			no->filhodir_heap = pnovo;
			pnovo->pai_heap = no;
		}
	
	return pnovo;
}
//funcao do Caio Numero Usp: 
//aqui acontece uma manipulacao dos vetores do pai, avo e filho(s) do no sendo trocado no fix up 
void swap1 (NO *no){
	NO *aux_l = no->filhoesq_heap, *aux_r = no->filhodir_heap, *aux_p = no->pai_heap;

	if (no->pai_heap->filhoesq_heap == no){ //caso o no seja filho da esquerda do pai
			if (no->pai_heap->pai_heap != NULL){ //caso o pai nao seja heap->raiz
				// caso o no tenha um pai filho da esquerda do avo
				if (no->pai_heap->pai_heap->filhoesq_heap == no->pai_heap) no->pai_heap->pai_heap->filhoesq_heap = no;
				// caso o no tenha um pai filho da direita do avo
				if (no->pai_heap->pai_heap->filhodir_heap == no->pai_heap) no->pai_heap->pai_heap->filhodir_heap = no;
			}
			if (no->pai_heap->filhodir_heap != NULL) no->pai_heap->filhodir_heap->pai_heap = no; 
			//caso o irmao do no nao seja nula
			if (no->filhodir_heap != NULL) no->filhodir_heap->pai_heap = no;
			no->filhoesq_heap = no->pai_heap; //o filho da esquerda do no aponta para seu pai
			no->filhodir_heap = no->pai_heap->filhodir_heap; // e seu filho da direita aponta para o filhodir do pai
			no->pai_heap->filhoesq_heap = aux_l;// o pai recebe os antigos filhos do no
			no->pai_heap->filhodir_heap = aux_r;
			no->pai_heap = no->pai_heap->pai_heap; //o pai agora do no eh seu avo
			aux_p->pai_heap = no; // o pai agora do pai eh seu filho da esquerda
			if (no->filhoesq_heap != NULL && no->filhoesq_heap->filhoesq_heap != NULL)
															no->filhoesq_heap->filhoesq_heap->pai_heap = aux_p;
			if (no->filhoesq_heap != NULL && no->filhoesq_heap->filhodir_heap != NULL) 
														 	no->filhoesq_heap->filhodir_heap->pai_heap = aux_p;
		}else if (no->pai_heap->filhodir_heap == no){ // caso o no seja filho da direita do pai
			//o resto eh o mesmo processo descrito acima mas para o no sendo filho da direita
			if (no->pai_heap->pai_heap != NULL){ 
				if (no->pai_heap->pai_heap->filhoesq_heap == no->pai_heap) no->pai_heap->pai_heap->filhoesq_heap = no;
				if (no->pai_heap->pai_heap->filhodir_heap == no->pai_heap) no->pai_heap->pai_heap->filhodir_heap = no;
			}
			if (no->pai_heap->filhoesq_heap != NULL) no->pai_heap->filhoesq_heap->pai_heap = no;
			no->filhodir_heap = no->pai_heap;
			no->filhoesq_heap = no->pai_heap->filhoesq_heap;
			no->pai_heap->filhoesq_heap = aux_l;
			no->pai_heap->filhodir_heap = aux_r;
			no->pai_heap = no->pai_heap->pai_heap;
			aux_p->pai_heap = no;
			no->filhoesq_heap->pai_heap = no;
			if (no->filhodir_heap != NULL && no->filhodir_heap->filhodir_heap != NULL) 
															no->filhodir_heap->filhodir_heap->pai_heap = aux_p;
			if (no->filhodir_heap != NULL && no->filhodir_heap->filhoesq_heap != NULL) 
															no->filhodir_heap->filhoesq_heap->pai_heap = aux_p;
		}
}

//funcao do Caio Numero Usp: 
void fix_up (HEAP *heap, NO *no){
	//verifica essa condicao para continuar ou nao a recursao
	if (no != heap->raiz && no->item->frequencia < no->pai_heap->item->frequencia){ 
		if (no->pai_heap == heap->raiz) heap->raiz = no;
	
		swap1 (no);

		fix_up (heap, no);
	}
}
//funcao que adiciona um no na heap e depois arruma a heap caso o no tenha frequencia menor que de seu pai
int enfileirar(HEAP *heap, NO *no){
	if(heap != NULL){// se a heap estiver alocada

		if(heap->raiz != NULL){ // se ela ter pelo menos um elemento adicionado ja
			int *vetor;
			int n  = 0;
			NO *aux = heap->raiz; //ponteiro que ira percorrer a heap
			vetor = transforma_em_binario(&n,heap->tam+1); //vetor recebe um vetor de 1 e 0 que correspondem ao tamanho atual + 1 da heap
			heap->tam++;
			//aux vai andando ate chegar em um no folha ou um no que tenha apenas o filho da esquerda adicionado
			for(int i = 1; i< n; i++){
				if(vetor[i]==FILHO_ESQ){ // caso a o valor da posicao 1 do vetor seja 0 va para filhoesq
					if(aux->filhoesq_heap == NULL){ //verifica-se se o filho da esquerda existe
						//se nao existir crie um
						aux->filhoesq_heap = no;
						no->pai_heap = aux;
						aux= aux->filhoesq_heap;
						break;
					} else { aux= aux->filhoesq_heap;  } // se existir va para ele
					//o mesmo caso o valor da posicao i do vetor apontar para o filho da direita
				} else if(vetor[i]== FILHO_DIR){
					if(aux->filhodir_heap == NULL){
						
						aux->filhodir_heap = no;
						no->pai_heap = aux;
						aux= aux->filhodir_heap;
						break;
					} else { aux= aux->filhodir_heap; }
				}
			}
			//arrumando heap nova
			fix_up(heap,aux);
		
			return 1;
		} else{ // caso nao tenha nada adicionado na heap alocada

			//o no sera a sua nova raiz
			heap->raiz = criar_raiz_heap(heap, no);

			heap->tam++;
			
			return 1;
		}
	}
	return 0;
}
//funcao do Caio Numero Usp: 
void swap_left (HEAP *heap, NO *raiz){
	NO *aux = raiz->filhoesq_heap, *aux1 = raiz->filhoesq_heap->filhoesq_heap, 
		 *aux2 = raiz->filhoesq_heap->filhodir_heap, *aux3 = raiz->filhodir_heap;

		 if (raiz == heap->raiz) heap->raiz = raiz->filhoesq_heap;

		 raiz->filhodir_heap = aux2;
		 raiz->filhoesq_heap = aux1;
		 if (aux1 != NULL) aux1->pai_heap = raiz;
		 if (aux2 != NULL) aux2->pai_heap = raiz;
		 if (aux3 != NULL) aux3->pai_heap = aux;
		 aux->pai_heap = raiz->pai_heap;
		 if (raiz->pai_heap != NULL){
		 	if (raiz->pai_heap->filhoesq_heap == raiz) raiz->pai_heap->filhoesq_heap = aux;
		 	if (raiz->pai_heap->filhodir_heap == raiz) raiz->pai_heap->filhodir_heap = aux;
		 }
		 raiz->pai_heap = aux;
		 aux->filhodir_heap = aux3;
		 aux->filhoesq_heap = raiz;

}

//funcao do Caio Numero Usp: 
void swap_right (HEAP *heap, NO *raiz){
	//auxiliares recebem os ponteiros do no a ser trocado
	NO *aux = raiz->filhodir_heap, *aux1 = raiz->filhodir_heap->filhoesq_heap, 
		 *aux2 = raiz->filhodir_heap->filhodir_heap, *aux3 = raiz->filhoesq_heap;
		 // se o no for heap->raiz
		if (raiz == heap->raiz) heap->raiz = raiz->filhodir_heap;
		//heap->raiz apontara agora para seu filho da direita

		raiz->filhodir_heap = aux2; //o filho da direita do no recebe o filho da direita do filho da direita
		 raiz->filhoesq_heap = aux1; // o filho da esquerda do no recebe o filho da esquerda de seu filho da direita
			//caso os novos filhos nao sejam null modifica-se o novo pai que apontam
		 if (aux1 != NULL) aux1->pai_heap = raiz; 
		 if (aux2 != NULL) aux2->pai_heap = raiz;
		 if (aux3 != NULL) aux3->pai_heap = aux;
		 aux->pai_heap = raiz->pai_heap; 
		 if (raiz->pai_heap != NULL){ // se a raiz nao for heap->raiz
		 	//modifica-se para onde o ponteiro do pai aponta para seu filho da direita ou da esquerda
		 	if (raiz->pai_heap->filhoesq_heap == raiz) raiz->pai_heap->filhoesq_heap = aux;
		 	if (raiz->pai_heap->filhodir_heap == raiz) raiz->pai_heap->filhodir_heap = aux;
		 }
		 raiz->pai_heap = aux; 
		 aux->filhoesq_heap = aux3;
		 aux->filhodir_heap = raiz;
}



//funcao do Caio Numero Usp: 
void fix_down(HEAP *heap, NO *raiz){
    if (raiz != NULL ){ // caso a raiz nao seja null
    	if (raiz->filhodir_heap == NULL && raiz->filhoesq_heap == NULL) return;
    	//caso haja ainda filhos da esquerda e da direita
        else if (raiz->filhodir_heap == NULL){
        	//se a frequencia da raiz for maior que a de seu filho da esquerda
        	if (raiz->item->frequencia > raiz->filhoesq_heap->item->frequencia){
				swap_left (heap, raiz); //troca-se os ponteiros pelo swap_left
				fix_down(heap, raiz);//arruma-se a heap
        	}
        } else if(raiz->filhoesq_heap->item->simbolo == '#' &&
									raiz->item->frequencia > raiz->filhoesq_heap->item->frequencia &&
									raiz->filhoesq_heap->item->frequencia == raiz->filhodir_heap->item->frequencia){
           //caso o filho da esquerda tenha simbolo # e a raiz seja maior que o filho da esquerda em frequencia
        	// e os dois filhos tenham uma frequencia igual
        	// opta-se por trocar sempre pelo filho da esquerda

            swap_left (heap, raiz);  
            fix_down(heap, raiz);        
        } else if(raiz->filhodir_heap->item->simbolo =='#' &&
									raiz->item->frequencia > raiz->filhoesq_heap->item->frequencia &&
									raiz->filhoesq_heap->item->frequencia == raiz->filhodir_heap->item->frequencia){
           //caso o filho da direita tenha simbolo # e a raiz seja maior que o filho da direita em frequencia
        	// e os dois filhos tenham uma frequencia igual
        	// opta-se por trocar sempre pelo filho da direita

            swap_right (heap, raiz);
            fix_down(heap, raiz->filhodir_heap);    
        } else if (raiz->item->frequencia > raiz->filhoesq_heap->item->frequencia || raiz->item->frequencia > raiz->filhodir_heap->item->frequencia){
        	

        	if (raiz->filhoesq_heap->item->frequencia < raiz->filhodir_heap->item->frequencia){
        		swap_left (heap, raiz);
            	fix_down(heap, raiz);
        	}else {
				swap_right (heap, raiz);
            	fix_down(heap, raiz);
			}
        }
    }
}

// funcao responsavel pela retirada do no raiz e pela substituicao dele pelo ultimo no da heap
NO* desenfileirar(HEAP *heap){
	
	if(heap != NULL && heap->tam!=0){ // verifica-se se tem pelo menos um item adicionado
		if(heap->tam<=3){ // se a heap so ter uma raiz e seus filhos da esquerda e/ou da direita
			if(heap->tam== 1){ // se so houver a raiz da heap
				NO *aux = heap->raiz;
				heap->tam--;
				heap->raiz = NULL; // heap raiz agora aponta para NULL
				return aux;
			
			}else if (heap->tam == 2) { // se so houver heap->raiz e seu filho da esquerda
				//filho da esquerda vira a nova heap->raiz
				NO *aux = heap->raiz;
				aux->filhoesq_heap->filhoesq_heap = aux;
				aux->pai_heap = aux->filhoesq_heap;
				aux->filhoesq_heap = NULL;

				heap->raiz = aux->pai_heap;
				aux->pai_heap->filhoesq_heap = NULL;
				aux->pai_heap = NULL;
				heap->tam--;
				return aux;
			
			}else if (heap->tam == 3) { // se houver heap->raiz e seu filho da esquerda e da direita
				NO *aux = heap->raiz;
				//ha a manipulcao de ponteiros para a heap->raiz ser o filho da esquerda e seu filho
				//ser ainda o filho da esquerda da antiga heap->raiz
				heap->raiz->filhoesq_heap->pai_heap = heap->raiz->filhodir_heap;
				heap->raiz->filhodir_heap->filhoesq_heap = heap->raiz->filhoesq_heap;
				heap->raiz = heap->raiz->filhodir_heap;
				heap->raiz->pai_heap = NULL;
				aux->filhodir_heap = NULL;
				aux->filhoesq_heap = NULL;
				heap->tam--;
				fix_down(heap, heap->raiz); // caso haja um desequilibrio na heap chama-se essa funcao
				return aux;
			}

		}else{ // caso o tamanho da heap seja maior que 3
		NO *ultimo = heap->raiz;
		NO *aux = heap->raiz;
		int *vetor;
		int pos= 0;
		int i;
		vetor = transforma_em_binario(&pos,heap->tam);
		//procura-se onde esta o ultimo filho da heap percorrendo-se o vetor recem criado de 0 e 1
		for(i=1; i<pos; i++){
			if(FILHO_ESQ == vetor[i]) ultimo= ultimo->filhoesq_heap;
			else ultimo = ultimo->filhodir_heap;
		}
		// a partir daqui ha a manipulacao de vetores para que o no achado seja a nova heap->raiz
		if(vetor[i-1] == FILHO_ESQ){ ultimo->pai_heap->filhoesq_heap = NULL; }
		else { ultimo->pai_heap->filhodir_heap = NULL; }
		
		ultimo->pai_heap = NULL;
		ultimo->filhoesq_heap = aux->filhoesq_heap;
		ultimo->filhodir_heap = aux->filhodir_heap;
		if(aux->filhodir_heap != NULL) aux->filhodir_heap->pai_heap = ultimo;
		if(aux->filhoesq_heap != NULL)aux->filhoesq_heap->pai_heap = ultimo;
		aux->filhodir_heap = NULL;
		aux->filhoesq_heap = NULL;
		heap->raiz = ultimo;
		heap->tam--;
		//caso haja um desequilibrio na condicao da heap chama-se a funcao fix_down para arrumar
		fix_down(heap, heap->raiz);
		return aux;
		}


	}

	return NULL;
}


int tamanho_heap(HEAP *heap){
	return heap->tam;
}



