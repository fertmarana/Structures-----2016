/*
NOME: Fernanda Tostes Marana
Numero USP: 4471070
*/
#include "huffman.h"


HUFFMAN *criarTabelaHuffman(){
	HUFFMAN *huff = (HUFFMAN*)malloc(sizeof(HUFFMAN));
	if(huff != NULL){
		huff->arvore = criar_arvore();
	}
return huff;
}


void gerar_tabela_simbolos(HUFFMAN *huffman, NO *raiz, char *simbolo, int pos){
	if(raiz->filhoesq_arv == NULL && raiz->filhodir_arv == NULL){
		simbolo[pos+1] = '\0';
		strcpy(huffman->tabela[raiz->item->simbolo], simbolo);

	} else{
		if(raiz->filhoesq_arv != NULL) {
			pos++;
			simbolo[pos] = '0';
			gerar_tabela_simbolos(huffman,raiz->filhoesq_arv,simbolo,pos);
			pos--;
			
		}
		if(raiz->filhoesq_arv != NULL){
		 pos++;
		 simbolo[pos] = '1';
		 gerar_tabela_simbolos(huffman,raiz->filhodir_arv,simbolo,pos);
		 pos--;
		}
	}


}


void contagem_frequencia(int *freq, char *msg){
	for(int i = 0; i< NR_SIMBOLOS; i++) freq[i] = 0;
	for(int i = 0; msg[i]!='\0'; i++) freq[(int)msg[i]]++;
}

//funcao responsavel por compactar a mensagem em uma string de 0 e 1
//sendo cada combinacao representante de um determinado char
int compactarHuffman(char* msg,char **comp,HUFFMAN *huffman){
	
	int freq[NR_SIMBOLOS];
	
	contagem_frequencia(freq,msg);
	//realiza-se a contagem de frequencia de cada char possivek

	HEAP *heap = criar_heap();
	//cria-se a heap
	
	if(heap != NULL){
		for(int i = 0; i< NR_SIMBOLOS; i++){
			if(freq[i]>0){
				NO *no = criar_no( criar_item(freq[i], (char)i) );
				enfileirar(heap,no);
				
			}

		}
	//a partir daqui realiza-se o processo de retirar os dois nos com menor frequencia e adicionar um
		// outro na heap criado a partir desses
	while(tamanho_heap(heap)>1){
		NO *fesq = desenfileirar(heap);
		NO *fdir = desenfileirar(heap);
		NO *no =(NO*)malloc(sizeof(NO));
		
		no->filhoesq_arv = fesq;
		fesq->pai_arv = no;

		no->filhodir_arv = fdir;
		fdir->pai_arv = no;
	
		no->filhoesq_heap = NULL; 
		no->filhodir_heap = NULL;
		no->pai_heap = NULL;
		no->item = criar_item(fesq->item->frequencia + fdir->item->frequencia,'#');
		
	

		enfileirar(heap, no);
		
	}		
	
	//depois de criar a heap
	NO *ok = heap->raiz;
	//cria-se a arvore com o unico no que sobrou
	NO *raiz = criar_raiz_arv(huffman->arvore,ok );
	//apagar_heap(&heap);
	
	
	char simbolo[TAM];
	gerar_tabela_simbolos(huffman, raiz,simbolo,-1);
	//gera-se uma tabela de simbolos que percorre o huffman
	int j = 0;
	int size = 0;
	(*comp) = (char*)malloc(sizeof(char)*100000);
	//aloca-se espaco para a nova string
	for(int i = 0; msg[i] != '\0'; i++){
		size += strlen(huffman->tabela[(int)msg[i]]);
		
		strcat(*comp, huffman->tabela[(int)msg[i]]);
		//funcao que coloca cada pequena string q forma uma letra na string grande *comp
	}
return size; //retorna-se o tamanho da string compactada
	}
	return 0;
}



//funcao responsavel por descompactar a mensegam compactada
char* descompactarHuffman(char* comp,int size, HUFFMAN *huffman){
	NO * raiz = huffman->arvore->raiz;
	int index = 0;
	char *msg = NULL;
	for(int i = 0; i<=size; i++){
		if(raiz->filhoesq_arv == NULL && raiz->filhodir_arv == NULL){
			msg = (char*)realloc(msg,sizeof(char)*(index+1));
			msg[index] = raiz->item->simbolo;
			index++;
			raiz = huffman->arvore->raiz;
			i--;
		} else {
			if(comp[i] == '0'){
				raiz = raiz->filhoesq_arv;
			} else if(comp[i]=='1'){
				raiz = raiz->filhodir_arv;
			}
		}
	}
	msg[index] = '\0';

	return msg;
}


void liberarTabelaHuffman(HUFFMAN **huffman){
	if(huffman != NULL){
		apagar_arvore(&((*huffman)->arvore));
	}
	free(*huffman);
	(*huffman) = NULL;


}