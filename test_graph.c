#include <stdio.h>
#include <assert.h>
#include "graph.h"

void test_basic_functionality(void);
void test_edge_weight(void);

int main(void){

    printf("\nTesting graph ADT...\n");
    test_basic_functionality();
    test_edge_weight();
    printf("\tall tests passed...\n");

    return 0;
}

void test_basic_functionality(void){

    graph_t g = new_graph(16, UNDIRECTED);
    assert(g);

    nid_t *list = malloc(16 * sizeof(nid_t));
    for(int i = 0; i < 16; i++) list[i] = i;

    /*printf("\tTesting node retrieval...\n");
    for(int i = 0; i < 16; i++){
        list[i] = get_node(g, i);
        assert(list[i]);
    }
    */

    printf("\tTesting edge creation...\n");
    for(int i = 0; i < 16; i++){
        for(int j = i + 1; j < 16; j++){
            add_edge(g, list[i], list[j],0);
            assert(adjacent(g, list[i], list[j]));
        }
    }
    
    printf("\tTesting node adjacency...\n");
    for(int i = 0; i < 16; i++){
        for(int j = i + 1; j < 16; j++){
            assert(adjacent(g, list[i], list[j]));
        }
    }

    printf("\tTesting node removal...\n");
    for(int i = 0; i < 16; i++){
        for(int j = i + 1; j < 16; j++){
            rem_edge(g, list[i], list[j]);
            assert(!adjacent(g, list[i], list[j]));
        }
    }

    printf("\tTesting neighbors ...\n");
    int n;
    for(int i = 1; i < 16; i+=3){
        add_edge(g,list[0],list[i],0);
    }
    int j = 1;
    nid_t *l = neighbors(g,list[0],&n);
    for(int i = 0; i < n; i++){
        assert(j == (l[i]));
        j+=3;
    }
    free(l);
    free(list);

    dest_graph(g);
}

void test_edge_weight(void){

    printf("\tTesting edge_weights ...\n");

    graph_t g = new_graph(1024, UNDIRECTED);

    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 500; j++){
            add_edge(g,i,j,i+j);
        }
    }
    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 500; j++){
            assert(edge_size(g,i,j) == i + j);
        }
    }
    dest_graph(g);
}

