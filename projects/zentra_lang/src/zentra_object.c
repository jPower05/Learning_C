#include "../include/zentra_object.h"

zentra_obj_t *new_zentra_object(zentra_vm_t *vm, zentra_obj_type_t type){
    zentra_obj_t *obj = malloc(sizeof(zentra_obj_t));
    if(obj == NULL){
        return NULL;
    }
    obj->type = type;
    obj->is_marked = false;
    push_zentra_object_onto_vm_objects(vm, obj);
    return obj;
}

zentra_obj_t *new_zentra_integer(zentra_vm_t *vm, int value){
    zentra_obj_t *obj = new_zentra_object(vm, INTEGER);
    if(obj == NULL){
         return NULL;
    }
    obj->data.v_int = value;
    return obj;
}

zentra_obj_t *new_zentra_float(zentra_vm_t *vm, float value){
    zentra_obj_t *obj = new_zentra_object(vm, FLOAT);
    if(obj == NULL){
         return NULL;
    }
    obj->data.v_float = value;
    return obj;
}

zentra_obj_t *new_zentra_string(zentra_vm_t *vm, const char *value){
    zentra_obj_t *obj = new_zentra_object(vm, STRING);
    if(obj == NULL){
         return NULL;
    }

    obj->data.v_string = malloc(strlen(value)+1);
    if(obj->data.v_string == NULL){
        free(obj);
        return NULL;
    }
    strcpy(obj->data.v_string, value);
    return obj;
}

zentra_obj_t *new_zentra_vector3(zentra_vm_t *vm, zentra_obj_t *x, zentra_obj_t *y, zentra_obj_t *z){
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

    zentra_obj_t *obj = new_zentra_object(vm, VECTOR3);
    if (!obj) {
        free(vec);
        return NULL;
    }
    obj->data.v_vector3 = vec;

    return obj;
}

zentra_obj_t *new_zentra_array(zentra_vm_t *vm, size_t capacity){
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
    zentra_obj_t *obj = new_zentra_object(vm, ARRAY);
    if(!obj){
        free(arr->elements);
        free(arr);
        return NULL;
    }
    obj->data.v_array = arr;
    return obj;
}

void free_zentra_object(zentra_obj_t *obj) {
    if (!obj) return;

    switch (obj->type) {
        case INTEGER:{
            break;
        }
        case FLOAT:{
            break;
        }
        case STRING:{
            if (obj->data.v_string) {
                free(obj->data.v_string);
            }
            break;
        }
        case VECTOR3:{
            break;
        }
        case ARRAY:{
            if (obj->data.v_array) {
                if (obj->data.v_array->elements) {
                    free(obj->data.v_array->elements);
                    obj->data.v_array->elements = NULL;
                }
                free(obj->data.v_array);
                obj->data.v_array = NULL;
            }
            break;
        }
        default:
            break;
    }
    free(obj);
}

bool zentra_object_is_numeric(zentra_obj_t *obj){
    // only allow numerical values
    if(obj == NULL) return false;
    if(obj->type == INTEGER) return true;
    if(obj->type == FLOAT) return true;
    return false;
}

