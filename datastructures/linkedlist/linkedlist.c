#include "linkedlist.h"
#include <stdint.h>
#include <stdio.h>

struct _node{
    char *key;
    void *object;
    struct _node *next;
};

struct _linkedlist{
    uint32_t size;
    node *root;
    node *tail;
};

linkedlist *linkedlist_create(){
    linkedlist *ll = malloc(sizeof(*ll));
    if (!ll) return NULL;
    ll->size = 0;
    ll->root = NULL;
    ll->tail = NULL;
    return ll;
}

void linkedlist_destroy(linkedlist *ll){
    if(ll == NULL){
        return;
    }
    
    node *curr = ll->root;

    while(curr != NULL){
        node *tmp = curr->next;
        free(curr->key);
        free(curr);
        curr = tmp;
    }
    free(ll);
}

void linkedlist_print(linkedlist *ll){
    printf("start linkedlist\n");
    if(ll == NULL || ll->size==0 || ll->root == NULL){
        printf("nothing to print\n");
        return;
    }
    node *tmp = ll->root;
    while(tmp != NULL){
        printf("\"%s\"(%p) - \n", tmp->key, tmp->object);
        tmp = tmp->next;
    }
    printf("end linkedlist\n");
}

bool linkedlist_insert(linkedlist *ll, const char *key, void *obj){
    if(key == NULL || ll == NULL){
        return false;
    }
    node *e = malloc(sizeof(*e));
    e->object = obj;
    e->key = strdup(key);
    e->next = NULL;

    // if tail update new tail
    if (ll->tail) {
        ll->tail->next = e;
    } else {
        ll->root = e; // first node
    }
    ll->tail = e;
    ll->size++;
    return true;

}
void *linkedlist_lookup(linkedlist *ll, const char *key){
    if(ll == NULL || key == NULL || ll->root == NULL){
        return NULL;
    }
    node *tmp = ll->root;
    while(tmp != NULL && strcmp(tmp->key, key) != 0){
        tmp = tmp->next;
    }
    if(tmp == NULL) return NULL;
    return tmp->object;
}

void *linkedlist_delete(linkedlist *ll, const char *key){
    if(ll == NULL || key == NULL || ll->root == NULL){
        return NULL;
    }

    node *curr = ll->root;
    node *prev = NULL;

    while(curr != NULL){
        if(strcmp(curr->key, key) == 0){

            // if curr is the only node
            if(curr == ll->root && curr == ll->tail){
                ll->root = NULL;
                ll->tail = NULL;
            }

            // if curr is the head but not only node
            else if(curr == ll -> root){
                ll -> root = curr->next;
            }

            // if curr is the tail
            else if(curr == ll->tail){
                ll->tail = prev;
                prev->next = NULL;
            }

            // any other node in the middle
            else{
                prev->next = curr->next;
            }

            void *value = curr->object;
            // free memory
            free(curr->key);
            free(curr);
            ll->size--;
            return value;   // return the node's object so they can handle freeing
        }
        prev = curr;
        curr = curr->next;
    }

    return NULL;
}