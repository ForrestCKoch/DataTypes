/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : bst.c

* Purpose : prodvides a binary search tree ADT

* Creation Date : 23-09-2016

* Last Modified : Fri 28 Oct 2016 08:09:25 PM AEDT

* Created By : Forrest Koch 

_._._._._._._._._._._._._._._._._._._._._.*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "bst.h"

// a binary search tree data type for use with void *'s
typedef struct _bst_node_t * bst_node_t;
struct _bst_node_t{
    int key;
    void *ptr;
    bst_node_t left;
    bst_node_t right;
};
struct _bst_t{
    bst_node_t head;
    size_t size;
};

// saftey checks
static bool valid_bst_node(bst_node_t node);

// recursive funcs to complete corresponding ADT funcs
static bst_node_t new_bst_node(void *ptr, int key);
static void dest_bst_node(bst_node_t node, bool free_flag);
static void insert_bst_node(bst_node_t node, void *ptr, int key);
static void remove_bst_node(bst_node_t node, int key, bst_node_t prev, bool free_flag);
static void *find_key(bst_node_t node, int key);

// helper/balancing functions
static bst_node_t rotate_right(bst_node_t node);
static bst_node_t rotate_left(bst_node_t node);
static bst_node_t convert_right_vine(bst_node_t node);
static bst_node_t balance_vine(bst_node_t node);



// returns an empty bst_t
bst_t new_bst(){
    bst_t ret = malloc(sizeof(struct _bst_t));
    ret->head = NULL;
    ret->size = 0;
    return ret;
}
// free's all memory associated with the bst_t
void dest_bst(bst_t bst, bool free_flag){
    valid_bst(bst);
    dest_bst_node(bst->head, free_flag);
    free(bst);
    return;
}
// insert a key to the bst_t
void insert_to_bst(bst_t bst, void *ptr, int key){
    if(!is_in_bst(bst, key)){
        if(bst->head) insert_bst_node(bst->head, ptr, key);
        else bst->head = new_bst_node(ptr, key);
        bst->size++;
    }
    // do we want to automatically take care of balancing?
    size_t size = bst->size + 1;
    bool flag = true;
    while(size > 1 && flag){
        if(size % 2) flag = false;
        size /= 2;
    }
    if(flag) balance_tree(bst);
    return;
}
// remove a key from the bst_t
void remove_from_bst(bst_t bst, int key, bool free_flag){
    if(is_in_bst(bst, key)){
        if(bst->head->left || bst->head->right) remove_bst_node(bst->head, key, NULL, free_flag);
        else{
            //it is the last node
            remove_bst_node(bst->head, key, NULL, free_flag);
            bst->head = NULL;
        }
        bst->size--;
    }
    return;
}
// returns the void * associated with a key if it exists, else returns NULL
void *is_in_bst(bst_t bst, int key){
    return find_key(bst->head, key);
}

size_t size_of_bst(bst_t bst){
    return bst->size;
}

// balance the bst
void balance_tree(bst_t bst){
    bst->head = convert_right_vine(bst->head);
    bst->head = balance_vine(bst->head);
}

bool valid_bst(bst_t bst){
    if(!bst) return false;
    if(!bst->head) return true;
    return valid_bst_node(bst->head);
}

static bool valid_bst_node(bst_node_t node){
    if(!node) return true;
    if(node->right && node->right->key <= node->key) return false;
    if(node->left && node->left->key >= node->key) return false;
    return valid_bst_node(node->right) && valid_bst_node(node->left);
}

static bst_node_t new_bst_node(void *ptr, int key){
    bst_node_t ret = malloc(sizeof(struct _bst_node_t));
    ret->ptr = ptr;
    ret->key = key;
    ret->right = NULL;
    ret->left = NULL;
    return ret;
}
static void dest_bst_node(bst_node_t node, bool free_flag){
    if(node){
        dest_bst_node(node->left, free_flag);
        dest_bst_node(node->right, free_flag);
        if(free_flag) free(node->ptr);
        free(node);
    }
    return;
}
static void insert_bst_node(bst_node_t node, void *ptr, int key){
    if(key > node->key){
        if(node->right) insert_bst_node(node->right, ptr, key);
        else node->right = new_bst_node(ptr, key);
    }else if(key < node->key){
        if(node->left) insert_bst_node(node->left, ptr, key);
        else node->left = new_bst_node(ptr, key);
    }
    return;
}

static void remove_bst_node(bst_node_t node, int key, bst_node_t prev, bool free_flag){
    // we have guarenteed that the key will be in tree
    if(key > node->key) remove_bst_node(node->right, key, node, free_flag);
    else if(key < node->key) remove_bst_node(node->left, key, node, free_flag);
    else{// this is our node
        // if this node is not a leaf
        if(node->right){
            // find the value just greater and replace node w/ it
            bst_node_t curr = node->right;
            bst_node_t p = NULL;
            while(curr->left){
                p = curr;
                curr = curr->left;
            }
            //now pop out curr
            if(p) p->left = curr->right;
            else node->right = curr->right;
            //replace node data w/ curr's
            //swap ptrs in case of free_flag
            void *tmp = node->ptr;
            node->key = curr->key;
            node->ptr = curr->ptr;
            curr->ptr = tmp;
            //dipose of curr
            curr->right = NULL;
            curr->left = NULL;
            dest_bst_node(curr, free_flag);
        }else if(node->left){
            // there is no greater value, replace with lower branch
            bst_node_t toDel = node->left;
            void *tmp = node->ptr;
            node->key = node->left->key;
            node->ptr = node->left->ptr;
            node->right = node->left->right;
            node->left = node->left->left;
            toDel->right = NULL;
            toDel->left = NULL;
            toDel->ptr = tmp;
            dest_bst_node(toDel, free_flag);
        }else{//leaf node, adjust prev
            if(prev){
                if(node == prev->right) prev->right = NULL;
                else prev->left = NULL;
            }
            dest_bst_node(node, free_flag);
        }
    }
    return;
}

static void *find_key(bst_node_t node, int key){
    if(!node) return NULL;
    if(key > node->key) return find_key(node->right, key);
    else if(key < node->key) return find_key(node->left, key);
    else return node->ptr;
}

static bst_node_t rotate_right(bst_node_t node){

    // no need to do anything if there is no left
    if(!node->left) return node;

    bst_node_t new_left = node->left->right;
    bst_node_t ret = node->left;

    ret->right = node;
    node->left = new_left;

    return ret;
}
static bst_node_t rotate_left(bst_node_t node){
    // no need to do anything if there is no left
    if(!node->right) return node;

    bst_node_t new_right = node->right->left;
    bst_node_t ret = node->right;

    ret->left = node;
    node->right = new_right;

    return ret;

}

static bst_node_t convert_right_vine(bst_node_t node){

    if(!node) return NULL;
    while(node->left) node = rotate_right(node);
    node->right = convert_right_vine(node->right);
    return node;

}
static bst_node_t balance_vine(bst_node_t node){
    // assumes that the tree being passed in is a linked list

    // get count
    int node_count = 0;
    bst_node_t head = node;
    bst_node_t curr = node;
    while(curr){
        node_count++;
        curr = curr->right;
    }
    while(node_count > 1){
        head = rotate_left(head);
        curr = head;
        if(!curr){
            fprintf(stderr, "%s: you fucked up\n", __FUNCTION__);
            exit(1);
        }
        while(curr->right && curr->right->right && curr->right->right->right){
            curr->right = rotate_left(curr->right);
            curr = curr->right;
        }
        node_count /= 2;
    }
    return head;
}

// test the rotate functions w/o revealing too much about ADT
void test_rotate(void){
    bst_t tree = new_bst();
    for(int i = 0; i < 8; i++) insert_to_bst(tree, NULL, i);
    if(!valid_bst(tree)){
        fprintf(stderr, "Error A\n");
        exit(1);
    }
    tree->head = rotate_left(tree->head);
    if(!valid_bst(tree)){
        fprintf(stderr, "Error B\n");
        exit(1);
    }
    tree->head->right = rotate_left(tree->head->right);
    if(!valid_bst(tree)){
        fprintf(stderr, "Error C\n");
        exit(1);
    }
    tree->head->right = rotate_right(tree->head->right);
    if(!valid_bst(tree)){
        fprintf(stderr, "Error D\n");
        exit(1);
    }
    tree->head = rotate_right(tree->head);
    if(!valid_bst(tree)){
        fprintf(stderr, "Error E\n");
        exit(1);
    }
    bst_node_t node = tree->head;
    for(int i = 0; i < 8; i++){
        if(node->key != i){
            fprintf(stderr, "Error B\n");
            exit(1);
        }
        node = node->right;
    }
    dest_bst(tree, false);
}

int get_min_bst(bst_t bst){
    // in case the tree is empty, just return 0.
    // not our problem :P
    if(!size_of_bst(bst)) return 0;
    bst_node_t curr = bst->head;
    while(curr->left) curr = curr->left;
    return curr->key;
}

int get_max_bst(bst_t bst){
    // in case the tree is empty, just return 0.
    // not our problem :P
    if(!size_of_bst(bst)) return 0;
    bst_node_t curr = bst->head;
    while(curr->right) curr = curr->right;
    return curr->key;
}

int get_head_bst(bst_t bst){
    if(!size_of_bst(bst)) return 0;
    return bst->head->key;
}

int *bst_to_array(bst_t bst){

    int *array = malloc(sizeof(int) * size_of_bst(bst));
    int index = 0;
    bst_node_t curr;
    // major hack warning ahead :P

    // convert to linked list
    bst->head = convert_right_vine(bst->head);
    curr = bst->head;
    while(curr){
        array[index++] = curr->key;
        curr = curr->right;
    }
    if(index != size_of_bst(bst)){
        fprintf(stderr, "Sizes don't match!\n");
        exit(1);
    }
    // don't forget to return to working form
    bst->head = balance_vine(bst->head);
    return array;
}

