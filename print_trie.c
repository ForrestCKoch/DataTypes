/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : print_trie.c

* Purpose : read a bunch of words from stdin then print out occurences
* of each word

* Creation Date : 28-10-2016

* Last Modified : Mon 31 Oct 2016 07:48:22 PM AEDT

* Created By : Forrest Koch 

_._._._._._._._._._._._._._._._._._._._._.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

int main(void){

    trie_t trie = new_trie();
    char word[MAX_WORD_LENGTH];

    while(fgets(word,MAX_WORD_LENGTH,stdin)){
        word[strcspn(word,"\n")] = 0;
        insert_to_trie(trie,word);
    }

    print_trie(trie);
    dest_trie(trie);

    return 0;
}
