#include <CUnit/CUnit.h>
#include "../include/zentra_object.h"
#include <stdlib.h>

void test_add_integers(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *a = new_zentra_integer(arena, 5);
    zentra_obj_t *b = new_zentra_integer(arena, 3);

    zentra_obj_t *result = add_zentra_object(arena, a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == INTEGER);
    CU_ASSERT_TRUE(result->data.v_int == 8);

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_add_integer_float(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);
    CU_ASSERT_PTR_NOT_NULL(arena);  

    zentra_obj_t *a = new_zentra_integer(arena, 4);
    zentra_obj_t *b = new_zentra_float(arena, 2.5f);

    zentra_obj_t *result = add_zentra_object(arena, a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == FLOAT);
    CU_ASSERT_DOUBLE_EQUAL(result->data.v_float, 6.5, 0.0001);

    // destory the arena
    zentra_arena_destroy(arena);
}

void test_add_strings(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);
    CU_ASSERT_PTR_NOT_NULL(arena);  

    zentra_obj_t *a = new_zentra_string(arena, "Hello ");
    zentra_obj_t *b = new_zentra_string(arena, "World");

    zentra_obj_t *result = add_zentra_object(arena, a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == STRING);
    CU_ASSERT_STRING_EQUAL(result->data.v_string, "Hello World");

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_add_vectors(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *x1 = new_zentra_integer(arena, 1);
    zentra_obj_t *y1 = new_zentra_integer(arena, 2);
    zentra_obj_t *z1 = new_zentra_integer(arena, 3);
    zentra_obj_t *v1 = new_zentra_vector3(arena, x1, y1, z1);

    zentra_obj_t *x2 = new_zentra_integer(arena, 4);
    zentra_obj_t *y2 = new_zentra_integer(arena, 5);
    zentra_obj_t *z2 = new_zentra_integer(arena, 6);
    zentra_obj_t *v2 = new_zentra_vector3(arena, x2, y2, z2);

    zentra_obj_t *result = add_zentra_object(arena, v1, v2);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == VECTOR3);
    CU_ASSERT_TRUE(result->data.v_vector3->x->data.v_int == 5);
    CU_ASSERT_TRUE(result->data.v_vector3->y->data.v_int == 7);
    CU_ASSERT_TRUE(result->data.v_vector3->z->data.v_int == 9);

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_add_arrays(void) {
    // create a temporary arena for allocation 
    zentra_arena_t *arena = zentra_arena_create(1024);
    CU_ASSERT_PTR_NOT_NULL(arena);  

    zentra_obj_t *a = new_zentra_array(arena, 2);
    zentra_array_set(a, 0, new_zentra_integer(arena, 1));
    zentra_array_set(a, 1, new_zentra_integer(arena, 2));

    zentra_obj_t *b = new_zentra_array(arena, 2);
    zentra_array_set(b, 0, new_zentra_integer(arena, 3));
    zentra_array_set(b, 1, new_zentra_integer(arena, 4));

    zentra_obj_t *result = add_zentra_object(arena, a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == ARRAY);
    CU_ASSERT_TRUE(result->data.v_array->capacity == 4);
    CU_ASSERT_TRUE(result->data.v_array->elements[0]->data.v_int == 1);
    CU_ASSERT_TRUE(result->data.v_array->elements[1]->data.v_int == 2);
    CU_ASSERT_TRUE(result->data.v_array->elements[2]->data.v_int == 3);
    CU_ASSERT_TRUE(result->data.v_array->elements[3]->data.v_int == 4);

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_add_null(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *a = new_zentra_integer(arena, 1);
    zentra_obj_t *result = add_zentra_object(arena, a, NULL);
    CU_ASSERT_PTR_NULL(result);
    zentra_arena_destroy(arena);
}

void test_clone_integer(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *orig = new_zentra_integer(arena, 42);
    zentra_obj_t *copy = clone_zentra_object(arena, orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_clone_float(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);      
    CU_ASSERT_PTR_NOT_NULL(arena);  

    zentra_obj_t *orig = new_zentra_float(arena, 3.14f);
    zentra_obj_t *copy = clone_zentra_object(arena, orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_clone_string(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);      
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *orig = new_zentra_string(arena, "Hello");
    zentra_obj_t *copy = clone_zentra_object(arena, orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));
    CU_ASSERT_PTR_NOT_EQUAL(orig->data.v_string, copy->data.v_string); // deep copy

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_clone_vector3(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);      
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *x = new_zentra_integer(arena, 1);
    zentra_obj_t *y = new_zentra_integer(arena, 2);
    zentra_obj_t *z = new_zentra_integer(arena, 3);
    zentra_obj_t *orig = new_zentra_vector3(arena, x, y, z);
    zentra_obj_t *copy = clone_zentra_object(arena, orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));
    CU_ASSERT_PTR_NOT_EQUAL(orig->data.v_vector3, copy->data.v_vector3);

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_clone_array(void) {
    // create a temporary arena for allocation      
    zentra_arena_t *arena = zentra_arena_create(1024);
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *arr = new_zentra_array(arena, 2);
    zentra_array_set(arr, 0, new_zentra_integer(arena, 10));
    zentra_array_set(arr, 1, new_zentra_integer(arena, 20));

    zentra_obj_t *copy = clone_zentra_object(arena, arr);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(arr, copy));
    CU_ASSERT_PTR_NOT_EQUAL(arr->data.v_array, copy->data.v_array);
    CU_ASSERT_PTR_NOT_EQUAL(arr->data.v_array->elements[0], copy->data.v_array->elements[0]);
    CU_ASSERT_PTR_NOT_EQUAL(arr->data.v_array->elements[1], copy->data.v_array->elements[1]);

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_clone_null(void) {
    // allocate a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);      
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *copy = clone_zentra_object(arena, NULL);
    CU_ASSERT_PTR_NULL(copy);
    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_compare_integers(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);      
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *a = new_zentra_integer(arena, 5);
    zentra_obj_t *b = new_zentra_integer(arena, 5);
    zentra_obj_t *c = new_zentra_integer(arena, 7);

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_compare_integer_float(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *a = new_zentra_integer(arena, 5);
    zentra_obj_t *b = new_zentra_float(arena, 5.0f);
    zentra_obj_t *c = new_zentra_float(arena, 5.1f);

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_compare_strings(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);      
    CU_ASSERT_PTR_NOT_NULL(arena);  

    zentra_obj_t *a = new_zentra_string(arena, "Hello");
    zentra_obj_t *b = new_zentra_string(arena, "Hello");
    zentra_obj_t *c = new_zentra_string(arena, "World");

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_compare_vector3(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);      
    CU_ASSERT_PTR_NOT_NULL(arena);
    
    zentra_obj_t *v1 = new_zentra_vector3(
        arena,
        new_zentra_integer(arena,1), new_zentra_integer(arena, 2), new_zentra_integer(arena, 3)
    );
    zentra_obj_t *v2 = new_zentra_vector3(
        arena,
        new_zentra_integer(arena,1), new_zentra_integer(arena,2), new_zentra_integer(arena,3)
    );
    zentra_obj_t *v3 = new_zentra_vector3(
        arena,
        new_zentra_integer(arena, 1), new_zentra_integer(arena, 2), new_zentra_integer(arena, 4)
    );

    CU_ASSERT_TRUE(compare_zentra_object(v1, v2));
    CU_ASSERT_FALSE(compare_zentra_object(v1, v3));

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_compare_arrays(void) {

    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);      
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *a = new_zentra_array(arena, 2);
    zentra_array_set(a, 0, new_zentra_integer(arena, 10));
    zentra_array_set(a, 1, new_zentra_integer(arena, 20));

    zentra_obj_t *b = new_zentra_array(arena, 2);
    zentra_array_set(b, 0, new_zentra_integer(arena, 10));
    zentra_array_set(b, 1, new_zentra_integer(arena, 20));

    zentra_obj_t *c = new_zentra_array(arena, 2);
    zentra_array_set(c, 0, new_zentra_integer(arena, 10));
    zentra_array_set(c, 1, new_zentra_integer(arena, 21));

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_compare_null(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);    
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *a = NULL;
    zentra_obj_t *b = NULL;
    zentra_obj_t *c = new_zentra_integer(arena, 1);

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));
    CU_ASSERT_FALSE(compare_zentra_object(c, b));

    // destroy the arena
    zentra_arena_destroy(arena);
}

void test_compare_different_types(void) {
    // create a temporary arena for allocation
    zentra_arena_t *arena = zentra_arena_create(1024);      
    CU_ASSERT_PTR_NOT_NULL(arena);

    zentra_obj_t *i = new_zentra_integer(arena, 5);
    zentra_obj_t *f = new_zentra_float(arena, 5.0f);
    zentra_obj_t *s = new_zentra_string(arena, "5");

    CU_ASSERT_TRUE(compare_zentra_object(i, f)); // numeric match
    CU_ASSERT_FALSE(compare_zentra_object(i, s)); // different type
    CU_ASSERT_FALSE(compare_zentra_object(f, s));

    // destroy the arena
    zentra_arena_destroy(arena);
}



// Registration function called from test_runner.c
void add_zentra_object_operators_test(void) {
    CU_pSuite suite = CU_add_suite("ZentraObjectOperatorsTests", NULL, NULL);
    if (suite == NULL) return;

    CU_add_test(suite, "Add integers", test_add_integers);
    CU_add_test(suite, "Add integer+float", test_add_integer_float);
    CU_add_test(suite, "Add strings", test_add_strings);
    CU_add_test(suite, "Add vectors", test_add_vectors);
    CU_add_test(suite, "Add arrays", test_add_arrays);
    CU_add_test(suite, "Add with NULL", test_add_null);

    CU_add_test(suite, "Clone integer", test_clone_integer);
    CU_add_test(suite, "Clone float", test_clone_float);
    CU_add_test(suite, "Clone string", test_clone_string);
    CU_add_test(suite, "Clone vector3", test_clone_vector3);
    CU_add_test(suite, "Clone array", test_clone_array);
    CU_add_test(suite, "Clone NULL", test_clone_null);

    CU_add_test(suite, "Compare integers", test_compare_integers);
    CU_add_test(suite, "Compare integer and float", test_compare_integer_float);
    CU_add_test(suite, "Compare strings", test_compare_strings);
    CU_add_test(suite, "Compare vector3", test_compare_vector3);
    CU_add_test(suite, "Compare arrays", test_compare_arrays);
    CU_add_test(suite, "Compare NULL", test_compare_null);
    CU_add_test(suite, "Compare different types", test_compare_different_types);

}