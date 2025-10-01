#pragma once
#include <stdlib.h>
#include <string.h>

// forward declare
typedef struct ZentraObject zentra_obj_t;

typedef struct ZentraVector3{
    zentra_obj_t *x;
    zentra_obj_t *y;
    zentra_obj_t *z;
} zentra_vector3_t;

typedef struct ZentraArray{
    zentra_obj_t **elements;
    size_t capacity;
    size_t size;
} zentra_array_t;

typedef enum ZentaObjectType{
    INTEGER,
    FLOAT,
    STRING,
    VECTOR3,
    ARRAY
}zentra_obj_type_t;

typedef union ZentraObjectData{
    int v_int;
    float v_float;
    char *v_string;
    zentra_vector3_t *v_vector3;
    zentra_array_t *v_array;
}zentra_obj_data_t;

typedef struct ZentraObject{
    zentra_obj_type_t type;
    zentra_obj_data_t data;
} zentra_obj_t;


void free_zentra_object(zentra_obj_t *obj);
zentra_obj_t *new_zentra_integer(int value);
zentra_obj_t *new_zentra_float(float value);
zentra_obj_t *new_zentra_string(char *value);
zentra_obj_t *new_zentra_vector3(
    zentra_obj_t *x, zentra_obj_t *y, zentra_obj_t *z
);
zentra_obj_t *new_zentra_array(size_t capacity);
