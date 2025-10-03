#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// Declare test registration functions defined in your other test files
// These functions will add test cases to a given suite
void add_zentra_object_tests(void);
void add_zentra_array_tests(void);
void add_zentra_object_operators_test(void);

int main(void) {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add all test suites and test cases
    add_zentra_object_tests();   // from test_zentra_object.c
    add_zentra_array_tests();    // from test_zentra_array.c
    add_zentra_object_operators_test(); //from test_zentra_object_operators.c

    // Run tests in basic mode (console output)
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Clean up
    CU_cleanup_registry();
    return CU_get_error();
}