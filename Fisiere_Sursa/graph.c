#include "graph.h"

graph *new_graph() 
{
    graph *x = malloc(sizeof(graph));
    x->max_size = 0;
    x->nodes = 0;
    x->friends = NULL
    return x;
}

void add_node(graph *x, unsigned int node)
{
    if(x->max_size == 0)
        x->max_size = 1;
    if(x->nodes + 1 > x->max_size)
        x->max_size <<= 1;
    x->friends[node] = new_list();
}

void add_connection(graph *x, unsigned int a, unsigned int b)
{
    add_node(x->friends[a], new_node(&b, sizeof(int)));
    add_node(x->friends[b], new_node(&a, sizeof(int)));
}

void remove_connection(graph *x, unsigned int a, unsigned int b)
{

    remove_node(x->friends[a], &b);
    remove_node(x->friends[b], &a);

}

void get_distance(graph *x, unsigned int a, unsigned int b);
