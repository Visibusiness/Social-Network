#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#define MAX_STRING_SIZE 256
#define HMAX 10

list_t *ll_create(unsigned int data_size)
{
    list_t *ll = malloc(sizeof(list_t));
    ll->head = NULL;
    ll->data_size = data_size;
    ll->size = 0;
    return ll;
}

unsigned int ll_get_size(list_t *list)
{
    if (!list)
        return -1;
    return list->size;
}

void ll_free(list_t **pp_list)
{
    node_t *currNode;
    if (!pp_list || !*pp_list)
        return;

    while (ll_get_size(*pp_list) > 0) {
        currNode = ll_remove_nth_node(*pp_list, 0);
        free(currNode->data);
        currNode->data = NULL;
        free(currNode);
        currNode = NULL;
    }

    free(*pp_list);
    *pp_list = NULL;
}

int compare_function_ints(void *a, void *b)
{
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b)
        return 0;
    if (int_a < int_b)
        return -1;
        return 1;
}

int compare_function_strings(void *a, void *b)
{
    char *str_a = (char *)a;
    char *str_b = (char *)b;

    return strcmp(str_a, str_b);
}

/*
 * Functii de hashing:
 */
unsigned int hash_function_int(void *a)
{
    /*
     * Credits: https://stackoverflow.com/a/12996028/7883884
     */
    unsigned int uint_a = *((unsigned int *)a);

    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = (uint_a >> 16u) ^ uint_a;
    return uint_a;
}

unsigned int hash_function_string(void *a)
{
    /*
     * Credits: http://www.cse.yorku.ca/~oz/hash.html
     */
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
        x->buckets[i] = ll_create(sizeof(info));
    return x;
}

int ht_has_key(hashtable_t *x, void *key)
{
    node_t *p = x->buckets[x->hash_function(key) % x->hmax]->head;
    while (p != NULL)
    {
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
    while (p != NULL)
    {
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
        node_t *p = x->buckets[index]->head;
        while (p) {
            if (!x->compare_function(key, ((info *)p->data)->key)) {
                free(((info *)p->data)->value);
                ((info *)p->data)->value = data->value;
            }
            p = p->next;
        }
        return;
    }
    list_t *list = x->buckets[index];
    ll_add_nth_node(list, 0, data);
    free(data);
    x->size++;
}

void ht_remove_entry(hashtable_t *x, void *key)
{
    list_t *list = x->buckets[x->hash_function(key) % x->hmax];
    node_t *p = list->head;
    int pos = 0;
    while (p && x->compare_function(key, ((info *)p->data)->key))
    {
        p = p->next;
        pos++;
    }
    node_t *q = ll_remove_nth_node(list, pos);
    key_val_free_function(q->data);
    free(q->data);
    free(q);
}

void ht_free(hashtable_t *x)
{
    for (int i = 0; i < x->hmax; i++)
    {
        node_t *p = x->buckets[i]->head, *aux;
        while (p)
        {
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

unsigned int ht_get_size(hashtable_t *ht)
{
    if (ht == NULL)
        return 0;
    return ht->size;
}

unsigned int ht_get_hmax(hashtable_t *ht)
{
    if (ht == NULL)
        return 0;
    return ht->hmax;
}
