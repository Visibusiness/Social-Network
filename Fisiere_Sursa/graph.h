typedef struct graph_t graph_t;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 256
#define HMAX 10

typedef struct node_t node_t;

struct node_t
{
    void *data;
    node_t *prev, *next;
};

typedef struct list_t
{
    node_t *head;
    unsigned int data_size;
    unsigned int size;
} list_t;

node_t *new_node(void *data);
node_t *remove_from_list(list_t *list , void *data);
list_t *new_list();
void add_in_list(list_t *list, node_t* node);
void link(node_t *x, node_t *y);
list_t *ll_create(unsigned int data_size);
void ll_free(list_t **pp_list);

struct graph_t
{
    unsigned int nodes;
    list_t **friends;
};

graph_t *new_graph();
void add_node(graph_t *x, unsigned int node);
void add_connection(graph_t *x, unsigned int a, unsigned int b);
void remove_connection(graph_t *x, unsigned int a, unsigned int b);
void get_distance(graph_t *x, unsigned int a, unsigned int b);
