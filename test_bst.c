/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : test_bst.c

* Purpose : quick test for the bst ADT

* Creation Date : 24-09-2016

* Last Modified : Fri 28 Oct 2016 07:37:11 PM AEDT

* Created By : Forrest Koch 

_._._._._._._._._._._._._._._._._._._._._.*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"

void test_forward(void);
void test_reverse(void);
void test_free_flag(void);
void test_balance(void);
void test_bst_to_array(void);

typedef struct _test_t{
    int key;
}test_t;

int main(void){

    printf("\nTesting bst ADT ...\n");
    test_forward();
    test_reverse();
    test_free_flag();
    printf("\tTesting node rotations...\n");
    // outdated tests, they exploit the fact the the tree didn't used to
    // balance itself...
    //test_rotate();
    //test_balance();
    test_bst_to_array();
    printf("\tAll tests passed ...\n");

    return 0;
}
void test_forward(void){
    
    printf("\tTesting deletion low-high of balanced tree... ...\n");

    test_t *array = malloc(15*sizeof(test_t));
    for(int i = 0; i < 15; i++) array[i].key = i;

    bst_t bst = new_bst();
    insert_to_bst(bst, (void *)&array[7], array[7].key);
    insert_to_bst(bst, (void *)&array[11], array[11].key);
    insert_to_bst(bst, (void *)&array[3], array[3].key);
    insert_to_bst(bst, (void *)&array[13], array[13].key);
    insert_to_bst(bst, (void *)&array[9], array[9].key);
    insert_to_bst(bst, (void *)&array[1], array[1].key);
    insert_to_bst(bst, (void *)&array[5], array[5].key);
    insert_to_bst(bst, (void *)&array[0], array[0].key);
    insert_to_bst(bst, (void *)&array[2], array[2].key);
    insert_to_bst(bst, (void *)&array[4], array[4].key);
    insert_to_bst(bst, (void *)&array[6], array[6].key);
    insert_to_bst(bst, (void *)&array[8], array[8].key);
    insert_to_bst(bst, (void *)&array[10], array[10].key);
    insert_to_bst(bst, (void *)&array[12], array[12].key);
    insert_to_bst(bst, (void *)&array[14], array[14].key);

    for(int i = 0; i < 15; i++){
        for(int j = i; j < 15; j++){
            assert(((test_t *)is_in_bst(bst,j))->key == j);
        }
        remove_from_bst(bst, i, false);
    }
    dest_bst(bst, false);
    free(array);
}
void test_reverse(void){

    printf("\tTesting deletion high-low of balanced tree... ...\n");
    
    test_t *array = malloc(15*sizeof(test_t));
    for(int i = 0; i < 15; i++){
        array[i].key = i;
    }

    bst_t bst = new_bst();
    insert_to_bst(bst, (void *)&array[7], array[7].key);
    insert_to_bst(bst, (void *)&array[11], array[11].key);
    insert_to_bst(bst, (void *)&array[3], array[3].key);
    insert_to_bst(bst, (void *)&array[13], array[13].key);
    insert_to_bst(bst, (void *)&array[9], array[9].key);
    insert_to_bst(bst, (void *)&array[1], array[1].key);
    insert_to_bst(bst, (void *)&array[5], array[5].key);
    insert_to_bst(bst, (void *)&array[0], array[0].key);
    insert_to_bst(bst, (void *)&array[2], array[2].key);
    insert_to_bst(bst, (void *)&array[4], array[4].key);
    insert_to_bst(bst, (void *)&array[6], array[6].key);
    insert_to_bst(bst, (void *)&array[8], array[8].key);
    insert_to_bst(bst, (void *)&array[10], array[10].key);
    insert_to_bst(bst, (void *)&array[12], array[12].key);
    insert_to_bst(bst, (void *)&array[14], array[14].key);

    for(int i = 14; i >= 0; i--){
        for(int j = i; j >= 0; j--){
            assert(((test_t *)is_in_bst(bst,j))->key == j);
        }
        remove_from_bst(bst, i, false);
    }
    dest_bst(bst, false);
    free(array);
}

void test_free_flag(void){

    printf("\tTesting free_flag ...\n");
    
    test_t **array = malloc(15*sizeof(test_t *));
    for(int i = 0; i < 15; i++){
        array[i] = malloc(sizeof(test_t));
        array[i]->key = i;
    }

    bst_t bst = new_bst();
    insert_to_bst(bst, (void *)array[7], array[7]->key);
    insert_to_bst(bst, (void *)array[11], array[11]->key);
    insert_to_bst(bst, (void *)array[3], array[3]->key);
    insert_to_bst(bst, (void *)array[13], array[13]->key);
    insert_to_bst(bst, (void *)array[9], array[9]->key);
    insert_to_bst(bst, (void *)array[1], array[1]->key);
    insert_to_bst(bst, (void *)array[5], array[5]->key);
    insert_to_bst(bst, (void *)array[0], array[0]->key);
    insert_to_bst(bst, (void *)array[2], array[2]->key);
    insert_to_bst(bst, (void *)array[4], array[4]->key);
    insert_to_bst(bst, (void *)array[6], array[6]->key);
    insert_to_bst(bst, (void *)array[8], array[8]->key);
    insert_to_bst(bst, (void *)array[10], array[10]->key);
    insert_to_bst(bst, (void *)array[12], array[12]->key);
    insert_to_bst(bst, (void *)array[14], array[14]->key);

    for(int i = 14; i >= 0; i--){
        for(int j = i; j >= 0; j--){
            assert(((test_t *)is_in_bst(bst,j))->key == j);
        }
        remove_from_bst(bst, i, true);
    }
    dest_bst(bst, false);
    free(array);
}

void test_balance(void){
    
    printf("\tTesting balance ...\n");
    bst_t tree = new_bst();
    for(int i = 15; i > 0; i--){
        insert_to_bst(tree, NULL, i);
    }
    assert(valid_bst(tree));
    balance_tree(tree);
    //assert(valid_bst(tree));
    dest_bst(tree, false);
}

void test_bst_to_array(void){
    printf("\tTesting array conversion...\n");
    bst_t tree = new_bst();
    for(int i = 0; i < 1023; i++) insert_to_bst(tree,NULL,i);
    int * array = bst_to_array(tree);
    for(int i = 0; i < 1023; i++) assert(array[i] == i);
    dest_bst(tree, false);
    free(array);
}
