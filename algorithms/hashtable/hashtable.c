#include "hashtable.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _entry{
    char *key;
    void *object;
    struct _entry *next;
}entry;

struct _hashtable{
    uint32_t size;
    hashfunction *hash;
    entry **elements;
};

static size_t hashtable_index(hashtable *ht, const char *key){
    size_t result = (ht->hash(key, strlen(key)) % ht->size);
    return result;
}

hashtable *hashtable_create(uint32_t size, hashfunction *hf){
    hashtable *ht = malloc(sizeof(*ht));
    ht->size = size;
    ht->hash = hf;
    ht->elements = calloc(sizeof(entry*), ht->size);
    return ht;
}


void hashtable_destroy(hashtable *ht){
    free(ht->elements);
    free(ht);
}


void hashtable_print(hashtable *ht){
    printf("start table\n");
    for(uint32_t i=0; i < ht->size; i++){
        if(ht->elements[i] == NULL){
            // disable this if using bigger table
            printf("\t%i\t---\n", i);
        }else{
            printf("\t%i\t\n", i);
            entry *tmp = ht->elements[i];
            while(tmp != NULL){
                printf("\"%s\"(%p) - ", tmp->key, tmp->object);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("end table \n");
}


bool hashtable_insert(hashtable *ht, const char *key, void *obj){
    if(key == NULL || ht == NULL || obj == NULL){
        return false;
    }
    size_t index = hashtable_index(ht, key);
    // test if already exists
    if(hashtable_lookup(ht, key) != NULL) return false;
    // create new entry
    entry *e = malloc(sizeof(*e));
    e->object = obj;
    e->key = malloc(strlen(key)+1);
    strcpy(e->key, key);
    // insert entry -> add the new element to the start of the elements list
    // setting it as its head and setting the previous head to be the new elements
    // next
    e->next = ht->elements[index];
    ht->elements[index] = e;
    return true;
}
// TODO fix dupe index calls
void *hashtable_lookup(hashtable *ht, const char *key){
    if(key == NULL || ht == NULL){
        return false;
    }
    size_t index = hashtable_index(ht, key);
    entry *tmp = ht->elements[index];
    while(tmp != NULL && strcmp(tmp->key, key) != 0){
        tmp = tmp->next;
    }
    if(tmp == NULL) return NULL;
    return tmp->object;

}
void *hashtable_delete(hashtable *ht, const char *key){
    if(key == NULL || ht == NULL){
        return false;
    }
    size_t index = hashtable_index(ht, key);
    entry *tmp = ht->elements[index];
    entry *prev = NULL;
    while(tmp != NULL && strcmp(tmp->key, key) != 0){
        prev = tmp;
        tmp = tmp->next;
    }
    if(tmp == NULL) return NULL;
    if(prev == NULL){
        // deleting the head of the list
        ht->elements[index] = tmp->next;
    }else{
        // deleting from not the head
        prev->next = tmp->next;
    }
    void *result = tmp->object;
    free(tmp);
    return result;
}