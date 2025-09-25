// model a variant type that can hold either an int, a float, or a string. 
// The enum will describe the type, the union will store the data, 
// and the struct will combine them

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// enum to describle what kind of type the value is
typedef enum ValueType{
    INT,
    FLOAT,
    STRING,
} value_type_t;

// Union that can hold either an int, string or float
typedef union ValueUnion{
    int i;
    float f;
    char *s;
} value_union_t;

// struct Variant that holds both a union for its value and an enum which defines its type
typedef struct Variant{
    value_type_t type;
    value_union_t value;
}variant_t;


void variant_print(variant_t *v){
    if(v == NULL) return;
    switch(v->type){
        case INT:
            printf("Integer: %d\n", v->value.i);
            break;
        case FLOAT:
            printf("Float: %.2f\n", v->value.f);
            break;
        case STRING:
            printf("String: %s\n", v->value.s);
            break;
    }
}

// need a helper method to construct String variants
variant_t *variant_construct_string(char *value){
    variant_t *v = malloc(sizeof(variant_t));
    if(v == NULL) return NULL;
    v->type = STRING;
    v->value.s = strdup(value);
    if(v->value.s == NULL){
        free(v);
        return NULL;
    }
    return v;
}

// need a helper method to construct int variants
variant_t *variant_construct_int(int value){
    variant_t *v = malloc(sizeof(variant_t));
    if(v == NULL) return NULL;
    v->type = INT;
    v->value.i = value;
    return v;
}

// need a helper method to construct int variants
variant_t *variant_construct_float(float value){
    variant_t *v = malloc(sizeof(variant_t));
    if(v == NULL) return NULL;
    v->type = FLOAT;
    v->value.f = value;
    return v;
}

// Free a variant
void variant_free(variant_t *v) {
    if (v == NULL) return;

    if (v->type == STRING && v->value.s) {
        free(v->value.s);
    }
    free(v);
}


int main(){
    // create variants
    variant_t *i = variant_construct_int(5);
    variant_t *f = variant_construct_float(10.0f);
    variant_t *s = variant_construct_string("Hello There");

    variant_print(i);
    variant_print(f);
    variant_print(s);

    variant_free(i);
    variant_free(f);
    variant_free(s);

    return 0;
}