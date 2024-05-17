#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

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

int compare_function_strings(void *a, void *b)
{
    char *str_a = (char *)a;
    char *str_b = (char *)b;
    return strcmp(str_a, str_b);
}

unsigned int hash_function_string(void *a)
{
    /* Credits: http://www.cse.yorku.ca/~oz/hash.html */
    unsigned char *puchar_a = (unsigned char *)a;
    unsigned long hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}

void key_val_free_function(void *data)
{
    free(((info *)data)->key);
    free(((info *)data)->value);
}

hashtable_t *ht_create(unsigned int hmax, unsigned int (*hash_function)(void *),
                       int (*compare_function)(void *, void *),
                       void (*key_val_free_function)(void *))
{
    hashtable_t *x = malloc(sizeof(hashtable_t));
    x->buckets = malloc(hmax * sizeof(list_t *));
    x->compare_function = compare_function;
    x->hash_function = hash_function;
    x->key_val_free_function = key_val_free_function;
    x->hmax = hmax;
    x->size = 0;
    for (int i = 0; i < x->hmax; i++)
        x->buckets[i] = new_list(sizeof(info));
    return x;
}

int ht_has_key(hashtable_t *x, void *key)
{
    node_t *p = x->buckets[x->hash_function(key) % x->hmax]->head;
    while (p) {
        if (!x->compare_function(((info *)p->data)->key, key))
            return 1;
        p = p->next;
    }
    return 0;
}

void *ht_get(hashtable_t *x, void *key)
{
    list_t *lista = x->buckets[x->hash_function(key) % x->hmax];
    node_t *p = lista->head;
    while (p) {
        if (!x->compare_function(((info *)p->data)->key, key))
            return ((info *)p->data)->value;
        p = p->next;
    }
    return NULL;
}

void ht_put(hashtable_t *x, void *key, unsigned int key_size,
            void *value, unsigned int value_size)
{
    int index = x->hash_function(key) % x->hmax;
    info *data = malloc(sizeof(info));
    data->key = malloc(key_size);
    memcpy(data->key, key, key_size);
    data->value = malloc(value_size);
    memcpy(data->value, value, value_size);
    if (ht_has_key(x, key)) {
        printf("eroare hashtable\n");
        exit(-1);
        // node_t *p = x->buckets[index]->head;
        // while (p) {
        //     if (!x->compare_function(key, ((info *)p->data)->key)) {
        //         free(((info *)p->data)->value);
        //         ((info *)p->data)->value = data->value;
        //     }
        //     p = p->next;
        // }
        // return;
    }
    add_in_list(x->buckets[index], new_node(data));
    x->size++;
}

void ht_remove_entry(hashtable_t *x, void *key)
{
    list_t *list = x->buckets[x->hash_function(key) % x->hmax];
    node_t *p = list->head;
    while (p && x->compare_function(key, ((info *)p->data)->key))
        p = p->next;
    
    node_t *q = remove_from_list(list, key, x->compare_function);
    key_val_free_function(q->data);
    free(q->data);
    free(q);
}

void ht_free(hashtable_t *x)
{
    for (int i = 0; i < x->hmax; i++) {
        node_t *p = x->buckets[i]->head, *aux;
        while (p) {
            aux = p->next;
            key_val_free_function(p->data);
            free(p->data);
            free(p);
            p = aux;
        }
        free(x->buckets[i]);
    }
    free(x->buckets);
    free(x);
}