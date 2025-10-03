#include "zentra_object.h"

zentra_obj_t *add_zentra_object(zentra_obj_t *a, zentra_obj_t *b){
    if(a == NULL || b == NULL){
        return NULL;
    }
    switch(a->type){
        case INTEGER:{
            switch(b->type){
                case INTEGER:
                    return new_zentra_integer(a->data.v_int + b->data.v_int);
                case FLOAT:
                    return new_zentra_float((float) a->data.v_int + b->data.v_float);
                default:
                    return NULL;    
            }
        }
        case FLOAT:{
            switch(b->type){
                case INTEGER:
                    return new_zentra_float(a->data.v_float + (float)b->data.v_int);
                case FLOAT:
                    return new_zentra_float(a->data.v_float + b->data.v_float);
                default:
                    return NULL;    
            }
        }
        case STRING:{
            if(b->type != STRING){
                return NULL;
            }
            size_t stringlen = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;

            // allocate new string
            char *newstr = malloc(stringlen);
            if (!newstr) return NULL;
            strcpy(newstr, a->data.v_string);  // copy first string
            strcat(newstr, b->data.v_string);  // append second string
            zentra_obj_t *obj = new_zentra_string(newstr);
            free(newstr);
            return obj;
        }
        case VECTOR3:{
            if(b->type != VECTOR3){
                return NULL;
            }
            return new_zentra_vector3(
                add_zentra_object(a->data.v_vector3->x, b->data.v_vector3->x),
                add_zentra_object(a->data.v_vector3->y, b->data.v_vector3->y),
                add_zentra_object(a->data.v_vector3->z, b->data.v_vector3->z)
            );
        }
        case ARRAY: {
            if(b->type != ARRAY){
                return NULL;
            }
            size_t arraylen = a->data.v_array->capacity + b->data.v_array->capacity;
            zentra_obj_t *obj = new_zentra_array(arraylen);

            for(size_t i = 0; i < a->data.v_array->capacity; i++){
                zentra_obj_t *element = zentra_array_get(a, i);
                if(element){
                    zentra_array_set(obj, i, clone_zentra_object(element));
                }
                
            }
            for(size_t i = 0; i < b->data.v_array->capacity; i++){
                // place after the contents of array a
                zentra_obj_t *element = zentra_array_get(b, i);
                if(element){
                    zentra_array_set(obj, i + a->data.v_array->capacity, clone_zentra_object(element));
                }
                
            }
            return obj;
        }
        default:
            return NULL;
    }
}

zentra_obj_t *clone_zentra_object(zentra_obj_t *obj){
    if(obj == NULL){
        return NULL;
    }
    switch(obj->type){
        case INTEGER:{
            return new_zentra_integer(obj->data.v_int);
        }
        case FLOAT:{
            return new_zentra_float(obj->data.v_float);
        }
        case STRING:{
            return new_zentra_string(obj->data.v_string);
        }
        case VECTOR3:{
            zentra_obj_t *x = clone_zentra_object(obj->data.v_vector3->x);
            zentra_obj_t *y = clone_zentra_object(obj->data.v_vector3->y);
            zentra_obj_t *z = clone_zentra_object(obj->data.v_vector3->z);
            if(!x || !y || !z) { 
                free_zentra_object(x);
                free_zentra_object(y);
                free_zentra_object(z);
                return NULL;
            }
            return new_zentra_vector3(x, y, z);
        }
        case ARRAY:{
            // create a new array
            size_t len = obj->data.v_array->capacity;
            // create a new array
            zentra_obj_t *copy_obj = new_zentra_array(len);
            
            for(size_t i = 0; i < len; i++){
                // store each element in the original array
                zentra_obj_t *element = zentra_array_get(obj, i);
                if(element){
                    // add to the new copy array, cloning each element beforehand
                    zentra_array_set(copy_obj, i, clone_zentra_object(element));
                }
            }
            return copy_obj;
        }
        default:
            return NULL;
    }
}

bool compare_zentra_object(zentra_obj_t *a, zentra_obj_t *b){
    if(a == NULL && b == NULL){
        return true;
    }
    if(a == NULL || b == NULL){
        return false;
    }
    switch(a->type){
        case INTEGER:{
            switch(b->type){
                case INTEGER:
                    return (a->data.v_int == b->data.v_int);
                case FLOAT:
                    return ((float) a->data.v_int == b->data.v_float);
                default:
                    return false;    
            }
        }
        case FLOAT:{
            switch(b->type){
                case INTEGER:
                    return (a->data.v_float == (float)b->data.v_int);
                case FLOAT:
                    return (a->data.v_float == b->data.v_float);
                default:
                    return false;    
            }
        }
        case STRING:{
            if(b->type != STRING){
                return false;
            }
            return strcmp(a->data.v_string, b->data.v_string) == 0; // strcmp returns 0 if equal
        }
        case VECTOR3:{
            if(b->type != VECTOR3){
                return false;
            }
            return (
                compare_zentra_object(a->data.v_vector3->x, b->data.v_vector3->x) &&
                compare_zentra_object(a->data.v_vector3->y, b->data.v_vector3->y) &&
                compare_zentra_object(a->data.v_vector3->z, b->data.v_vector3->z));
        }
        case ARRAY:{
            if(b->type != ARRAY){
                return false;
            }
            // if different sizes obviously not equal
            if(a->data.v_array->capacity != b->data.v_array->capacity){
                return false;
            }
            size_t len = a->data.v_array->capacity;
            zentra_obj_t **a_arr = a->data.v_array->elements;
            zentra_obj_t **b_arr = b->data.v_array->elements;
            for(size_t i = 0; i < len; i++){
                if(!compare_zentra_object(a_arr[i], b_arr[i])){
                    return false;
                }
            }
            return true;
        }
    }
}

void free_zentra_object(zentra_obj_t *obj) {
    if (!obj) return;

    switch (obj->type) {
        case STRING:{
            free(obj->data.v_string);
            break;
        }
        case VECTOR3:{
            if (obj->data.v_vector3) {
                free_zentra_object(obj->data.v_vector3->x);
                free_zentra_object(obj->data.v_vector3->y);
                free_zentra_object(obj->data.v_vector3->z);
                free(obj->data.v_vector3);
            }
            break;
        }
        case ARRAY:{
            zentra_array_t *arr = obj->data.v_array;
            if (arr) {
                for (size_t i = 0; i < arr->capacity; ++i) {
                    if (arr->elements[i]) {
                        free_zentra_object(arr->elements[i]);  // Recursive free
                    }
                }
                free(arr->elements);   // Free the array of pointers
                free(arr);          // Free the array structure
            }
            break;
        }
        default:
            // No dynamic memory for int/float
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
