#include "../include/zentra_object.h"

zentra_obj_t *new_zentra_object(zentra_arena_t *arena, zentra_obj_type_t type){
    if (!arena) return NULL;

    zentra_obj_t *obj = zentra_arena_alloc(arena, sizeof(zentra_obj_t));
    if (!obj) return NULL;

    obj->type = type;
    return obj;
}

zentra_obj_t *new_zentra_integer(zentra_arena_t *arena, int value){
    zentra_obj_t *obj = new_zentra_object(arena, INTEGER);
    if(obj == NULL){
         return NULL;
    }
    obj->data.v_int = value;
    return obj;
}

zentra_obj_t *new_zentra_float(zentra_arena_t *arena, float value){
    zentra_obj_t *obj = new_zentra_object(arena, FLOAT);
    if(obj == NULL){
         return NULL;
    }
    obj->data.v_float = value;
    return obj;
}

zentra_obj_t *new_zentra_string(zentra_arena_t *arena, const char *value){
    if(!arena || value == NULL){
        return NULL;
    }
    // allocate the object itself
    zentra_obj_t *obj = new_zentra_object(arena, STRING);
    if(obj == NULL){
         return NULL;
    }
    // allocate space for the string in the arena
    size_t len = strlen(value) + 1;

    obj->data.v_string = zentra_arena_alloc(arena, len);
    if(!obj->data.v_string){
        return NULL;
    }
    strcpy(obj->data.v_string, value);
    return obj;
}

zentra_obj_t *new_zentra_vector3(zentra_arena_t *arena, zentra_obj_t *x, zentra_obj_t *y, zentra_obj_t *z){
    if(!arena || x == NULL || y == NULL || z == NULL){
        return NULL;
    }

    // vector only allows numeric values
    if((!zentra_object_is_numeric(x)) || (!zentra_object_is_numeric(y)) || (!zentra_object_is_numeric(z))){
        return NULL;
    }

    zentra_vector3_t *vec = zentra_arena_alloc(arena, sizeof(zentra_vector3_t));
    if (!vec) return NULL;
    vec->x = x;
    vec->y = y;
    vec->z = z;

    zentra_obj_t *obj = new_zentra_object(arena, VECTOR3);
    if (!obj) {
        return NULL;
    }
    obj->data.v_vector3 = vec;

    return obj;
}

zentra_obj_t *new_zentra_array(zentra_arena_t *arena, size_t capacity){
    if(!arena){
        return NULL;
    }
    if(capacity <= 0){
        capacity = 1;
    }
    zentra_array_t *arr = zentra_arena_alloc(arena, sizeof(zentra_array_t));
    if(!arr){
        return NULL;
    }
     
    arr->capacity = capacity;
    arr->elements = zentra_arena_alloc(arena, sizeof(zentra_obj_t *) * capacity);
    if (!arr->elements) {
        return NULL;
    }

    // zero initialize elements
    for(size_t i = 0; i < capacity; i++){
        arr->elements[i] = NULL;
    }

    // allocate the object
    zentra_obj_t *obj = new_zentra_object(arena, ARRAY);
    if(!obj){
        return NULL;
    }
    obj->data.v_array = arr;
    return obj;
}

