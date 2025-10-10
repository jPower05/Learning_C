// #include <CUnit/CUnit.h>
// #include "../include/zentra_object.h"
// #include <stdlib.h>

// // Test: create array and verify basic set/get
// void test_array_set_get(void) {
//     zentra_obj_t *arr = new_zentra_array(5);
//     CU_ASSERT_PTR_NOT_NULL(arr);
//     CU_ASSERT_EQUAL(arr->type, ARRAY);

//     // Create integers
//     zentra_obj_t *val1 = new_zentra_integer(42);
//     zentra_obj_t *val2 = new_zentra_integer(99);

//     // Valid set/get
//     CU_ASSERT_TRUE(zentra_array_set(arr, 0, val1));
//     CU_ASSERT_TRUE(zentra_array_set(arr, 1, val2));

//     zentra_obj_t *res1 = zentra_array_get(arr, 0);
//     zentra_obj_t *res2 = zentra_array_get(arr, 1);

//     CU_ASSERT_PTR_NOT_NULL(res1);
//     CU_ASSERT_PTR_NOT_NULL(res2);
//     CU_ASSERT_EQUAL(res1->data.v_int, 42);
//     CU_ASSERT_EQUAL(res2->data.v_int, 99);

//     // Invalid indices
//     CU_ASSERT_FALSE(zentra_array_set(arr, 10, val1));   // out of capacity
//     CU_ASSERT_PTR_NULL(zentra_array_get(arr, 10));

//     // cleanup
//     free_zentra_object(arr);
//     // NOTE: don't free val1/val2 separately if array takes ownership
// }

// // Test: ensure array initialized with NULLs
// void test_array_default_values(void) {
//     zentra_obj_t *arr = new_zentra_array(3);
//     for (size_t i = 0; i < 3; i++) {
//         CU_ASSERT_PTR_NULL(zentra_array_get(arr, i));
//     }
//     free_zentra_object(arr);
// }

// // Test: overwrite element
// void test_array_overwrite(void) {
//     zentra_obj_t *arr = new_zentra_array(2);
//     zentra_obj_t *val1 = new_zentra_integer(7);
//     zentra_obj_t *val2 = new_zentra_integer(21);

//     CU_ASSERT_TRUE(zentra_array_set(arr, 0, val1));
//     CU_ASSERT_TRUE(zentra_array_set(arr, 0, val2)); // overwrite

//     zentra_obj_t *res = zentra_array_get(arr, 0);
//     CU_ASSERT_PTR_NOT_NULL(res);
//     CU_ASSERT_EQUAL(res->data.v_int, 21);

//     free_zentra_object(arr);
// }

// // Registration function called from test_runner.c
// void add_zentra_array_tests(void) {
//     CU_pSuite suite = CU_add_suite("ZentraArrayTests", NULL, NULL);
//     if (suite == NULL) return;

//     CU_add_test(suite, "zentra_array_get_set()", test_array_set_get);
//     CU_add_test(suite, "zentra_array_default_values()", test_array_default_values);
//     CU_add_test(suite, "zentra_array_overwrite()", test_array_overwrite);
    

// }