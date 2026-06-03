#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "graph.h"

Graph* create_big_city_graph() {
    Graph* g = malloc(sizeof(Graph));
    g->num_nodes = 100;
    g->adj_matrix = malloc(g->num_nodes * sizeof(double*));
    g->node_names = malloc(g->num_nodes * sizeof(char*));
    
    srand(42);  // Pour reproductibilite
    
    for (int i = 0; i < g->num_nodes; i++) {
        g->adj_matrix[i] = calloc(g->num_nodes, sizeof(double));
        char name[10]; sprintf(name, "N%d", i);
        g->node_names[i] = strdup(name);
    }
    
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            int node = row * 10 + col;
            
            if (col < 9) g->adj_matrix[node][node+1] = 1.5 + (rand() % 10)/10.0;
            if (row < 9) g->adj_matrix[node][node+10] = 1.8 + (rand() % 15)/10.0;
            
            if (col > 0 && row % 3 == 0) g->adj_matrix[node][node-1] = 2.5 + (rand() % 10)/10.0;
            if (row > 0 && col % 3 == 0) g->adj_matrix[node][node-10] = 2.2 + (rand() % 12)/10.0;
            
            if (row < 9 && col < 9 && (row+col) % 4 == 0) {
                g->adj_matrix[node][node+11] = 2.8;
            }
        }
    }
    
    return g;
}

typedef struct {
    double dist;
    int prev;
} NodeInfo;

double dijkstra(Graph* g, int start, int end, int* path, int* path_len) {
    NodeInfo* info = malloc(g->num_nodes * sizeof(NodeInfo));
    int* visited = calloc(g->num_nodes, sizeof(int));
    
    for (int i = 0; i < g->num_nodes; i++) {
        info[i].dist = INFINITY;
        info[i].prev = -1;
    }
    info[start].dist = 0;
    
    for (int iter = 0; iter < g->num_nodes; iter++) {
        int u = -1;
        double min_dist = INFINITY;
        for (int v = 0; v < g->num_nodes; v++) {
            if (!visited[v] && info[v].dist < min_dist) {
                min_dist = info[v].dist;
                u = v;
            }
        }
        if (u == -1) break;
        visited[u] = 1;
        
        for (int v = 0; v < g->num_nodes; v++) {
            if (g->adj_matrix[u][v] > 0) {
                double new_dist = info[u].dist + g->adj_matrix[u][v];
                if (new_dist < info[v].dist) {
                    info[v].dist = new_dist;
                    info[v].prev = u;
                }
            }
        }
    }
    
    *path_len = 0;
    int current = end;
    while (current != -1) {
        path[(*path_len)++] = current;
        current = info[current].prev;
    }
    for (int i = 0; i < *path_len / 2; i++) {
        int tmp = path[i];
        path[i] = path[*path_len - 1 - i];
        path[*path_len - 1 - i] = tmp;
    }
    
    double result = info[end].dist < INFINITY ? info[end].dist : -1;
    free(info);
    free(visited);
    return result;
}

void free_graph(Graph* g) {
    for (int i = 0; i < g->num_nodes; i++) {
        free(g->adj_matrix[i]);
        free(g->node_names[i]);
    }
    free(g->adj_matrix);
    free(g->node_names);
    free(g);
}
//Test