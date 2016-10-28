CC=gcc
CFLAGS=-g -Wall -pg
bins= interpreter test_bst test_graph stress_graph test_queue test_trie\
	print_trie

all: $(bins)

print_trie: print_trie.c trie.o trie.h bst.o

interpreter: graph.o interpreter.c bst.o

test_graph: graph.o test_graph.c bst.o

stress_graph: graph.o stress_graph.c bst.o

test_bst: bst.o test_bst.c

test_queue: queue.o test_queue.c

test_trie: trie.o bst.o test_trie.c

bst.o: bst.c bst.h

graph.o: graph.c graph.h bst.h

queue.o: queue.c queue.h

trie.o: trie.c trie.h bst.h

clean:
	rm *.o $(bins)
