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
    if(array->elements[index] != NULL){
        free_zentra_object(array->elements[index]);
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

    if(array->capacity <= index){
        return NULL;
    }

    return array->elements[index];
}

