#include <CUnit/CUnit.h>
#include "../src/zentra_object.h"
#include <stdlib.h>

void test_add_integers(void) {
    zentra_obj_t *a = new_zentra_integer(5);
    zentra_obj_t *b = new_zentra_integer(3);

    zentra_obj_t *result = add_zentra_object(a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == INTEGER);
    CU_ASSERT_TRUE(result->data.v_int == 8);

    free_zentra_object(a);
    free_zentra_object(b);
    free_zentra_object(result);
}

void test_add_integer_float(void) {
    zentra_obj_t *a = new_zentra_integer(4);
    zentra_obj_t *b = new_zentra_float(2.5f);

    zentra_obj_t *result = add_zentra_object(a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == FLOAT);
    CU_ASSERT_DOUBLE_EQUAL(result->data.v_float, 6.5, 0.0001);

    free_zentra_object(a);
    free_zentra_object(b);
    free_zentra_object(result);
}

void test_add_strings(void) {
    zentra_obj_t *a = new_zentra_string("Hello ");
    zentra_obj_t *b = new_zentra_string("World");

    zentra_obj_t *result = add_zentra_object(a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == STRING);
    CU_ASSERT_STRING_EQUAL(result->data.v_string, "Hello World");

    free_zentra_object(a);
    free_zentra_object(b);
    free_zentra_object(result);
}

void test_add_vectors(void) {
    zentra_obj_t *x1 = new_zentra_integer(1);
    zentra_obj_t *y1 = new_zentra_integer(2);
    zentra_obj_t *z1 = new_zentra_integer(3);
    zentra_obj_t *v1 = new_zentra_vector3(x1, y1, z1);

    zentra_obj_t *x2 = new_zentra_integer(4);
    zentra_obj_t *y2 = new_zentra_integer(5);
    zentra_obj_t *z2 = new_zentra_integer(6);
    zentra_obj_t *v2 = new_zentra_vector3(x2, y2, z2);

    zentra_obj_t *result = add_zentra_object(v1, v2);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == VECTOR3);
    CU_ASSERT_TRUE(result->data.v_vector3->x->data.v_int == 5);
    CU_ASSERT_TRUE(result->data.v_vector3->y->data.v_int == 7);
    CU_ASSERT_TRUE(result->data.v_vector3->z->data.v_int == 9);

    free_zentra_object(v1);
    free_zentra_object(v2);
    free_zentra_object(result);
}

void test_add_arrays(void) {
    zentra_obj_t *a = new_zentra_array(2);
    zentra_array_set(a, 0, new_zentra_integer(1));
    zentra_array_set(a, 1, new_zentra_integer(2));

    zentra_obj_t *b = new_zentra_array(2);
    zentra_array_set(b, 0, new_zentra_integer(3));
    zentra_array_set(b, 1, new_zentra_integer(4));

    zentra_obj_t *result = add_zentra_object(a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == ARRAY);
    CU_ASSERT_TRUE(result->data.v_array->capacity == 4);
    CU_ASSERT_TRUE(result->data.v_array->elements[0]->data.v_int == 1);
    CU_ASSERT_TRUE(result->data.v_array->elements[1]->data.v_int == 2);
    CU_ASSERT_TRUE(result->data.v_array->elements[2]->data.v_int == 3);
    CU_ASSERT_TRUE(result->data.v_array->elements[3]->data.v_int == 4);

    free_zentra_object(a);
    free_zentra_object(b);
    free_zentra_object(result);
}

void test_add_null(void) {
    zentra_obj_t *a = new_zentra_integer(1);
    zentra_obj_t *result = add_zentra_object(a, NULL);
    CU_ASSERT_PTR_NULL(result);
    free_zentra_object(a);
}

void test_clone_integer(void) {
    zentra_obj_t *orig = new_zentra_integer(42);
    zentra_obj_t *copy = clone_zentra_object(orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));

    free_zentra_object(orig);
    free_zentra_object(copy);
}

void test_clone_float(void) {
    zentra_obj_t *orig = new_zentra_float(3.14f);
    zentra_obj_t *copy = clone_zentra_object(orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));

    free_zentra_object(orig);
    free_zentra_object(copy);
}

void test_clone_string(void) {
    zentra_obj_t *orig = new_zentra_string("Hello");
    zentra_obj_t *copy = clone_zentra_object(orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));
    CU_ASSERT_PTR_NOT_EQUAL(orig->data.v_string, copy->data.v_string); // deep copy

    free_zentra_object(orig);
    free_zentra_object(copy);
}

void test_clone_vector3(void) {
    zentra_obj_t *x = new_zentra_integer(1);
    zentra_obj_t *y = new_zentra_integer(2);
    zentra_obj_t *z = new_zentra_integer(3);
    zentra_obj_t *orig = new_zentra_vector3(x, y, z);
    zentra_obj_t *copy = clone_zentra_object(orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));
    CU_ASSERT_PTR_NOT_EQUAL(orig->data.v_vector3, copy->data.v_vector3);

    free_zentra_object(orig);
    free_zentra_object(copy);
}

void test_clone_array(void) {
    zentra_obj_t *arr = new_zentra_array(2);
    zentra_array_set(arr, 0, new_zentra_integer(10));
    zentra_array_set(arr, 1, new_zentra_integer(20));

    zentra_obj_t *copy = clone_zentra_object(arr);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(arr, copy));
    CU_ASSERT_PTR_NOT_EQUAL(arr->data.v_array, copy->data.v_array);
    CU_ASSERT_PTR_NOT_EQUAL(arr->data.v_array->elements[0], copy->data.v_array->elements[0]);
    CU_ASSERT_PTR_NOT_EQUAL(arr->data.v_array->elements[1], copy->data.v_array->elements[1]);

    free_zentra_object(arr);
    free_zentra_object(copy);
}

void test_clone_null(void) {
    zentra_obj_t *copy = clone_zentra_object(NULL);
    CU_ASSERT_PTR_NULL(copy);
}

void test_compare_integers(void) {
    zentra_obj_t *a = new_zentra_integer(5);
    zentra_obj_t *b = new_zentra_integer(5);
    zentra_obj_t *c = new_zentra_integer(7);

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    free_zentra_object(a);
    free_zentra_object(b);
    free_zentra_object(c);
}

void test_compare_integer_float(void) {
    zentra_obj_t *a = new_zentra_integer(5);
    zentra_obj_t *b = new_zentra_float(5.0f);
    zentra_obj_t *c = new_zentra_float(5.1f);

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    free_zentra_object(a);
    free_zentra_object(b);
    free_zentra_object(c);
}

void test_compare_strings(void) {
    zentra_obj_t *a = new_zentra_string("Hello");
    zentra_obj_t *b = new_zentra_string("Hello");
    zentra_obj_t *c = new_zentra_string("World");

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    free_zentra_object(a);
    free_zentra_object(b);
    free_zentra_object(c);
}

void test_compare_vector3(void) {
    zentra_obj_t *v1 = new_zentra_vector3(
        new_zentra_integer(1), new_zentra_integer(2), new_zentra_integer(3)
    );
    zentra_obj_t *v2 = new_zentra_vector3(
        new_zentra_integer(1), new_zentra_integer(2), new_zentra_integer(3)
    );
    zentra_obj_t *v3 = new_zentra_vector3(
        new_zentra_integer(1), new_zentra_integer(2), new_zentra_integer(4)
    );

    CU_ASSERT_TRUE(compare_zentra_object(v1, v2));
    CU_ASSERT_FALSE(compare_zentra_object(v1, v3));

    free_zentra_object(v1);
    free_zentra_object(v2);
    free_zentra_object(v3);
}

void test_compare_arrays(void) {
    zentra_obj_t *a = new_zentra_array(2);
    zentra_array_set(a, 0, new_zentra_integer(10));
    zentra_array_set(a, 1, new_zentra_integer(20));

    zentra_obj_t *b = new_zentra_array(2);
    zentra_array_set(b, 0, new_zentra_integer(10));
    zentra_array_set(b, 1, new_zentra_integer(20));

    zentra_obj_t *c = new_zentra_array(2);
    zentra_array_set(c, 0, new_zentra_integer(10));
    zentra_array_set(c, 1, new_zentra_integer(21));

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    free_zentra_object(a);
    free_zentra_object(b);
    free_zentra_object(c);
}

void test_compare_null(void) {
    zentra_obj_t *a = NULL;
    zentra_obj_t *b = NULL;
    zentra_obj_t *c = new_zentra_integer(1);

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));
    CU_ASSERT_FALSE(compare_zentra_object(c, b));

    free_zentra_object(c);
}

void test_compare_different_types(void) {
    zentra_obj_t *i = new_zentra_integer(5);
    zentra_obj_t *f = new_zentra_float(5.0f);
    zentra_obj_t *s = new_zentra_string("5");

    CU_ASSERT_TRUE(compare_zentra_object(i, f)); // numeric match
    CU_ASSERT_FALSE(compare_zentra_object(i, s)); // different type
    CU_ASSERT_FALSE(compare_zentra_object(f, s));

    free_zentra_object(i);
    free_zentra_object(f);
    free_zentra_object(s);
}

void test_free_integer(void) {
    zentra_obj_t *obj = new_zentra_integer(42);
    free_zentra_object(obj);  // Should not crash
}

void test_free_float(void) {
    zentra_obj_t *obj = new_zentra_float(3.14f);
    free_zentra_object(obj);  // Should not crash
}

void test_free_string(void) {
    zentra_obj_t *obj = new_zentra_string("Hello");
    free_zentra_object(obj);  // Should free v_string and obj
}

void test_free_vector3(void) {
    zentra_obj_t *x = new_zentra_integer(1);
    zentra_obj_t *y = new_zentra_integer(2);
    zentra_obj_t *z = new_zentra_integer(3);
    zentra_obj_t *vec = new_zentra_vector3(x, y, z);
    free_zentra_object(vec);  // Should recursively free x, y, z and vec
}

void test_free_array(void) {
    zentra_obj_t *arr = new_zentra_array(2);
    zentra_array_set(arr, 0, new_zentra_integer(10));
    zentra_array_set(arr, 1, new_zentra_string("World"));
    free_zentra_object(arr);  // Should recursively free elements and array
}

void test_free_null(void) {
    zentra_obj_t *obj = NULL;
    free_zentra_object(obj);  // Should handle NULL safely, no crash
}

void test_free_nested_structures(void) {
    // Array containing a vector3 and string
    zentra_obj_t *vec = new_zentra_vector3(
        new_zentra_integer(1),
        new_zentra_integer(2),
        new_zentra_integer(3)
    );
    zentra_obj_t *str = new_zentra_string("Nested");
    
    zentra_obj_t *arr = new_zentra_array(2);
    zentra_array_set(arr, 0, vec);
    zentra_array_set(arr, 1, str);

    free_zentra_object(arr);  // Should free everything recursively
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

    CU_add_test(suite, "Free integer", test_free_integer);
    CU_add_test(suite, "Free float", test_free_float);
    CU_add_test(suite, "Free string", test_free_string);
    CU_add_test(suite, "Free vector3", test_free_vector3);
    CU_add_test(suite, "Free array", test_free_array);
    CU_add_test(suite, "Free NULL", test_free_null);
    CU_add_test(suite, "Free nested structures", test_free_nested_structures);

}