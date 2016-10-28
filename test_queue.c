/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : test_queue.c

* Purpose :

* Creation Date : 07-10-2016

* Last Modified : Fri 07 Oct 2016 11:02:10 PM UTC

* Created By : Forrest Koch 

_._._._._._._._._._._._._._._._._._._._._.*/
#include <stdio.h>
#include <assert.h>
#include "queue.h"

void test_queue(void);

int main(void){
    test_queue();
    return 0;
}

void test_queue(void){
    printf("Testing queue...\n");
    queue_t q = new_queue();
    int *n = malloc(100 * sizeof(int));
    for(int i = 0; i < 100; i++) n[i] = i;
    for(int i = 0; i < 100; i++){
        assert(size_queue(q) == i);
        enqueue(q,&n[i]);
        assert(size_queue(q) == i+1);
    }
    for(int i = 0; i < 100; i++){
        assert(size_queue(q) == 100 - i);
        assert(*(int *)dequeue(q) == i);
        assert(size_queue(q) == 99 - i);
    }
    dest_queue(q);
    printf("\tpassed...\n");
}
