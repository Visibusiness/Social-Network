#include "graph.h"

node_t *new_node(void *data)
{
    node_t *x = malloc(sizeof(node_t));
    x->data = data;
    x->prev = NULL;
    x->next = NULL;
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
                if(list->head)
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

post_info_t *new_post_info(unsigned int id, unsigned int user_id, char *title)
{
    post_info_t *x = malloc(sizeof(post_info_t));
    x->id = id;
    x->user_id = user_id;
    x->title = title;
    x->likes = new_list();
    return x;
}

node_t *new_post(node_t *parent, unsigned int id, unsigned int user_id, char *title)
{
    tree_t *tree = malloc(sizeof(tree_t));
    tree->info = new_post_info(id, user_id, title);
    tree->parent = parent;
    tree->sons = new_list();
    return new_node(tree);
}

all_posts_t *new_all_posts()
{
    all_posts_t *x = malloc(sizeof(all_posts_t));
    x->nr_posts = 0;
    x->root = new_post(NULL, 0, 0, NULL);
    return x;
}

void create_repost(node_t *parent, unsigned int id, unsigned int user_id, char *title)
{
    list_t *sons = ((tree_t*)(parent->data))->sons;
    add_in_list(sons, new_post(parent, id, user_id, title));
}

node_t *find_node_in_tree(node_t *parent, unsigned int parent_id, unsigned int search_id)
{
    if(!parent)
        return NULL;
    node_t *cr = ((tree_t*)(parent->data))->sons->head;
    while(cr) {
        unsigned int cr_id = ((tree_t*)(cr->data))->info->id;
        if(search_id == 0) {
            if(cr_id == parent_id)
                return cr;
        } else {
            if(cr_id == parent_id) {
                if(parent_id == search_id)
                    return cr;
                return find_node_in_tree(cr, search_id, search_id);
            }
            if(parent_id == search_id) {
                node_t *find = find_node_in_tree(cr, search_id, search_id);
                if(find)
                    return find;
            }
        }
        cr = cr->next;
    }
    return NULL;
}

node_t *parent(node_t *x)
{
    if(!x)
        return NULL;
    return ((tree_t *)(x->data))->parent;
}

unsigned int distance_to_root(node_t *root, node_t *x)
{
    unsigned int distance = 0;
    while(x != root) {
        x = parent(x);
        distance++;
    }
    return distance;
}

node_t *common_repost_id(node_t *root, node_t *x, node_t *y)
{
    unsigned int a = distance_to_root(root, x);
    unsigned int b = distance_to_root(root, y);
    while (a > b) {
        x = parent(x);
        a--;
    }
    while (b > a) {
        y = parent(y);
        b--;
    }
    while (x != y) {
        x = parent(x);
        y = parent(y);
    }
    return x;
}

like_t *new_like(unsigned int id)
{
    like_t *x = malloc(sizeof(like_t));
    x->id = id;
    x->like = 1;
    return x;
}

node_t *find_like(list_t *likes, unsigned int id)
{
    node_t *cr = likes->head;
    while (cr) {
        if(((like_t *)(cr->data))->id == id)
            return cr;
        cr = cr->next;
    }
    return NULL;
}

unsigned int like_count(list_t *likes)
{
    int count = 0;
    node_t *cr = likes->head;
    while (cr) {
        if(((like_t *)(cr->data))->like == 1)
            count++;
        cr = cr->next;
    }
    return count;
}

void find_most_liked_id(node_t *post, unsigned int *most_likes, unsigned int *most_liked_id)
{
    if(!post)
        return;
    unsigned int cr_likes = like_count(((tree_t*)(post->data))->info->likes);
    unsigned int cr_id = ((tree_t*)(post->data))->info->id;
    if(cr_likes > *most_likes || ((cr_likes == *most_likes) && (cr_id > *most_liked_id))) {
        *most_likes = cr_likes;
        *most_liked_id = cr_id;
    }
    node_t *cr = ((tree_t*)(post->data))->sons->head;
    while (cr) {
        find_most_liked_id(cr, most_likes, most_liked_id);
        cr = cr->next;
    }
}

void remove_repost(list_t *list, node_t *post)
{
    list->size--;
    if(post != list->head)
        link(post->prev, post->next);
    else {
        list->head = post->next;
        if(list->head)
            list->head->prev = NULL;
    }
}

void free_post_info(post_info_t **info)
{
    if(!*info)
        return;
    if((*info)->title)
        free((*info)->title);
    node_t *cr = (*info)->likes->head, *next;
    while(cr) {
        next = cr->next;
        free(cr->data);
        free(cr);
        cr = next;
    }
    free((*info)->likes);
    free(*info);
}

void free_post(node_t **post)
{
    if(!*post)
        return;
    tree_t *tree = (tree_t*)((*post)->data);
    free_post_info(&(tree->info));
    node_t *cr = tree->sons->head, *next;
    while(cr) {
        next = cr->next;
        free_post(&cr);
        cr = next;
    }
    free(tree->sons);
    free(tree);
    free(*post);
    *post = NULL;
}

void free_all_post(all_posts_t *posts)
{
    free_post(&(posts->root));
}

int is_friend(graph_t *x, unsigned int a, unsigned int b)
{
    node_t *cr = x->friends[a]->head;
    while(cr) {
        if(*(unsigned int *)cr->data == b)
            return 1;
        cr = cr->next;
    }
    return 0;
}