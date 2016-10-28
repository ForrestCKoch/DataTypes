/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : trie.c

* Purpose : provides a trie for handling strings

* Creation Date : 28-10-2016

* Last Modified : Fri 28 Oct 2016 07:10:19 PM AEDT

* Created By : Forrest Koch 

_._._._._._._._._._._._._._._._._._._._._.*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "trie.h"
#include "bst.h"

typedef struct _trie_node_t{
    char value;
    bst_t children;
    int is_key;
}* trie_node_t;

struct _trie_t{
    trie_node_t root;
};

static trie_node_t new_trie_node(char c, int is_key);
static void dest_trie_node(trie_node_t node);

trie_t new_trie(){
    trie_t trie = malloc(sizeof(struct _trie_t));
    trie->root = new_trie_node(0,false);
    return trie;
}
void dest_trie(trie_t trie){
    dest_trie_node(trie->root);
    free(trie);
    return;
}
void insert_to_trie(trie_t trie, char *word){
    // return if empty string
    if(!word[0]) return;
    // initialize vars
    int curr_index = 0;
    trie_node_t curr_node = trie->root;
    trie_node_t next_node = is_in_bst(curr_node->children, word[curr_index]);
    // find our spot in the trie to keep building;
    while(next_node && word[curr_index+1]){
        curr_index++;
        curr_node = next_node;
        next_node = is_in_bst(curr_node->children, word[curr_index]);
    }
    // first check we aren't at the end
    while(word[curr_index+1]){
        next_node = new_trie_node(word[curr_index],false);
        insert_to_bst(curr_node->children, next_node, next_node->value);
        curr_index++;
        curr_node = next_node;
    }
    // now we either need mark the next node on or create a new node
    // to serve as a key
    next_node = is_in_bst(curr_node->children, word[curr_index]);
    if(next_node) next_node->is_key++;
    else{
        next_node = new_trie_node(word[curr_index],true);
        insert_to_bst(curr_node->children, next_node, next_node->value);
    }
}
int is_in_trie(trie_t trie, char *word){
    trie_node_t curr_node = trie->root;
    int curr_index = 0;
    // traverse until we run out of nodes or letters
    while(curr_node && word[curr_index]){
        curr_node = is_in_bst(curr_node->children, word[curr_index++]);
    }
    // if we've reached the end of our word and it's a key return true
    // else false
    if(!word[curr_index] && curr_node) return curr_node->is_key;
    else return false;
}

void print_trie(trie_t trie);

static trie_node_t new_trie_node(char c, int is_key){
    trie_node_t node = malloc(sizeof(struct _trie_node_t));
    node->value = c;
    node->children = new_bst(); 
    node->is_key = is_key;
    return node;
}
static void dest_trie_node(trie_node_t node){
    int curr_value;
    trie_node_t curr;

    while(size_of_bst(node->children)){
        // get the lowest value in tree.
        // later this can be optimized but for now, meh
        curr_value = get_min_bst(node->children);
        curr = is_in_bst(node->children, curr_value);
        // call recursively to destroy any further trees
        dest_trie_node(curr);
        // now that that node has been destroyed remove from tree
        // noting the the memory should have already been free'd
        remove_from_bst(node->children, curr_value, false);
    }
    // tree should be empty, dispose of it then self
    dest_bst(node->children, false);
    free(node);
    return;
}

