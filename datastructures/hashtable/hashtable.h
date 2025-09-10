#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct _hashtable hashtable;
typedef struct _entry entry;
typedef uint64_t (hashfunction) (const char*, size_t);

hashtable *hashtable_create(uint32_t size, hashfunction *hf);
void hashtable_destroy(hashtable *ht);
void hashtable_print(hashtable *ht);
bool hashtable_insert(hashtable *ht, const char *key, void *object);
void *hashtable_lookup(hashtable *ht, const char *key);
void *hashtable_delete(hashtable *ht, const char *key);