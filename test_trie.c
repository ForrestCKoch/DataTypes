/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : test_trie.c

* Purpose :

* Creation Date : 28-10-2016

* Last Modified : Fri 28 Oct 2016 05:43:39 PM AEDT

* Created By : Forrest Koch 

_._._._._._._._._._._._._._._._._._._._._.*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "trie.h"

int main(void){
    printf("Testing trie...\n");
    trie_t trie = new_trie();
    insert_to_trie(trie, "hello");
    insert_to_trie(trie, "hell");
    assert(is_in_trie(trie, "hello"));
    assert(is_in_trie(trie, "hell"));
    dest_trie(trie);
    
    trie = new_trie();
    insert_to_trie(trie, "hell");
    insert_to_trie(trie, "hello");
    assert(is_in_trie(trie, "hell"));
    assert(is_in_trie(trie, "hello"));
    dest_trie(trie);

    trie = new_trie();
    insert_to_trie(trie, "hello");
    assert(!is_in_trie(trie, "hell"));
    assert(is_in_trie(trie, "hello"));
    dest_trie(trie);

    trie = new_trie();
    insert_to_trie(trie, "hell");
    assert(!is_in_trie(trie, "hello"));
    assert(is_in_trie(trie, "hell"));
    dest_trie(trie);

    trie = new_trie();
    insert_to_trie(trie, "hell");
    insert_to_trie(trie, "hello");
    assert(!is_in_trie(trie, "hel"));
    assert(is_in_trie(trie, "hello"));
    dest_trie(trie);

    trie = new_trie();
    insert_to_trie(trie, "hell");
    insert_to_trie(trie, "hello");
    assert(!is_in_trie(trie, "help"));
    assert(is_in_trie(trie, "hello"));
    dest_trie(trie);

    trie = new_trie();
    insert_to_trie(trie, "hello");
    insert_to_trie(trie, "hello");
    assert(is_in_trie(trie, "hello") == 2);
    dest_trie(trie);

    return 0;
}

