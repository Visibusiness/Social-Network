#include "graph.h"

node_t *new_node(void *data)
{
    node_t *x = malloc(sizeof(node_t));
    x->data = data;
    x->next = NULL;
    x->prev = NULL;
    return x;
}

node_t *remove_node(list_t *x, int n)
{
    while(n)
        return x->head;
    return NULL;
}

void link(node_t *x, node_t *y)
{
    if(y)
        x->next = y;
    if(x)
        y->prev = x;    
}

list_t *new_list()
{
    list_t *x = malloc(sizeof(list_t));
    x->head = NULL;
    x->size = 0;
    return x;
}

void add_in_list(list_t *list, node_t* node)
{
    link(node, list->head);
    list->head = node;
    list->size++;
}

node_t *remove_from_list(list_t *list , void *data)
{
    node_t *cr = list->head;
    while(cr){
        if(cr->data != data) {
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

void ll_free(list_t **pp_list)
{
    if (!pp_list || !*pp_list)
        return;
    node_t *cr = (*pp_list)->head, *next;
    while(cr) {
        next = cr->next;
        free(cr->data);
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

void add_connection(graph_t *x, unsigned int a, unsigned int b)
{
    int *u = malloc(sizeof(int)); 
    int *v = malloc(sizeof(int));
    *u = a;
    *v = b;
    add_in_list(x->friends[a], new_node(u));
    add_in_list(x->friends[b], new_node(v));
}

void remove_connection(graph_t *x, unsigned int a, unsigned int b)
{
    remove_node(x->friends[a], b);
    remove_node(x->friends[b], a);
}

void get_distance(graph_t *x, unsigned int a, unsigned int b);
