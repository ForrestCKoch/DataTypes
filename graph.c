/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : graph.c

* Purpose : Graph ADT for educational purposes

* Creation Date : 23-09-2016

* Last Modified : Mon 17 Oct 2016 10:38:41 PM AEDT

* Created By :  Forrest Koch

_._._._._._._._._._._._._._._._._._._._._.*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph.h"
#include "bst.h"

typedef unsigned char bits8;

struct _graph_t{
    // total # of nodes
    nid_t size;
    // bit array used for fast access
    bits8 **edge_map;
    // remenant dependancy from when we used node *'s
    nid_t *list;
    // the number of "regions" in the edge_map
    size_t map_regions;
    // array of bst's for edge weight lookup
    bst_t *edge_trees;
    // is the graph directed or undirected?
    int dir;
};


static bool valid_graph(graph_t g){
    #ifdef DEBUG
    if(!g) return false;

    if(g->map_regions){
        if(!g->edge_map || !g->edge_trees) return false;
        for(nid_t i = 0; i < g->size; i++){
            if(!g->edge_map[i] || !g->edge_trees[i]) return false;
        }
    }else{
        if(g->edge_map || g->edge_trees) return false;
    }

    if(g->list){
        for(nid_t i = 0; i < g->size; i++){
            if(g->list[i] != i) return false;
        }
    }else{
        return false;
    }
    #endif
    return true;
}

graph_t new_graph(nid_t size, int dir){

    graph_t g = (graph_t)malloc(sizeof(struct _graph_t));
    g->size = size;
    g->dir = dir;

    g->edge_map = NULL;
    g->list = NULL;

    g->list = (nid_t *)malloc(size * sizeof(nid_t));
    for(nid_t i = 0; i < size; i++) g->list[i] = i;

    // how many 8 bit regions on the edge map?
    g->map_regions = size / 8;
    if(g->map_regions % 8){
        g->map_regions++;
    }
    // initialize edge_trees and edge_map
    // make size x regions array for edge_map
    g->edge_map = (bits8 **)calloc(size, sizeof(bits8 *));
    g->edge_trees = (bst_t *)malloc(size * sizeof(bst_t));
    for(nid_t i = 0; i < size; i++){
        g->edge_map[i] = (bits8 *)calloc(g->map_regions, sizeof(bits8 *));
        g->edge_trees[i] = new_bst();
    }


    return g;
}

void dest_graph(graph_t g){

    if(!valid_graph(g)){
        fprintf(stderr, "Error in %s: invalid graph\n", __FUNCTION__); 
        return;
    }

    for(nid_t i = 0; i < g->size; i++){
        free(g->edge_map[i]);
        g->edge_map[i] = NULL;
        dest_bst(g->edge_trees[i],true);
        g->edge_trees[i] = NULL;
    }
    
    free(g->edge_map);
    g->edge_map = NULL;
    
    free(g->edge_trees);
    g->edge_trees = NULL;
    
    free(g->list);
    g->list = NULL;

    free(g);
    g = NULL;

    return;
}

/*
nid_t get_node(graph_t g, nid_t id){
    if(!valid_graph(g)){
        fprintf(stderr, "Error in %s: invalid graph\n", __FUNCTION__); 
        return -1;
    }
    if(id > g->size){
        fprintf(stderr, "Error in %s: accessing invalid node\n", __FUNCTION__);
        return -1;
    }
    return g->list[id];
}

int get_id(nid_t n){
    if(!n){
        fprintf(stderr, "Error in %s: accessing invalid node\n", __FUNCTION__);
        return -1;
    }
    return n;
}
*/

void add_edge(graph_t g, nid_t a, nid_t b, size_t weight){
    
    if(!valid_graph(g)){
        fprintf(stderr, "Error in %s: invalid graph\n", __FUNCTION__); 
        return;
    }
    if(a < 0 || a > g->size){
        fprintf(stderr, "Error in %s: accessing invalid node\n", __FUNCTION__);
        return;
    }
    if(b < 0 || b> g->size){
        fprintf(stderr, "Error in %s: accessing invalid node\n", __FUNCTION__);
        return;
    }

    // add edge to the edge_map for quick lookup
    int regionB = b/ 8;
    int bitB = b% 8;
    bits8 maskB = 1;
    maskB = maskB << bitB;

    g->edge_map[a][regionB] = g->edge_map[a][regionB] | maskB;
    // add edge to edge_trees
    // how are we going to handle having to free the void *?s
    int *edge_weight_a = malloc(sizeof(int));
    *edge_weight_a = weight;
    insert_to_bst(g->edge_trees[a], edge_weight_a, b);

    if(g->dir == UNDIRECTED){
        int regionA = a/ 8;
        int bitA = a% 8;
        bits8 maskA = 1;
        maskA = maskA << bitA;

        g->edge_map[b][regionA] = g->edge_map[b][regionA] | maskA;
        int *edge_weight_b = malloc(sizeof(int));
        *edge_weight_b = weight;
        insert_to_bst(g->edge_trees[b], edge_weight_b, a);
    }

    return;

}

void rem_edge(graph_t g, nid_t a, nid_t b){
    if(!valid_graph(g)){
        fprintf(stderr, "Error in %s: invalid graph\n", __FUNCTION__); 
        return;
    }
    if(a < 0 || a> g->size){
        fprintf(stderr, "Error in %s: accessing invalid node\n", __FUNCTION__);
        return;
    }
    if(b < 0 || b> g->size){
        fprintf(stderr, "Error in %s: accessing invalid node\n", __FUNCTION__);
        return;
    }

    int regionA = a/ 8;
    int bitA = a% 8;
    bits8 maskA = 1;
    maskA = maskA << bitA;

    int regionB = b/ 8;
    int bitB = b% 8;
    bits8 maskB = 1;
    maskB = maskB << bitB;

    if(adjacent(g, a, b)){
        g->edge_map[a][regionB] = g->edge_map[a][regionB] ^ maskB;
        remove_from_bst(g->edge_trees[a], b, true);
        if(g->dir == UNDIRECTED){
            g->edge_map[b][regionA] = g->edge_map[b][regionA] ^ maskA;
            remove_from_bst(g->edge_trees[b], a, true);
        }
    }

    return;

}

bool adjacent(graph_t g, nid_t a, nid_t b){
    if(!valid_graph(g)){
        fprintf(stderr, "Error in %s: invalid graph\n", __FUNCTION__); 
        return false;
    }
    if(a < 0 || a > g->size){
        fprintf(stderr, "Error in %s: accessing invalid node\n", __FUNCTION__);
        return false;
    }
    if(b < 0 || b > g->size){
        fprintf(stderr, "Error in %s: accessing invalid node\n", __FUNCTION__);
        return false;
    }

    int regionA = a / 8;
    int bitA = a % 8;
    bits8 maskA = 1;
    maskA = maskA << bitA;

    int regionB = b / 8;
    int bitB = b % 8;
    bits8 maskB = 1;
    maskB = maskB << bitB;

    bits8 tmpA = g->edge_map[a][regionB] | maskB;
    bits8 tmpB = g->edge_map[b][regionA] | maskA;

    if(tmpA == g->edge_map[a][regionB]) return true;
    if(g->dir == UNDIRECTED && tmpB == g->edge_map[b][regionA]) return true;
    return false;

}

size_t edge_size(graph_t g, nid_t a, nid_t b){
    if(!adjacent(g, a, b)) return 0;
    else return *(int *)(is_in_bst(g->edge_trees[a],b));
}

nid_t *neighbors(graph_t g, nid_t a, int *n){
    if(!valid_graph(g)){
        fprintf(stderr, "Error in %s: invalid graph\n", __FUNCTION__); 
        return NULL;
    }
    if(a < 0 || a > g->size){
        fprintf(stderr, "Error in %s: accessing invalid node\n", __FUNCTION__);
        return NULL;
    }
    int count = 0;

    for(nid_t i = 0; i < g->size; i++){
        if(adjacent(g, a, g->list[i])){
            count++;
        }
    }
    
    nid_t *list;
    if(count){
        list = (nid_t *)malloc(count * sizeof(nid_t));
    }else{
        list = NULL;
    }
    *n = count;

    count = 0;
    for(nid_t i = 0; i < g->size; i++){
        if(adjacent(g, a, g->list[i])){
            list[count++] = g->list[i];
        }
    }
    

    return list;
}    

void print_graph(graph_t g){
    if(!valid_graph(g)){
        fprintf(stderr, "Error in %s: invalid graph\n", __FUNCTION__); 
        return;
    }

}

