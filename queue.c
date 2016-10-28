/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : queue.c

* Purpose :

* Creation Date : 03-10-2016

* Last Modified : Fri 07 Oct 2016 11:02:19 PM UTC

* Created By : Forrest Koch 

_._._._._._._._._._._._._._._._._._._._._.*/
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

typedef struct _queue_node_t * queue_node_t;

struct _queue_t{
    queue_node_t head;
    queue_node_t tail;
    size_t size;
};

struct _queue_node_t{
    queue_node_t next;
    queue_node_t prev;
    void *ptr;
};

static queue_node_t new_queue_node(void *ptr);
static void dest_queue_node(queue_node_t node);
static bool valid_queue(queue_t q);

queue_t new_queue(void){
    queue_t ret = malloc(sizeof(struct _queue_node_t));
    ret->head = NULL;
    ret->tail = NULL;
    ret->size = 0;
    return ret;
}

void dest_queue(queue_t q){
    if(!valid_queue(q)){
        fprintf(stderr, "%s: invalid queue provided\n", __FUNCTION__);
        exit(1);
    }
    queue_node_t prev = q->head;
    queue_node_t curr = q->head;
    while(curr){
        curr = curr->next;
        dest_queue_node(prev);
        prev = curr;
    }
    if(prev) dest_queue_node(prev);
    free(q);
    return;
}

void enqueue(queue_t q, void *ptr){
    if(!valid_queue(q)){
        fprintf(stderr, "%s: invalid queue provided\n", __FUNCTION__);
        exit(1);
    }
    queue_node_t new = new_queue_node(ptr);
    if(q->head){
        q->head->prev = new;
        new->next = q->head;
        q->head = new;
    }else{
        q->head = new;
        q->tail = new;
    }
    q->size++;
    return;
}

void * dequeue(queue_t q){
    if(!valid_queue(q)){
        fprintf(stderr, "%s: invalid queue provided\n", __FUNCTION__);
        exit(1);
    }
    void *ret;
    if(q->size){
        queue_node_t node = q->tail;
        q->tail = node->prev;
        ret = node->ptr;
        dest_queue_node(node);
        q->size--;
        if(!q->size) q->head = q->tail;
    }else ret = NULL;
    return ret;
}

size_t size_queue(queue_t q){
    if(!valid_queue(q)){
        fprintf(stderr, "%s: invalid queue provided\n", __FUNCTION__);
        exit(1);
    }
    return q->size;
}

static queue_node_t new_queue_node(void *ptr){
    queue_node_t ret = malloc(sizeof(struct _queue_node_t));
    ret->next = NULL;
    ret->prev = NULL;
    ret->ptr = ptr;
    return ret;
}

static void dest_queue_node(queue_node_t node){
    node->next = NULL;
    node->prev = NULL;
    node->ptr = NULL;
    free(node);
}

static bool valid_queue(queue_t q){
    if(!q) return false;
    if(!q->head && q->tail) return false;
    if(!q->tail && q->head) return false;
    if((!q->head || !q->tail) && q->size) return false;
    if(!q->size && (q->head || q->tail)) return false;
    return true;
}
