#include "zentra_object.h"

zentra_obj_t *new_zentra_integer(int value){
    zentra_obj_t *obj = malloc(sizeof(zentra_obj_t));
    if(obj == NULL){
         return NULL;
    }
    obj->type = INTEGER;
    obj->data.v_int = value;
    return obj;
}

zentra_obj_t *new_zentra_float(float value){
    zentra_obj_t *obj = malloc(sizeof(zentra_obj_t));
    if(obj == NULL){
         return NULL;
    }
    obj->type = FLOAT;
    obj->data.v_float = value;
    return obj;
}

zentra_obj_t *new_zentra_string(const char *value){
    zentra_obj_t *obj = malloc(sizeof(zentra_obj_t));
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

    vec->x = x;
    vec->y = y;
    vec->z = z;

    zentra_obj_t *obj = malloc(sizeof(zentra_obj_t));
    if (!obj) {
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
    zentra_obj_t *obj = malloc(sizeof(zentra_obj_t));
    if(!obj){
        free(arr->elements);
        free(arr);
        return NULL;
    }

    obj->type = ARRAY;
    obj->data.v_array = arr;
    return obj;
}

