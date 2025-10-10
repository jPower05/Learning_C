#pragma once
#include "../include/zentra_stack.h"

// Forward declaration to break circular include dependency
typedef struct ZentraObject zentra_obj_t;

typedef struct ZentraVirtualMachine{
    zentra_stack_t *frames;
    zentra_stack_t *objects;
}zentra_vm_t;

typedef struct ZentraFrame{
    zentra_stack_t *references;
} zentra_frame_t;


zentra_vm_t *new_zentra_vm();
void free_zentra_vm(zentra_vm_t *vm);

/* wrapper function for preventing pushing wrong data onto our stacks*/
void push_zentra_frame_onto_vm(zentra_vm_t *vm, zentra_frame_t *frame);

zentra_frame_t *new_zentra_frame_for_vm(zentra_vm_t *vm);

void free_zentra_frame(zentra_frame_t *frame);

void push_zentra_object_onto_vm_objects(zentra_vm_t *vm, zentra_obj_t *obj);

void push_zentra_object_onto_vm_frames(zentra_frame_t *frame, zentra_obj_t *obj);

void mark(zentra_vm_t *vm);

void trace(zentra_vm_t *vm);

void trace_blacken_object(zentra_stack_t *gray_objects, zentra_obj_t *obj);

void trace_mark_object(zentra_stack_t *gray_objects, zentra_obj_t *obj);

void sweep(zentra_vm_t *vm);

void collect_garbage_zentra_vm(zentra_vm_t *vm);



