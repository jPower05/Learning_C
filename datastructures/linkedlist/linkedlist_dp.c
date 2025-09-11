#include "linkedlist_dp.h"

struct _node_dp{
    int value;
    struct _node_dp *next;
};


node_dp *node_create(int value){
    // allocate space
    node_dp *n = (node_dp*)malloc(sizeof(n));
    
    n->value = value;
    n->next = NULL;
    return n;
}

void *node_append(node_dp **head_ref, int value){
    // create a new node
    node_dp *n = node_create(value);
    // check if current head
    if(*head_ref == NULL){
        *head_ref = n;
        return;
    }
    node_dp *curr = *head_ref;
    node_dp *prev = NULL;
    while(curr != NULL){
        prev = curr;
        curr = curr->next;
    }
    prev->next = n;
}
void node_print(node_dp ** head_ref){
    printf("printing linkedlist\n");
    if(*head_ref == NULL){
        printf("nothing to print\n");
        return;
    }
    node_dp *curr = *head_ref;
    while(curr != NULL){
        printf("curr : \n", curr->value);
        curr = curr->next;
    }
    printf("finished printing\n");

}
node_dp *node_delete(node_dp **head_ref, int value){
    if (*head_ref == NULL) return NULL;

    node_dp *curr = *head_ref;
    node_dp *prev = NULL;

    while(curr != NULL){
        if(curr->value == value){
            // found the node
            if(prev == NULL){
                // deleting the head
                *head_ref = curr->next;
            }else{
                prev->next = curr->next;
            }
            curr->next = NULL;  // detach the deleted node
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

void free(node_dp **head_ref){
    node_dp *curr = *head_ref;
    node_dp *next = NULL;

    while(curr != NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }

    // set head to null
    *head_ref = NULL;
}