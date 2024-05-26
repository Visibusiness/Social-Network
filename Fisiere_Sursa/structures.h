#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t node_t;
typedef struct list_t list_t;
typedef struct graph_t graph_t;
typedef struct clique_t clique_t;

typedef struct like_t like_t;
typedef struct post_info_t post_info_t;
typedef struct tree_t tree_t;
typedef struct all_posts_t all_posts_t;

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

struct clique_t {
	unsigned int size;
	unsigned int *state;
};

void free_node(node_t **x);
node_t *new_node(void *data);
node_t *remove_from_list(list_t *list, unsigned int searched);
list_t *new_list(void);
void add_in_list(list_t *list, node_t *node);
void link(node_t *x, node_t *y);
list_t *ll_create(unsigned int data_size);
void ll_free(list_t **pp_list);

graph_t *new_graph(unsigned int nodes);
void free_graph(graph_t **x);
void add_connection(graph_t *x, unsigned int a, unsigned int b);
void remove_connection(graph_t *x, unsigned int a, unsigned int b);
int get_distance(graph_t *x, unsigned int a, unsigned int b);
void maybe_good_suggestions(graph_t *x, unsigned int a,
							unsigned int *good_suggestions);
unsigned int *suggestions(graph_t *x, unsigned int a);
unsigned int *common_friends(graph_t *x, unsigned int a, unsigned int b);
unsigned int most_popular_friend(graph_t *x, unsigned int a);

void free_clique(clique_t **x);
clique_t *new_clique(unsigned int nodes);
void backtracking_clique(graph_t *x, clique_t *cr,
						 clique_t *maximal, unsigned int id);
clique_t *maximal_clique(graph_t *x, unsigned int a);

struct like_t {
	unsigned int id;
	int like;
};

struct post_info_t {
	unsigned int id;
	unsigned int user_id;
	char *title;
	list_t *likes;
};

struct tree_t {
	node_t *parent;
	post_info_t *info;
	list_t *sons;
};

struct all_posts_t {
	int nr_posts;
	node_t *root;
};

node_t *new_post(node_t *parent, unsigned int id,
				 unsigned int user_id, char *title);
all_posts_t *new_all_posts(void);
post_info_t *new_post_info(unsigned int id,
						   unsigned int user_id, char *title);
void create_repost(node_t *parent, unsigned int id,
				   unsigned int user_id, char *title);
node_t *find_node_in_tree(node_t *parent,
						  unsigned int parent_id, unsigned int search_id);
node_t *common_repost_id(node_t *root, node_t *x, node_t *y);
like_t *new_like(unsigned int id);
node_t *find_like(list_t *likes, unsigned int id);
unsigned int like_count(list_t *likes);
void find_most_liked_id(node_t *post, unsigned int *cr_max,
						unsigned int *id_of_max);

void remove_repost(list_t *list, node_t *post);
void free_post_info(post_info_t **info);
void free_post(node_t **post);
void free_all_post(all_posts_t **posts);

int is_friend(graph_t *x, unsigned int a, unsigned int b);
