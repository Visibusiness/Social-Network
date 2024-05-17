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
    if(x)
        x->next = y;
    else
        printf("linkinginginging aiurea\n");
    if(y)
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

graph_t *new_graph(unsigned int nodes)
{
    graph_t *x = malloc(sizeof(graph_t));
    x->nodes = nodes;
	x->friends = malloc(nodes * sizeof(list_t *));
	for(unsigned int i=0; i<nodes; i++)
	    x->friends[i] = new_list();
    return x;
}

void free_graph(graph_t *x)
{
    for(unsigned int i=0; i<x->nodes; i++)
        ll_free(&(x->friends[i]));
    free(x->friends);
}

void add_connection(graph_t *x, unsigned int a, unsigned int b)
{
    unsigned int *u = malloc(sizeof(unsigned int)); 
    unsigned int *v = malloc(sizeof(unsigned int));
    *u = a;
    *v = b;
    add_in_list(x->friends[a], new_node(v));
    add_in_list(x->friends[b], new_node(u));
}

void remove_connection(graph_t *x, unsigned int a, unsigned int b)
{
    remove_node(x->friends[a], b);
    remove_node(x->friends[b], a);
}

void print_vecini(graph_t *x, unsigned int cr)
{
    return;
    printf("Vecini lui %d sunt\n", cr);
    node_t *node = x->friends[cr]->head;
    while(node) {
        unsigned int vecin = *((int *)node->data);
        printf("%d este vecin al lui %d\n", vecin, cr);
        node = node->next;
        // node = NULL;
    }
    printf("\n");
}

int get_distance(graph_t *x, unsigned int a, unsigned int b)
{
    unsigned int *used = calloc(x->nodes, sizeof(unsigned int));
    unsigned int *in_use = calloc(x->nodes, sizeof(unsigned int));
    unsigned int first=0, last=0;
    int must_return = 0;
    in_use[0]=a;
    used[a]=1;

    while(first <= last) {
        unsigned int cr=in_use[first];
        // printf("sunt in %d\n", cr);
        node_t *node = x->friends[cr]->head;
        while(node) {
            unsigned int vecin = *((unsigned int *)node->data);
            // printf("%d este vecin al lui %d\n", vecin, cr);
            if(vecin == b) {
                must_return = used[cr] + 1;
                node = NULL;
            } else if(used[vecin] == 0) {
                used[vecin] = used[cr] + 1;
                in_use[++last] = vecin;
            }
            if(node)
                node = node->next;
        }
        first++;
    }
    free(in_use);
    free(used);
    return must_return;
}
