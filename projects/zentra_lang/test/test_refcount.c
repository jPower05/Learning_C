#include <CUnit/CUnit.h>
#include "../src/zentra_object.h"
#include <stdlib.h>

void test_refcount_basic(void) {
    zentra_obj_t *obj = new_zentra_integer(123);
    CU_ASSERT_PTR_NOT_NULL(obj);
    CU_ASSERT_EQUAL(obj->refcount, 1);

    refcount_inc(obj);
    CU_ASSERT_EQUAL(obj->refcount, 2);

    refcount_dec(obj);
    CU_ASSERT_EQUAL(obj->refcount, 1);

    refcount_dec(obj); // Should free the object
    // Can't check obj->refcount here, as obj is freed
}

void test_refcount_free_on_zero(void) {
    zentra_obj_t *obj = new_zentra_integer(42);
    CU_ASSERT_PTR_NOT_NULL(obj);
    CU_ASSERT_EQUAL(obj->refcount, 1);
    refcount_dec(obj); // Should free the object
    // No crash = pass
}

void add_refcount_tests(void) {
    CU_pSuite suite = CU_add_suite("RefcountTests", NULL, NULL);
    if (suite == NULL) return;
    CU_add_test(suite, "refcount_basic", test_refcount_basic);
    CU_add_test(suite, "refcount_free_on_zero", test_refcount_free_on_zero);
}
