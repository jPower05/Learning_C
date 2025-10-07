#pragma once
#include "zentra_arena_allocator.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Forward declarations (opaque types)
typedef struct ZentraObject zentra_obj_t;
typedef struct ZentraArray zentra_array_t;

typedef struct ZentraVector3{
    zentra_obj_t *x;
    zentra_obj_t *y;
    zentra_obj_t *z;
} zentra_vector3_t;

typedef struct ZentraArray{
    zentra_obj_t **elements;
    size_t capacity;
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
zentra_obj_t *new_zentra_object(zentra_arena_t *arena, zentra_obj_type_t type);
zentra_obj_t *new_zentra_integer(zentra_arena_t *arena, int value);
zentra_obj_t *new_zentra_float(zentra_arena_t *arena, float value);
zentra_obj_t *new_zentra_string(zentra_arena_t *arena, const char *value);
zentra_obj_t *new_zentra_vector3(
    zentra_arena_t *arena,
    zentra_obj_t *x, zentra_obj_t *y, zentra_obj_t *z
);
zentra_obj_t *new_zentra_array(zentra_arena_t *arena, size_t capacity);

// Array functionality
bool zentra_array_set(zentra_obj_t *arr, size_t index, zentra_obj_t *value);
zentra_obj_t *zentra_array_get(zentra_obj_t *arr, size_t index);
bool zentra_array_contains(zentra_obj_t *arr, zentra_obj_t *value);
void zentra_array_clear(zentra_obj_t *arr);

// Object Operators
zentra_obj_t *add_zentra_object(zentra_arena_t *arena, zentra_obj_t *a, zentra_obj_t *b);
zentra_obj_t *clone_zentra_object(zentra_arena_t *arena, zentra_obj_t *obj);
bool compare_zentra_object(zentra_obj_t *a, zentra_obj_t *b);

// helper functions
bool zentra_object_is_numeric(zentra_obj_t *obj);

