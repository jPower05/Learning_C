#include "../include/zentra_arena_allocator.h"

zentra_arena_t *zentra_arena_create(size_t size){
    zentra_arena_t *arena = malloc(sizeof(zentra_arena_t));
    if (!arena) return NULL;

    arena->base = malloc(size);
    if (!arena->base) {
        free(arena);
        return NULL;
    }

    arena->size = size;
    arena->used = 0;
    return arena;
}
void *zentra_arena_alloc(zentra_arena_t *arena, size_t bytes){
    if (!arena || arena->used + bytes > arena->size) {
        return NULL; // Not enough space
    }
    void *ptr = arena->base + arena->used;
    arena->used += bytes;
    return ptr;
}
void zentra_arena_reset(zentra_arena_t *arena){
    if (arena) {
        arena->used = 0;
    }
}
void zentra_arena_destroy(zentra_arena_t *arena){
    if (arena) {
        free(arena->base);
        free(arena);
    }
}