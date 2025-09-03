#include "hashtable.h"

uint64_t hash(const char *name, size_t length){
    uint64_t hash_value = 0;
    for(int i = 0; i < length; i++){
        hash_value += name[i];
        hash_value = hash_value * name[i];
    }
    return hash_value;
}


int main(){
    // create hashtable
    const int tablesize = (1<<4);
    hashtable *ht = hashtable_create(tablesize, hash);
    hashtable_print(ht);
    hashtable_destroy(ht);
}