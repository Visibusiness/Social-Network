#include "graph.h"

node_t *new_node(void *data)
{
    node_t *x = malloc(sizeof(node_t));
    x->data = data;
    x->next = NULL;
    x->prev = NULL;
    return x;
}

void free_node(node_t **x)
{
    free((*x)->data);
    free(*x);
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

node_t *remove_from_list(list_t *list, unsigned int searched)
{
    node_t *cr = list->head;
    while(cr) {
        if(*(unsigned int *)cr->data == searched) {
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
    node_t *aux = remove_from_list(x->friends[a], b);
    free_node(&aux);
    aux = remove_from_list(x->friends[b], a);
    free_node(&aux);
}


int get_distance(graph_t *x, unsigned int a, unsigned int b)
{
    if(a == b)
        return 1;

    unsigned int *distance = calloc(x->nodes, sizeof(unsigned int));
    unsigned int *in_use = calloc(x->nodes, sizeof(unsigned int));
    unsigned int first=0, last=0;
    int must_return = 0;
    in_use[0]=a;
    distance[a]=1;

    while(first <= last) {
        unsigned int cr=in_use[first];
        node_t *node = x->friends[cr]->head;
        while(node) {
            unsigned int neighbour = *(unsigned int *)node->data;
            if(neighbour == b) {
                must_return = distance[cr] + 1;
                first = last;
                node = NULL;
            } else if(distance[neighbour] == 0) {
                distance[neighbour] = distance[cr] + 1;
                in_use[++last] = neighbour;
            }
            if(node)
                node = node->next;
        }
        first++;
    }
    free(in_use);
    free(distance);
    return must_return;
}

void maybe_good_suggestions(graph_t *x, unsigned int a, unsigned int *good_suggestions)
{
    node_t *node = x->friends[a]->head;
    while(node) {
        unsigned int neighbour = *(unsigned int *)node->data;
        good_suggestions[neighbour] = 1;
        node = node->next;
    }
}

unsigned int *suggestions(graph_t *x, unsigned int a)
{
    unsigned int *good_suggestions = calloc(x->nodes, sizeof(unsigned int));
    node_t *node = x->friends[a]->head;
    while(node) {
        unsigned int neighbour = *(unsigned int *)node->data;
        maybe_good_suggestions(x, neighbour, good_suggestions);
        node = node->next;
    }
    node = x->friends[a]->head;
    while(node) {
        unsigned int neighbour = *(unsigned int *)node->data;
        good_suggestions[neighbour] = 0;
        node = node->next;
    }
    good_suggestions[a] = 0;
    return good_suggestions;
}

unsigned int *common_friends(graph_t *x, unsigned int a, unsigned int b)
{
    unsigned int *friends = calloc(x->nodes, sizeof(unsigned int));
    node_t *node = x->friends[a]->head;
    while(node) {
        unsigned int neighbour = *(unsigned int *)node->data;
        friends[neighbour] = 1;
        node = node->next;
    }
    node = x->friends[b]->head;
    while(node) {
        unsigned int neighbour = *(unsigned int *)node->data;
        friends[neighbour]++;
        node = node->next;
    }
    friends[a] = 0;
    friends[b] = 0;
    return friends;
}

unsigned int most_popular_friend(graph_t *x, unsigned int a)
{
    unsigned int friend = 0, count = 0;
    node_t *node = x->friends[a]->head;
    while(node) {
        unsigned int neighbour = *(unsigned int *)node->data;
        unsigned int current_count = x->friends[neighbour]->size;
        if(current_count > count) {
            count = current_count;
            friend = neighbour;
        }
        node = node->next;
    }
    return friend;
}
