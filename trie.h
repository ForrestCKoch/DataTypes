#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#define MAX_WORD_LENGTH 64

typedef struct _trie_t *trie_t;
// returns a pointer to a trie type
trie_t new_trie();
// free's all memory associated with the trie
void dest_trie(trie_t trie);
// add a word to the trie
void insert_to_trie(trie_t trie, char *word);
// return the number of times a word has been inserted
int is_in_trie(trie_t trie, char *word);

// print out the words with their occurence rate
void print_trie(trie_t trie);

#endif
