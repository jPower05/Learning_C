#include "../include/zentra_object.h"

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

    array->elements[index] = value;
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

    if(!array || array->capacity <= index){
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
    if(value == NULL){
        return false;
    }
    
    zentra_array_t *array = arr->data.v_array;
    for(size_t i = 0; i < array->capacity; i++){
        if(array->elements[i] && compare_zentra_object(array->elements[i], value)){
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

    zentra_array_t *array = arr->data.v_array;
    
    for(size_t i = 0; i < array->capacity; i++){
        // no freeing - just clear the pointer
        array->elements[i] = NULL;  
    }
}

