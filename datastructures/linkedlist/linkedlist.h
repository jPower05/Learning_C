#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct _linkedlist linkedlist;
typedef struct _node node;

linkedlist *linkedlist_create();
void linkedlist_destroy(linkedlist *ll);
void linkedlist_print(linkedlist *ll);
bool linkedlist_insert(linkedlist *ll, const char *key, void *object);
void *linkedlist_lookup(linkedlist *ll, const char *key);
void *linkedlist_delete(linkedlist *ll, const char *key);