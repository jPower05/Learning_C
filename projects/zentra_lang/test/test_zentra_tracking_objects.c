#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../include/zentra_object.h"
#include "../include/zentra_vm.h"

void test_new_zentra_object_tracking(void){
    zentra_vm_t *vm = new_zentra_vm();
    zentra_obj_t* obj = new_zentra_integer(vm, 42);
    CU_ASSERT_PTR_NOT_NULL(obj);
    CU_ASSERT_EQUAL(obj->type, INTEGER);
    CU_ASSERT_EQUAL(obj->data.v_int, 42);
    CU_ASSERT_PTR_EQUAL(vm->objects->elements[0], obj);
    free_zentra_vm(vm);
}

void test_free_zentra_vm(void) {
    // // 1. Create a VM instance
    // zentra_vm_t *vm = new_zentra_vm();
    // CU_ASSERT_PTR_NOT_NULL(vm);
    // CU_ASSERT_PTR_NOT_NULL(vm->frames);
    // CU_ASSERT_PTR_NOT_NULL(vm->objects);

    // // 2. Create a frame and push onto VM
    // zentra_frame_t *frame = new_zentra_frame_for_vm(vm);
    // CU_ASSERT_PTR_NOT_NULL(frame);
    // CU_ASSERT_EQUAL(vm->frames->count, 1);

    // // 3. Create and track an object
    // zentra_obj_t *obj = new_zentra_integer(vm, 123);
    // push_zentra_object_onto_vm(vm, obj);
    // CU_ASSERT_EQUAL(vm->objects->count, 1);
    // CU_ASSERT_PTR_EQUAL(vm->objects->elements[0], obj);

    // // 4. Free the VM (should recursively free everything)
    // free_zentra_vm(vm);

    // // ✅ No crash = pass.  
    // // Memory correctness is verified via Valgrind or ASan externally.
}

void test_mark_and_sweep_gc(void) {
    // 1. Create VM
    zentra_vm_t *vm = new_zentra_vm();
    CU_ASSERT_PTR_NOT_NULL(vm);

    // 2. Create objects
    zentra_obj_t *a = new_zentra_integer(vm, 1);  // Will be kept
    zentra_obj_t *b = new_zentra_integer(vm, 2);  // Will be collected
    zentra_obj_t *c = new_zentra_integer(vm, 3);  // Will be kept

    CU_ASSERT_PTR_NOT_NULL(a);
    CU_ASSERT_PTR_NOT_NULL(b);
    CU_ASSERT_PTR_NOT_NULL(c);

    // 3. Create a frame and push references
    zentra_frame_t *frame = new_zentra_frame_for_vm(vm);
    push_zentra_object_onto_vm_frames(frame, a);
    push_zentra_object_onto_vm_frames(frame, c);

    CU_ASSERT_EQUAL(vm->frames->count, 1);
    CU_ASSERT_EQUAL(frame->references->count, 2);
    CU_ASSERT_EQUAL(vm->objects->count, 3);

    // 4. Collect garbage
    collect_garbage_zentra_vm(vm);

    // 5. Check counts: b should be removed
    CU_ASSERT_EQUAL(vm->objects->count, 2);

    // 6. Check that remaining objects are correct
    CU_ASSERT_PTR_EQUAL(vm->objects->elements[0], a);
    CU_ASSERT_PTR_EQUAL(vm->objects->elements[1], c);

    // 7. Cleanup VM (should free all remaining objects and frames)
    free_zentra_vm(vm);
}

void test_gc_collects_unreachable_array(void) {
    zentra_vm_t *vm = new_zentra_vm();
    CU_ASSERT_PTR_NOT_NULL(vm);

    // Create array and elements
    zentra_obj_t *a = new_zentra_integer(vm, 10);
    zentra_obj_t *b = new_zentra_integer(vm, 20);
    zentra_obj_t *arr = new_zentra_array(vm, 2);
    zentra_array_set(arr, 0, a);
    zentra_array_set(arr, 1, b);

    CU_ASSERT_PTR_NOT_NULL(arr);
    CU_ASSERT_PTR_NOT_NULL(a);
    CU_ASSERT_PTR_NOT_NULL(b);

    // Only a is root
    zentra_frame_t *frame = new_zentra_frame_for_vm(vm);
    push_zentra_object_onto_vm_frames(frame, a);

    // b and arr are unreachable → should be collected
    collect_garbage_zentra_vm(vm);

    // a survives
    bool a_found = false;
    bool b_found = false;
    bool arr_found = false;
    for (size_t i = 0; i < vm->objects->count; i++) {
        zentra_obj_t *o = vm->objects->elements[i];
        if (o == a) a_found = true;
        if (o == b) b_found = true;
        if (o == arr) arr_found = true;
    }

    CU_ASSERT_TRUE(a_found);
    CU_ASSERT_FALSE(b_found);
    CU_ASSERT_FALSE(arr_found);

    free_zentra_vm(vm);
}

void test_gc_collects_unreachable_vector3(void) {
    zentra_vm_t *vm = new_zentra_vm();
    CU_ASSERT_PTR_NOT_NULL(vm);

    // Create numeric components
    zentra_obj_t *x = new_zentra_integer(vm, 1);
    zentra_obj_t *y = new_zentra_integer(vm, 2);
    zentra_obj_t *z = new_zentra_integer(vm, 3);
    CU_ASSERT_PTR_NOT_NULL(x);
    CU_ASSERT_PTR_NOT_NULL(y);
    CU_ASSERT_PTR_NOT_NULL(z);

    // Make them roots so they survive GC
    zentra_frame_t *frame = new_zentra_frame_for_vm(vm);
    push_zentra_object_onto_vm_frames(frame, x);
    push_zentra_object_onto_vm_frames(frame, y);
    push_zentra_object_onto_vm_frames(frame, z);

    // Create a vector3 object that is NOT referenced by any frame → should be collected
    zentra_obj_t *vec = new_zentra_vector3(vm, x, y, z);
    CU_ASSERT_PTR_NOT_NULL(vec);

    // Run GC
    collect_garbage_zentra_vm(vm);

    // Vector3 should be gone
    bool vec_found = false;
    for (size_t i = 0; i < vm->objects->count; i++) {
        if (vm->objects->elements[i] == vec) vec_found = true;
    }
    CU_ASSERT_FALSE(vec_found);

    // Components should survive
    bool x_found = false, y_found = false, z_found = false;
    for (size_t i = 0; i < vm->objects->count; i++) {
        zentra_obj_t *o = vm->objects->elements[i];
        if (o == x) x_found = true;
        if (o == y) y_found = true;
        if (o == z) z_found = true;
    }
    CU_ASSERT_TRUE(x_found && y_found && z_found);

    free_zentra_vm(vm);
}

// Registration function called from test_runner.c
void add_zentra_tracking_object_tests(void) {
    CU_pSuite suite = CU_add_suite("ZentraObjectTrackingTests", NULL, NULL);
    if (suite == NULL) return;

    CU_add_test(suite, "new_zentra_object_tracking()", test_new_zentra_object_tracking);
    //CU_add_test(suite, "test_free_zentra_vm", test_free_zentra_vm);
    CU_add_test(suite, "mark_and_sweep_gc", test_mark_and_sweep_gc);
    CU_add_test(suite, "GC collects unreachable array", test_gc_collects_unreachable_array);
    CU_add_test(suite, "GC collects unreachable vector3", test_gc_collects_unreachable_vector3);
}