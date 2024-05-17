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

list_t *new_list();
void add_in_list(list_t *list, node_t* node);
void link(node_t *x, node_t *y);
list_t *ll_create(unsigned int data_size);
node_t *ll_remove_nth_node(list_t *list, unsigned int n);
unsigned int ll_get_size(list_t *list);
void ll_free(list_t **pp_list);
void ll_print_int(list_t *list);
void ll_print_string(list_t *list);

typedef struct info info;
struct info
{
    void *key;
    void *value;
};

typedef struct hashtable_t hashtable_t;
struct hashtable_t
{
    list_t **buckets; /* Array de liste simplu-inlantuite. */
    /* Nr. total de noduri existente curent in toate bucket-urile. */
    unsigned int size;
    unsigned int hmax; /* Nr. de bucket-uri. */
    /* (Pointer la) Functie pentru a calcula valoarea hash asociata cheilor. */
    unsigned int (*hash_function)(void *);
    /* (Pointer la) Functie pentru a compara doua chei. */
    int (*compare_function)(void *, void *);
    /* (Pointer la) Functie pentru a elibera memoria ocupata de cheie si valoare. */
    void (*key_val_free_function)(void *);
};

int compare_function_ints(void *a, void *b);
int compare_function_strings(void *a, void *b);

unsigned int hash_function_int(void *a);
unsigned int hash_function_string(void *a);

void key_val_free_function(void *data);

hashtable_t *ht_create(unsigned int hmax, unsigned int (*hash_function)(void *),
                       int (*compare_function)(void *, void *),
                       void (*key_val_free_function)(void *));

int ht_has_key(hashtable_t *x, void *key);

void *ht_get(hashtable_t *x, void *key);
void ht_put(hashtable_t *x, void *key, unsigned int key_size,
            void *value, unsigned int value_size);

void ht_remove_entry(hashtable_t *x, void *key);

void ht_free(hashtable_t *x);
unsigned int ht_get_size(hashtable_t *ht);
unsigned int ht_get_hmax(hashtable_t *ht);
