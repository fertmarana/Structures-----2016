all: clean item.o arvore_binaria.o heap.o huffman.o main.o compile clean

compile:	
	gcc item.o arvore_binaria.o heap.o huffman.o main.o -o trab4 -lm 
main.o:
	gcc -c main.c 
heap.o:
	gcc -c heap.c 
huffman.o:
	gcc -c huffman.c 
arvore_binaria.o:
	gcc -c arvore_binaria.c 
item.o:
	gcc -c item.c 	
clean:
	find -name '*~' | xargs rm -rf {}
	find -name '*.o' | xargs rm -rf {}
run:
	./trab4
zip:
	zip -r trab4 *.c *.h Makefile