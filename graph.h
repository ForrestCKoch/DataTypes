#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct _graph_t *graph_t;
typedef int nid_t;

#define DIRECTED 0
#define UNDIRECTED 1

// return a new graph. set dir = DIRECTED for a directed graph
// and dir = UNDIRECTED for an undirected graph
graph_t new_graph(nid_t size, int dir);

void dest_graph(graph_t g);

void add_edge(graph_t g, nid_t a, nid_t b, size_t weight);

void rem_edge(graph_t g, nid_t a, nid_t b);

bool adjacent(graph_t g, nid_t a, nid_t b);

size_t size_edge(graph_t g, nid_t a, nid_t b);

size_t edge_size(graph_t g, nid_t a, nid_t b);

nid_t *neighbors(graph_t g, nid_t a, int *n);    

// not implemented
//void print_graph(graph_t g);

#endif
