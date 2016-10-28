/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : stress_graph.c

* Purpose :

* Creation Date : 30-09-2016

* Last Modified : Mon 17 Oct 2016 10:45:13 PM AEDT

* Created By : Forrest Koch 

_._._._._._._._._._._._._._._._._._._._._.*/
#include "graph.h"

#define SIZE 1023

int main(void){
    
    graph_t g = new_graph(SIZE, UNDIRECTED);

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            add_edge(g,i,j,i+j);
        }
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = j; k < SIZE; k++){
                edge_size(g,i,k);
            }
        }
    }

    dest_graph(g);
    return 0;
}
        
