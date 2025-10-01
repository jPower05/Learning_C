#include <CUnit/CUnit.h>
#include "zentra_object.h"
#include <stdlib.h>

// Your actual test case function
void test_new_zentra_integer(void) {
    zentra_obj_t* obj = new_zentra_integer(42);
    CU_ASSERT_PTR_NOT_NULL(obj);
    CU_ASSERT_EQUAL(obj->type, INTEGER);
    CU_ASSERT_EQUAL(obj->data.v_int, 42);
    free(obj);
}

void test_new_zentra_float(void) {
    zentra_obj_t* obj = new_zentra_float(3.14f);
    CU_ASSERT_PTR_NOT_NULL(obj);
    CU_ASSERT_EQUAL(obj->type, FLOAT);
    CU_ASSERT_DOUBLE_EQUAL(obj->data.v_float, 3.14f, 0.0001);
    free(obj);
}

// Test for string creation
void test_new_zentra_string(void) {
    const char *input = "hello world";
    zentra_obj_t *obj = new_zentra_string((char *)input);

    CU_ASSERT_PTR_NOT_NULL(obj);
    CU_ASSERT_EQUAL(obj->type, STRING);
    CU_ASSERT_PTR_NOT_NULL(obj->data.v_string);
    CU_ASSERT_STRING_EQUAL(obj->data.v_string, input);

    free(obj->data.v_string);
    free(obj);
}

#include <CUnit/CUnit.h>
#include "zentra_object.h"

void test_new_zentra_vector3(void) {
    // Create individual float components
    zentra_obj_t *x = new_zentra_float(1.0f);
    zentra_obj_t *y = new_zentra_float(2.0f);
    zentra_obj_t *z = new_zentra_float(3.0f);

    // Sanity check for component creation
    CU_ASSERT_PTR_NOT_NULL(x);
    CU_ASSERT_PTR_NOT_NULL(y);
    CU_ASSERT_PTR_NOT_NULL(z);

    // Create the vector object
    zentra_obj_t *vec_obj = new_zentra_vector3(x, y, z);
    CU_ASSERT_PTR_NOT_NULL(vec_obj);
    CU_ASSERT_EQUAL(vec_obj->type, VECTOR3);
    CU_ASSERT_PTR_NOT_NULL(vec_obj->data.v_vector3);

    // Check vector components
    zentra_vector3_t *vec = vec_obj->data.v_vector3;
    CU_ASSERT_PTR_EQUAL(vec->x, x);
    CU_ASSERT_PTR_EQUAL(vec->y, y);
    CU_ASSERT_PTR_EQUAL(vec->z, z);

    // Check component values
    CU_ASSERT_EQUAL(vec->x->type, FLOAT);
    CU_ASSERT_EQUAL(vec->y->type, FLOAT);
    CU_ASSERT_EQUAL(vec->z->type, FLOAT);

    CU_ASSERT_DOUBLE_EQUAL(vec->x->data.v_float, 1.0f, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(vec->y->data.v_float, 2.0f, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(vec->z->data.v_float, 3.0f, 0.0001);

    // Clean up memory
    free_zentra_object(vec_obj);  // Recursively frees all components
}

void test_new_zentra_array(){
    // Create a new array of size 3
    zentra_obj_t *arr_obj = new_zentra_array(3);
    CU_ASSERT_PTR_NOT_NULL(arr_obj);
    CU_ASSERT_EQUAL(arr_obj->type, ARRAY);

    zentra_array_t *arr = arr_obj->data.v_array;
    CU_ASSERT_PTR_NOT_NULL(arr);
    CU_ASSERT_EQUAL(arr->capacity, 3);
    CU_ASSERT_EQUAL(arr->size, 0);

    // Elements should be NULL (calloc'd)
    for (size_t i = 0; i < arr->capacity; ++i) {
        CU_ASSERT_PTR_NULL(arr->elements[i]);
    }

    // Manually insert values
    arr->elements[0] = new_zentra_integer(10);
    arr->elements[1] = new_zentra_float(2.5f);
    arr->size = 2;

    // Verify inserted values
    CU_ASSERT_EQUAL(arr->elements[0]->type, INTEGER);
    CU_ASSERT_EQUAL(arr->elements[0]->data.v_int, 10);

    CU_ASSERT_EQUAL(arr->elements[1]->type, FLOAT);
    CU_ASSERT_DOUBLE_EQUAL(arr->elements[1]->data.v_float, 2.5f, 0.0001);

    // Free all memory safely
    free_zentra_object(arr_obj);
}


// Registration function called from test_runner.c
void add_zentra_object_tests(void) {
    CU_pSuite suite = CU_add_suite("ZentraObjectTests", NULL, NULL);
    if (suite == NULL) return;

    CU_add_test(suite, "new_zentra_integer()", test_new_zentra_integer);
    CU_add_test(suite, "new_zentra_float()", test_new_zentra_float);
    CU_add_test(suite, "new_zentra_string()", test_new_zentra_string);
    CU_add_test(suite, "new_zentra_vector3()", test_new_zentra_vector3);
    CU_add_test(suite,"new_zentra_array()", test_new_zentra_array);

}


