#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node_dp node_dp;

node_dp *node_create(int value);
void *node_append(node_dp **head_ref, int value);
void node_print(node_dp ** head_ref);
node_dp *node_delete(node_dp **head_ref, int value);
void free(node_dp **head_ref);