typedef struct graph graph;

#include "hashtable.h"

struct graph
{
    unsigned int nodes;
    unsigned int max_size;
    list_t *friends;
};

graph *new_graph();
void add_node(graph *x, unsigned int node);
void add_connection(graph *x, unsigned int a, unsigned int b);
void remove_connection(graph *x, unsigned int a, unsigned int b);
void get_distance(graph *x, unsigned int a, unsigned int b);
