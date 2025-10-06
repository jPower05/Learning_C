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

    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(result);
}

void test_add_integer_float(void) {
    zentra_obj_t *a = new_zentra_integer(4);
    zentra_obj_t *b = new_zentra_float(2.5f);

    zentra_obj_t *result = add_zentra_object(a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == FLOAT);
    CU_ASSERT_DOUBLE_EQUAL(result->data.v_float, 6.5, 0.0001);

    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(result);
}

void test_add_strings(void) {
    zentra_obj_t *a = new_zentra_string("Hello ");
    zentra_obj_t *b = new_zentra_string("World");

    zentra_obj_t *result = add_zentra_object(a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == STRING);
    CU_ASSERT_STRING_EQUAL(result->data.v_string, "Hello World");

    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(result);
}

void test_add_vectors(void) {
    zentra_obj_t *x1 = new_zentra_integer(1);
    zentra_obj_t *y1 = new_zentra_integer(2);
    zentra_obj_t *z1 = new_zentra_integer(3);
    zentra_obj_t *v1 = new_zentra_vector3(x1, y1, z1);
    refcount_dec(x1); refcount_dec(y1); refcount_dec(z1);

    zentra_obj_t *x2 = new_zentra_integer(4);
    zentra_obj_t *y2 = new_zentra_integer(5);
    zentra_obj_t *z2 = new_zentra_integer(6);
    zentra_obj_t *v2 = new_zentra_vector3(x2, y2, z2);
    refcount_dec(x2); refcount_dec(y2); refcount_dec(z2);

    zentra_obj_t *result = add_zentra_object(v1, v2);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == VECTOR3);
    CU_ASSERT_TRUE(result->data.v_vector3->x->data.v_int == 5);
    CU_ASSERT_TRUE(result->data.v_vector3->y->data.v_int == 7);
    CU_ASSERT_TRUE(result->data.v_vector3->z->data.v_int == 9);

    refcount_dec(v1);
    refcount_dec(v2);
    refcount_dec(result);
}

void test_add_arrays(void) {

    zentra_obj_t *a = new_zentra_array(2);
    zentra_obj_t *a0 = new_zentra_integer(1);
    zentra_obj_t *a1 = new_zentra_integer(2);
    zentra_array_set(a, 0, a0);
    refcount_dec(a0);
    zentra_array_set(a, 1, a1);
    refcount_dec(a1);

    zentra_obj_t *b = new_zentra_array(2);
    zentra_obj_t *b0 = new_zentra_integer(3);
    zentra_obj_t *b1 = new_zentra_integer(4);
    zentra_array_set(b, 0, b0);
    refcount_dec(b0);
    zentra_array_set(b, 1, b1);
    refcount_dec(b1);

    zentra_obj_t *result = add_zentra_object(a, b);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_TRUE(result->type == ARRAY);
    CU_ASSERT_TRUE(result->data.v_array->capacity == 4);
    CU_ASSERT_TRUE(result->data.v_array->elements[0]->data.v_int == 1);
    CU_ASSERT_TRUE(result->data.v_array->elements[1]->data.v_int == 2);
    CU_ASSERT_TRUE(result->data.v_array->elements[2]->data.v_int == 3);
    CU_ASSERT_TRUE(result->data.v_array->elements[3]->data.v_int == 4);

    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(result);
}

void test_add_null(void) {
    zentra_obj_t *a = new_zentra_integer(1);
    zentra_obj_t *result = add_zentra_object(a, NULL);
    CU_ASSERT_PTR_NULL(result);
    refcount_dec(a);
}

void test_clone_integer(void) {
    zentra_obj_t *orig = new_zentra_integer(42);
    zentra_obj_t *copy = clone_zentra_object(orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));

    refcount_dec(orig);
    refcount_dec(copy);
}

void test_clone_float(void) {
    zentra_obj_t *orig = new_zentra_float(3.14f);
    zentra_obj_t *copy = clone_zentra_object(orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));

    refcount_dec(orig);
    refcount_dec(copy);
}

void test_clone_string(void) {
    zentra_obj_t *orig = new_zentra_string("Hello");
    zentra_obj_t *copy = clone_zentra_object(orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));
    CU_ASSERT_PTR_NOT_EQUAL(orig->data.v_string, copy->data.v_string); // deep copy

    refcount_dec(orig);
    refcount_dec(copy);
}

void test_clone_vector3(void) {
    zentra_obj_t *x = new_zentra_integer(1);
    zentra_obj_t *y = new_zentra_integer(2);
    zentra_obj_t *z = new_zentra_integer(3);
    zentra_obj_t *orig = new_zentra_vector3(x, y, z);
    refcount_dec(x); refcount_dec(y); refcount_dec(z);
    zentra_obj_t *copy = clone_zentra_object(orig);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(orig, copy));
    CU_ASSERT_PTR_NOT_EQUAL(orig->data.v_vector3, copy->data.v_vector3);

    refcount_dec(orig);
    refcount_dec(copy);
}

void test_clone_array(void) {
    zentra_obj_t *arr = new_zentra_array(2);
    zentra_obj_t *v0 = new_zentra_integer(10);
    zentra_obj_t *v1 = new_zentra_integer(20);
    zentra_array_set(arr, 0, v0);
    refcount_dec(v0);
    zentra_array_set(arr, 1, v1);
    refcount_dec(v1);

    zentra_obj_t *copy = clone_zentra_object(arr);

    CU_ASSERT_PTR_NOT_NULL(copy);
    CU_ASSERT_TRUE(compare_zentra_object(arr, copy));
    CU_ASSERT_PTR_NOT_EQUAL(arr->data.v_array, copy->data.v_array);
    CU_ASSERT_PTR_NOT_EQUAL(arr->data.v_array->elements[0], copy->data.v_array->elements[0]);
    CU_ASSERT_PTR_NOT_EQUAL(arr->data.v_array->elements[1], copy->data.v_array->elements[1]);

    refcount_dec(arr);
    refcount_dec(copy);
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

    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(c);
}

void test_compare_integer_float(void) {
    zentra_obj_t *a = new_zentra_integer(5);
    zentra_obj_t *b = new_zentra_float(5.0f);
    zentra_obj_t *c = new_zentra_float(5.1f);

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(c);
}

void test_compare_strings(void) {
    zentra_obj_t *a = new_zentra_string("Hello");
    zentra_obj_t *b = new_zentra_string("Hello");
    zentra_obj_t *c = new_zentra_string("World");

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(c);
}

void test_compare_vector3(void) {
    zentra_obj_t *x1 = new_zentra_integer(1);
    zentra_obj_t *y1 = new_zentra_integer(2);
    zentra_obj_t *z1 = new_zentra_integer(3);
    zentra_obj_t *v1 = new_zentra_vector3(x1, y1, z1);
    refcount_dec(x1); refcount_dec(y1); refcount_dec(z1);

    zentra_obj_t *x2 = new_zentra_integer(1);
    zentra_obj_t *y2 = new_zentra_integer(2);
    zentra_obj_t *z2 = new_zentra_integer(3);
    zentra_obj_t *v2 = new_zentra_vector3(x2, y2, z2);
    refcount_dec(x2); refcount_dec(y2); refcount_dec(z2);

    zentra_obj_t *x3 = new_zentra_integer(1);
    zentra_obj_t *y3 = new_zentra_integer(2);
    zentra_obj_t *z3 = new_zentra_integer(4);
    zentra_obj_t *v3 = new_zentra_vector3(x3, y3, z3);
    refcount_dec(x3); refcount_dec(y3); refcount_dec(z3);

    CU_ASSERT_TRUE(compare_zentra_object(v1, v2));
    CU_ASSERT_FALSE(compare_zentra_object(v1, v3));

    refcount_dec(v1);
    refcount_dec(v2);
    refcount_dec(v3);
}

void test_compare_arrays(void) {
    zentra_obj_t *a = new_zentra_array(2);
    zentra_obj_t *a0 = new_zentra_integer(10);
    zentra_obj_t *a1 = new_zentra_integer(20);
    zentra_array_set(a, 0, a0);
    refcount_dec(a0);
    zentra_array_set(a, 1, a1);
    refcount_dec(a1);

    zentra_obj_t *b = new_zentra_array(2);
    zentra_obj_t *b0 = new_zentra_integer(10);
    zentra_obj_t *b1 = new_zentra_integer(20);
    zentra_array_set(b, 0, b0);
    refcount_dec(b0);
    zentra_array_set(b, 1, b1);
    refcount_dec(b1);

    zentra_obj_t *c = new_zentra_array(2);
    zentra_obj_t *c0 = new_zentra_integer(10);
    zentra_obj_t *c1 = new_zentra_integer(21);
    zentra_array_set(c, 0, c0);
    refcount_dec(c0);
    zentra_array_set(c, 1, c1);
    refcount_dec(c1);

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));

    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(c);
}

void test_compare_null(void) {
    zentra_obj_t *a = NULL;
    zentra_obj_t *b = NULL;
    zentra_obj_t *c = new_zentra_integer(1);

    CU_ASSERT_TRUE(compare_zentra_object(a, b));
    CU_ASSERT_FALSE(compare_zentra_object(a, c));
    CU_ASSERT_FALSE(compare_zentra_object(c, b));

    refcount_dec(c);
}

void test_compare_different_types(void) {
    zentra_obj_t *i = new_zentra_integer(5);
    zentra_obj_t *f = new_zentra_float(5.0f);
    zentra_obj_t *s = new_zentra_string("5");

    CU_ASSERT_TRUE(compare_zentra_object(i, f)); // numeric match
    CU_ASSERT_FALSE(compare_zentra_object(i, s)); // different type
    CU_ASSERT_FALSE(compare_zentra_object(f, s));

    refcount_dec(i);
    refcount_dec(f);
    refcount_dec(s);
}

void test_free_integer(void) {
    zentra_obj_t *obj = new_zentra_integer(42);
    refcount_dec(obj);  // Should not crash
}

void test_free_float(void) {
    zentra_obj_t *obj = new_zentra_float(3.14f);
    refcount_dec(obj);  // Should not crash
}

void test_free_string(void) {
    zentra_obj_t *obj = new_zentra_string("Hello");
    refcount_dec(obj);  // Should free v_string and obj
}

void test_free_vector3(void) {
    zentra_obj_t *x = new_zentra_integer(1);
    zentra_obj_t *y = new_zentra_integer(2);
    zentra_obj_t *z = new_zentra_integer(3);
    zentra_obj_t *vec = new_zentra_vector3(x, y, z);
    refcount_dec(x);
    refcount_dec(y);
    refcount_dec(z);
    refcount_dec(vec);  // Should recursively free x, y, z and vec
}

void test_free_array(void) {
    zentra_obj_t *arr = new_zentra_array(2);
    zentra_obj_t *i = new_zentra_integer(10);
    zentra_obj_t *str = new_zentra_string("World");
    zentra_array_set(arr, 0, i);
    refcount_dec(i);
    zentra_array_set(arr, 1, str);
    refcount_dec(str);
    refcount_dec(arr);  // Should recursively free elements and array
}

void test_free_null(void) {
    zentra_obj_t *obj = NULL;
    refcount_dec(obj);  // Should handle NULL safely, no crash
}

void test_free_nested_structures(void) {
    // Array containing a vector3 and string
    zentra_obj_t *x = new_zentra_integer(1);
    zentra_obj_t *y = new_zentra_integer(2);
    zentra_obj_t *z = new_zentra_integer(3);
    zentra_obj_t *vec = new_zentra_vector3(x, y, z);
    refcount_dec(x);
    refcount_dec(y);
    refcount_dec(z);
    zentra_obj_t *str = new_zentra_string("Nested");
    zentra_obj_t *arr = new_zentra_array(2);
    zentra_array_set(arr, 0, vec);
    refcount_dec(vec);
    zentra_array_set(arr, 1, str);
    refcount_dec(str);
    refcount_dec(arr);  // Should free everything recursively
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