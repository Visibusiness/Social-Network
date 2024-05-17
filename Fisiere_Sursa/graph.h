#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t node_t;
typedef struct list_t list_t;
typedef struct graph_t graph_t;

struct node_t
{
    void *data;
    node_t *prev, *next;
};

struct list_t
{
    node_t *head;
    unsigned int size;
};

struct graph_t
{
    unsigned int nodes;
    list_t **friends;
};

node_t *new_node(void *data);
node_t *remove_node(list_t *x, int n);
node_t *remove_from_list(list_t *list , void *data);
list_t *new_list();
void add_in_list(list_t *list, node_t* node);
void link(node_t *x, node_t *y);
list_t *ll_create(unsigned int data_size);
void ll_free(list_t **pp_list);

graph_t *new_graph();
void add_connection(graph_t *x, unsigned int a, unsigned int b);
void remove_connection(graph_t *x, unsigned int a, unsigned int b);
void get_distance(graph_t *x, unsigned int a, unsigned int b);
