#include "../include/zentra_vm.h"
#include "../include/zentra_object.h"   // need the contents of object here, only need the declaration in the header
#define DEFAULT_STACK_SIZE 8

zentra_vm_t *new_zentra_vm(){
    zentra_vm_t *vm = malloc(sizeof(zentra_vm_t));
    if(!vm) {
        return NULL;
    }
    vm->frames = new_zentra_stack(DEFAULT_STACK_SIZE);
    if(!vm->frames){
        free(vm);
        return NULL;
    }
    vm->objects = new_zentra_stack(DEFAULT_STACK_SIZE);
    if(!vm->objects){
        free(vm);
        return NULL;
    }
    return vm;
}
void free_zentra_vm(zentra_vm_t *vm){
    if (!vm) return;

    // 1. Free frames (if allocated)
    if (vm->frames) {
        for (size_t i = 0; i < vm->frames->count; i++) {
            zentra_frame_t *frame = (zentra_frame_t *)vm->frames->elements[i];
            free_zentra_frame(frame);
        }
        free_zentra_stack(vm->frames);
    }

    // 2. Free VM-owned objects (if allocated)
    if (vm->objects) {
        for (size_t i = 0; i < vm->objects->count; i++) {
            zentra_obj_t *obj = (zentra_obj_t *)vm->objects->elements[i];
            free_zentra_object(obj);
        }
        free_zentra_stack(vm->objects);
    }

    // 3. Finally free the VM structure itself
    free(vm);
}

/* wrapper function for preventing pushing wrong data onto our stacks*/
void push_zentra_frame_onto_vm(zentra_vm_t *vm, zentra_frame_t *frame){
    if(!vm || !frame){
        return;
    }
    push_zentra_stack(vm->frames, (void *)frame);
}

zentra_frame_t *new_zentra_frame_for_vm(zentra_vm_t *vm){
    if(!vm){
        return NULL;
    }
    zentra_frame_t *frame = malloc(sizeof(zentra_frame_t));
    frame->references = new_zentra_stack(DEFAULT_STACK_SIZE);
    if(!frame->references){
        free(frame);
        return NULL;
    }
    push_zentra_frame_onto_vm(vm, frame);   // using wrapper function for type safety
    return frame;
}

void free_zentra_frame(zentra_frame_t *frame){
    if(!frame){
        return;
    }
    free_zentra_stack(frame->references);
    free(frame);
}

void push_zentra_object_onto_vm_objects(zentra_vm_t *vm, zentra_obj_t *obj){
    if(!vm || !obj){
        return;
    }
    push_zentra_stack(vm->objects, (void *)obj);    // onto objects stack
}

void push_zentra_object_onto_vm_frames(zentra_frame_t *frame, zentra_obj_t *obj){
    if(!frame || !obj){
        return;
    }
    push_zentra_stack(frame->references, (void *)obj);
}

void mark(zentra_vm_t *vm){
    if(!vm){
        return;
    }
    for(size_t i = 0 ; i < vm->frames->count; i++){
        zentra_frame_t *frame = vm->frames->elements[i];
        for(size_t j = 0; j < frame->references->count; j++){
            zentra_obj_t *obj = frame->references->elements[j];
            obj->is_marked = true;
        }
    }
}

void trace(zentra_vm_t *vm){
    if(!vm){
        return;
    }
    zentra_stack_t *gray_objects = new_zentra_stack(DEFAULT_STACK_SIZE);
    if(!gray_objects){
        return;
    }
    
    for (size_t i = 0; i < vm->objects->count; i++) {
        zentra_obj_t *obj = (zentra_obj_t*)vm->objects->elements[i];
        if (obj && obj->is_marked) {
            push_zentra_stack(gray_objects, obj);
        }
    }

    while (gray_objects->count > 0) {
        zentra_obj_t *obj = (zentra_obj_t*)pop_zentra_stack(gray_objects);
        if (!obj) continue;
        trace_blacken_object(gray_objects, obj);
    }

    free_zentra_stack(gray_objects);

}

void trace_blacken_object(zentra_stack_t *gray_objects, zentra_obj_t *obj){
    if(!obj){
        return;
    }
    switch(obj->type){
        case INTEGER:
        case FLOAT:
        case STRING:
            return;
        case VECTOR3:{
            if (obj->data.v_vector3) {
                trace_mark_object(gray_objects, obj->data.v_vector3->x);
                trace_mark_object(gray_objects, obj->data.v_vector3->y);
                trace_mark_object(gray_objects, obj->data.v_vector3->z);
            }
            return;
        }
        case ARRAY:{
            zentra_array_t *arr = obj->data.v_array;
            if (!arr) return;
            for (size_t i = 0; i < arr->capacity; i++) {
                zentra_obj_t *element = arr->elements[i];
                trace_mark_object(gray_objects, element);
            }
            return;
        }
        default:{
            return;
        }
    }
}

void trace_mark_object(zentra_stack_t *gray_objects, zentra_obj_t *obj){
    if(!obj || obj->is_marked){
        return;
    }
    obj->is_marked = true;
    push_zentra_stack(gray_objects, obj);
}

void sweep(zentra_vm_t *vm){
    if(!vm){
        return;
    }
    for(size_t i = 0; i < vm->objects->count; i++){
        zentra_obj_t *obj = vm->objects->elements[i];
        if(!obj){
            continue;
        }
        if(obj->is_marked){
            obj->is_marked = false;
        }else{
            free_zentra_object(obj);
            vm->objects->elements[i] = NULL;
        }
    }

    remove_nulls_from_zentra_stack(vm->objects);
}

void collect_garbage_zentra_vm(zentra_vm_t *vm){
    mark(vm);
    trace(vm);
    sweep(vm);
}





