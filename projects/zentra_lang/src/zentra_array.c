#include "zentra_object.h"

bool zentra_array_set(zentra_obj_t *arr, size_t index, zentra_obj_t *value){
    if(arr == NULL || value == NULL){
        return false;
    }
    if(arr->type != ARRAY){
        return false;
    }
    
    zentra_array_t *array = arr->data.v_array;

    if(array->capacity <= index){
        return false;
    }

    // free previous value if it exists
    zentra_obj_t *prev = array->elements[index];
    if(prev){
        refcount_dec(prev);
    }
    array->elements[index] = value;
    if(value){
        refcount_inc(value);
    }
    return true;
}

zentra_obj_t *zentra_array_get(zentra_obj_t *arr, size_t index){
    if(arr == NULL){
        return NULL;
    }
    if(arr->type != ARRAY){
        return NULL;
    }

    zentra_array_t *array = arr->data.v_array;

    if(array->capacity <= index){
        return NULL;
    }

    return array->elements[index];
}

bool zentra_array_contains(zentra_obj_t *arr, zentra_obj_t *value){
    if(arr == NULL){
        return false;
    }
    if(arr->type != ARRAY){
        return false;
    }
    size_t len = arr->data.v_array->capacity;
    zentra_obj_t **elements = arr->data.v_array->elements;
    for(size_t i = 0; i < len; i++){
        if(compare_zentra_object(elements[i], value)){
            return true;
        }
    }
    return false;
}

void zentra_array_clear(zentra_obj_t *arr){
    if(arr == NULL){
        return;
    }
    if(arr->type != ARRAY){
        return;
    }

    size_t len = arr->data.v_array->capacity;
    
    for(size_t i = 0; i < len; i++){
        zentra_obj_t *element = zentra_array_get(arr, i);
        if(element){
            refcount_dec(element);
            zentra_array_set(arr,i,NULL);
        }
    }
}

