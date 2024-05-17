#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#define MAX_STRING_SIZE 256
#define HMAX 10


void link(node_t *x, node_t *y)
{
    if(y)
        x->next = y;
    if(x)
        y->prev = x;    
}


list_t *ll_create(unsigned int data_size)
{
    list_t *ll = malloc(sizeof(*ll));
    ll->head = NULL;
    ll->data_size = data_size;
    ll->size = 0;
    return ll;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int ll_get_size(list_t *list)
{
    if (!list)
        return -1;
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
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

int compare_function_strings(void *a, void *b)
{
    char *str_a = (char *)a;
    char *str_b = (char *)b;
    return strcmp(str_a, str_b);
}

/* Functii de hashing: */
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

/*
 * Functie apelata pentru a elibera memoria ocupata de cheia si valoarea unei
 * perechi din hashtable. Daca cheia sau valoarea contin tipuri de date complexe
 * aveti grija sa eliberati memoria luand in considerare acest aspect.
 */
void key_val_free_function(void *data)
{
    free(((info *)data)->key);
    free(((info *)data)->value);
}

/*
 * Functie apelata dupa alocarea unui hashtable pentru a-l initializa.
 * Trebuie alocate si initializate si listele inlantuite.
 */
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

/*
 * Functie care intoarce:
 * 1, daca pentru cheia key a fost asociata anterior o valoare in hashtable
 * folosind functia put;
 * 0, altfel.
 */
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

/*
 * Atentie! Desi cheia este trimisa ca un void pointer (deoarece nu se impune
 * tipul ei), in momentul in care se creeaza o noua intrare in hashtable (in
 * cazul in care cheia nu se gaseste deja in ht), trebuie creata o copie a
 * valorii la care pointeaza key si adresa acestei copii trebuie salvata in
 * structura info asociata intrarii din ht. Pentru a sti cati octeti trebuie
 * alocati si copiati, folositi parametrul key_size.
 *
 * Motivatie:
 * Este nevoie sa copiem valoarea la care pointeaza key deoarece dupa un apel
 * put(ht, key_actual, value_actual), valoarea la care pointeaza key_actual
 * poate fi alterata (de ex: *key_actual++). Daca am folosi direct adresa
 * pointerului key_actual, practic s-ar modifica din afara hashtable-ului cheia
 * unei intrari din hashtable. Nu ne dorim acest lucru, fiindca exista riscul sa
 * ajungem in situatia in care nu mai stim la ce cheie este inregistrata o
 * anumita valoare.
 */
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

/*
 * Procedura care elimina din hashtable intrarea asociata cheii key.
 * Atentie! Trebuie avuta grija la eliberarea intregii memorii folosite pentru o
 * intrare din hashtable (adica memoria pentru copia lui key --vezi observatia
 * de la procedura put--, pentru structura info si pentru structura Node din
 * lista inlantuita).
 */
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

/*
 * Procedura care elibereaza memoria folosita de toate intrarile din hashtable,
 * dupa care elibereaza si memoria folosita pentru a stoca structura hashtable.
 */
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
