#include "linkedlist.h"
#include <stdio.h>

typedef struct _basicnode{
    char *name;
    int value;
}basicnode;

int main(){
    linkedlist *ll = linkedlist_create();

    basicnode *a = malloc(sizeof(basicnode));
    a->name = strdup("A");
    a->value = 17;

    linkedlist_insert(ll, a->name, a);

    linkedlist_print(ll);

    basicnode *deleted = (basicnode *)linkedlist_delete(ll, "A");
    if (deleted) {
        printf("Deleted: %s (%d)\n", deleted->name, deleted->value);
        free(deleted->name);
        free(deleted);
    }

    linkedlist_print(ll);

    linkedlist_destroy(ll);
}