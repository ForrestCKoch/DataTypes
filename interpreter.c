/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : interpreter.c

* Purpose : interactive program to allow direct use of the graph ADT

* Creation Date : 23-09-2016

* Last Modified : Mon 26 Sep 2016 10:33:46 AM UTC

* Created By : Forrest Koch

_._._._._._._._._._._._._._._._._._._._._.*/
#include <stdio.h>
#include "graph.h"

#define GRAPH_SIZE 1024


int main(void){

    char line[BUFSIZ];

    graph_t g = new_graph(GRAPH_SIZE, UNDIRECTED);

    int valX, valY;
    nid_t nodeX, nodeY;

    while(fgets(line, BUFSIZ, stdin)){
        if(sscanf(line, "+ %d %d", &valX, &valY) == 2){
            nodeX = valX;
            nodeY = valY;
            if(nodeX && nodeY){
                add_edge(g, nodeX, nodeY, 0);
            }
        }else if(sscanf(line, "- %d %d", &valX, &valY) == 2){
            nodeX = valX;
            nodeY = valY; 
            if(nodeX && nodeY){
                rem_edge(g, nodeX, nodeY);
            }
        }else if(sscanf(line, "$ %d", &valX) == 1){
            nodeX = valX;
            if(nodeX){
                int n;
                nid_t *adj = neighbors(g, nodeX, &n);
                for(int i = 0; i < n; i++){
                    if(i%20) printf(", ");
                    else if(i) printf("\n");
                    printf("%d", adj[i]);
                } 
                printf("\n");
            }
        }else if(sscanf(line, "? %d %d", &valX, &valY) == 2){
            nodeX = valX;
            nodeY = valY;
            if(nodeX && nodeY){
                if(adjacent(g, nodeX, nodeY)){
                    printf("adjacent\n");
                }else{
                    printf("not adjacent\n");
                }
            }
        }
    }

    dest_graph(g);

    return 0;
}
