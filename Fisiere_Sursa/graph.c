#include "graph.h"

node_t *new_node(void *data)
{
    node_t *x = malloc(sizeof(node_t));
    x->data = data;
    x->next = NULL;
    x->prev = NULL;
    return x;
}

void link(node_t *x, node_t *y)
{
    if(y)
        x->next = y;
    if(x)
        y->prev = x;    
}

list_t *new_list(unsigned int data_size)
{
    list_t *x = malloc(sizeof(list_t));
    x->head = NULL;
    x->size = 0;
    x->data_size = data_size;
    return x;
}

void add_in_list(list_t *list, node_t* node)
{
    link(node, list->head);
    list->head = node;
    list->size++;
}

node_t *remove_from_list(list_t *list , void *data, int (*compare_function)(void *, void *))
{
    node_t *cr = list->head;
    while(cr){
        if(!compare_function(cr->data, data)) {
            if(cr != list->head)
                link(cr->prev, cr->next);
            else {
                list->head = cr->next;
                list->head->prev = NULL;
            }
            list->size--;
            return cr;
        }
        cr = cr->next;
    }
    return NULL;
}

void ll_free(list_t **pp_list, void (*free_function)(void *))
{
    if (!pp_list || !*pp_list)
        return;
    node_t *cr = (*pp_list)->head, *next;
    while(cr) {
        next = cr->next;
        free_function(cr->data);
        free(cr);
        cr = next;
    }
    free(*pp_list);
    *pp_list = NULL;
}

graph_t *new_graph() 
{
    graph_t *x = malloc(sizeof(graph_t));
    x->nodes = 0;
    x->friends = NULL;
    return x;
}

void add_node(graph_t *x, unsigned int node)
{
    if(x->max_size == 0)
        x->max_size = 1;
    if(x->nodes + 1 > x->max_size)
        x->max_size <<= 1;
    x->friends[node] = new_list(sizeof(int));
}

void add_connection(graph_t *x, unsigned int a, unsigned int b)
{
    int *u = malloc(sizeof(int)); 
    int *v = malloc(sizeof(int));
    *u = a;
    *v = b;
    add_node(x->friends[a], new_node(u));
    add_node(x->friends[b], new_node(v));
}

void remove_connection(graph_t *x, unsigned int a, unsigned int b)
{

    remove_node(x->friends[a], &b);
    remove_node(x->friends[b], &a);

}

void get_distance(graph_t *x, unsigned int a, unsigned int b);
