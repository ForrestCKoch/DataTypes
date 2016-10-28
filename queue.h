#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct _queue_t *queue_t;

queue_t new_queue(void);

void dest_queue(queue_t q);

void enqueue(queue_t q, void *ptr);

void * dequeue(queue_t q);

size_t size_queue(queue_t q);

#endif

