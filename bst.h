#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdlib.h>
// a binary search tree data type for use with void *'s
typedef struct _bst_t *bst_t;

// test rotation functions
void test_rotate(void);

// returns an empty bst_t
bst_t new_bst();
// free's all memory associated with the bst_t
// if free_flag = true then free all ptrs
void dest_bst(bst_t bst, bool free_flag);

bool valid_bst(bst_t bst);

// insert a key to the bst_t
void insert_to_bst(bst_t bst, void *ptr, int key);
// remove a key from the bst_t, if free_flag = true then free the ptr
void remove_from_bst(bst_t bst, int key, bool free_flag);
// returns the void * associated with a key if it exists, else returns NULL
void *is_in_bst(bst_t bst, int key);
// returns the number of nodes in the bst
size_t size_of_bst(bst_t bst);
// should we do automatically?
void balance_tree(bst_t bst);
// return the key of the lowest value in the tree
int get_min_bst(bst_t bst);
int get_max_bst(bst_t bst);
int get_head_bst(bst_t bst);
// returns an ordered array from the bst
int *bst_to_array(bst_t bst);

#endif
