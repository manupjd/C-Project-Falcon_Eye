#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    int num_nodes;
    double** adj_matrix;
    char** node_names;
} Graph;

Graph* create_big_city_graph();
double dijkstra(Graph* g, int start, int end, int* path, int* path_len);
void free_graph(Graph* g);

#endif
