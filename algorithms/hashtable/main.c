#include "hashtable.h"

uint64_t hash(const char *name, size_t length){
    uint64_t hash_value = 0;
    for(int i = 0; i < length; i++){
        hash_value += name[i];
        hash_value = hash_value * name[i];
    }
    return hash_value;
}

typedef struct _person{
    char *name;
    int age;
}person;


int main(){
    // create hashtable
    const int tablesize = (1<<4);
    hashtable *ht = hashtable_create(tablesize, hash);

    // sample person 
    person *jacob = malloc(sizeof(person));
    jacob->name = strdup("Jacob");
    jacob->age = 11;

    person *ron = malloc(sizeof(person));
    ron->name = strdup("Ron");
    ron->age = 11;


    hashtable_insert(ht, jacob->name, jacob);
    hashtable_insert(ht, ron->name, ron);

    hashtable_print(ht);

    hashtable_delete(ht, "Jacob");
    hashtable_print(ht);
    hashtable_destroy(ht);

    

}