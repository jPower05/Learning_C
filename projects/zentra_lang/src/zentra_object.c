#include "zentra_object.h"
#include <stdio.h>

zentra_obj_t *new_zentra_object(){
    zentra_obj_t *obj = malloc(sizeof(zentra_obj_t));
    if(obj == NULL){
        return NULL;
    }
    obj->refcount = 1;
    return obj;
}

zentra_obj_t *new_zentra_integer(int value){
    zentra_obj_t *obj = new_zentra_object();
    if(obj == NULL){
         return NULL;
    }
    obj->type = INTEGER;
    obj->data.v_int = value;
    return obj;
}

zentra_obj_t *new_zentra_float(float value){
    zentra_obj_t *obj = new_zentra_object();
    if(obj == NULL){
         return NULL;
    }
    obj->type = FLOAT;
    obj->data.v_float = value;
    return obj;
}

zentra_obj_t *new_zentra_string(const char *value){
    zentra_obj_t *obj = new_zentra_object();
    if(obj == NULL){
         return NULL;
    }
    obj->type = STRING;

    obj->data.v_string = malloc(strlen(value)+1);
    if(obj->data.v_string == NULL){
        free(obj);
        return NULL;
    }
    strcpy(obj->data.v_string, value);
    return obj;
}

zentra_obj_t *new_zentra_vector3(zentra_obj_t *x, zentra_obj_t *y, zentra_obj_t *z){
    if(x == NULL || y == NULL || z == NULL){
        return NULL;
    }
    zentra_vector3_t *vec = malloc(sizeof(zentra_vector3_t));
    if (!vec) return NULL;

    
    // vector only allows numeric values
    if((!zentra_object_is_numeric(x)) || (!zentra_object_is_numeric(y)) || (!zentra_object_is_numeric(z))){
        return NULL;
    }

    // increment refcounts
    refcount_inc(x);
    refcount_inc(y);
    refcount_inc(z);

    vec->x = x;
    vec->y = y;
    vec->z = z;

    zentra_obj_t *obj = new_zentra_object();
    if (!obj) {
        refcount_dec(x);
        refcount_dec(y);
        refcount_dec(z);
        free(vec);
        return NULL;
    }

    obj->type = VECTOR3;
    obj->data.v_vector3 = vec;

    return obj;
}

zentra_obj_t *new_zentra_array(size_t capacity){
    if(capacity <= 0){
        capacity = 1;
    }
    zentra_array_t *arr = malloc(sizeof(zentra_array_t));
    if(!arr){
        return NULL;
    }
     
    arr->capacity = capacity;
    arr->elements = calloc(arr->capacity, sizeof(zentra_obj_t *));  // size of a pointer
    if (!arr->elements) {
        free(arr);
        return NULL;
    }

    // allocate the object
    zentra_obj_t *obj = new_zentra_object();
    if(!obj){
        free(arr->elements);
        free(arr);
        return NULL;
    }

    obj->type = ARRAY;
    obj->data.v_array = arr;
    return obj;
}

void refcount_inc(zentra_obj_t *obj){
    if(obj == NULL){
        return;
    }
    obj->refcount++;
    return;
}

void refcount_dec(zentra_obj_t *obj){
    if(obj == NULL){
        return;
    }
    obj->refcount--;
    printf("[dec] type=%d, obj=%p, refcount=%d\n", obj->type, (void*)obj, obj->refcount);
    fflush(stdout);
    if(obj->refcount == 0){
        refcount_free(obj);
    }
}

void refcount_free(zentra_obj_t *obj){
    if(obj == NULL){
        return;
    }
    // Diagnostic: print type and address being freed
    const char *type_str = "UNKNOWN";
    switch(obj->type){
        case INTEGER: type_str = "INTEGER"; break;
        case FLOAT: type_str = "FLOAT"; break;
        case STRING: type_str = "STRING"; break;
        case VECTOR3: type_str = "VECTOR3"; break;
        case ARRAY: type_str = "ARRAY"; break;
    }
    printf("[free] type=%s, obj=%p, refcount=%d\n", type_str, (void*)obj, obj->refcount);
    fflush(stdout);
    switch(obj->type){
        case INTEGER:{
            break;
        }
        case FLOAT:{
            break;
        }
        case STRING:{
            if (obj->data.v_string) {
                printf("  [free] string data at %p\n", (void*)obj->data.v_string);
                fflush(stdout);
                free(obj->data.v_string);
            }
            break;
        }
        case VECTOR3:{
            if(obj->data.v_vector3){
                printf("  [free] vector3 struct at %p\n", (void*)obj->data.v_vector3);
                fflush(stdout);
                refcount_dec(obj->data.v_vector3->x);
                refcount_dec(obj->data.v_vector3->y);
                refcount_dec(obj->data.v_vector3->z);
                free(obj->data.v_vector3);
            }
            break;
        }
        case ARRAY:{
            if(obj->data.v_array){
                printf("  [free] array struct at %p, elements at %p\n", (void*)obj->data.v_array, (void*)obj->data.v_array->elements);
                fflush(stdout);
                size_t len = obj->data.v_array->capacity;
                for(size_t i = 0; i < len; i++){
                    refcount_dec(obj->data.v_array->elements[i]);
                }
                free(obj->data.v_array->elements);
                free(obj->data.v_array);
            }
            break;
        }
        default:
            break;
    }
    free(obj);
}

