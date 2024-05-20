#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t node_t;
typedef struct list_t list_t;
typedef struct graph_t graph_t;

typedef struct post_info post_info;
typedef struct tree_t tree_t;
typedef struct all_posts all_posts;

struct node_t {
    void *data;
    node_t *prev, *next;
};

struct list_t {
    node_t *head;
    unsigned int size;
};

struct graph_t {
    unsigned int nodes;
    list_t **friends;
};

void free_node(node_t **x);
node_t *new_node(void *data);
node_t *remove_from_list(list_t *list, unsigned int searched);
list_t *new_list();
void add_in_list(list_t *list, node_t* node);
void link(node_t *x, node_t *y);
list_t *ll_create(unsigned int data_size);
void ll_free(list_t **pp_list);

graph_t *new_graph();
void free_graph(graph_t *x);
void add_connection(graph_t *x, unsigned int a, unsigned int b);
void remove_connection(graph_t *x, unsigned int a, unsigned int b);
int get_distance(graph_t *x, unsigned int a, unsigned int b);
void maybe_good_suggestions(graph_t *x, unsigned int a, unsigned int *good_suggestions);
unsigned int *suggestions(graph_t *x, unsigned int a);
unsigned int *common_friends(graph_t *x, unsigned int a, unsigned int b);
unsigned int most_popular_friend(graph_t *x, unsigned int a);

struct post_info {
    unsigned int id;
    unsigned int user_id;
    char *title;
};

struct tree_t {
    node_t *parent;
    post_info *info;
    list_t *sons;
};

struct all_posts {
    int nr_posts;
    node_t *root;
};

node_t *new_post(node_t *parent, unsigned int id, unsigned int user_id, char *title);
all_posts *new_all_posts();
post_info *new_post_info(unsigned int id, unsigned int user_id, char *title);
void create_repost(node_t *parent, unsigned int id, unsigned int user_id, char *title);
