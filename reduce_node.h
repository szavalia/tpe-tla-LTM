#ifndef _REDUCE_NODE_H_
#define _REDUCE_NODE_H_

#include "node_t.h"
#include "variables.h"
#include <stdio.h>

char * reduce_main_node(node_t *n);

char * reduce_variable_node(node_t *n);

char * reduce_num_node(node_t *n);

char * reduce_string_node(node_t *n);

char * reduce_boolean_node(node_t *n);

char * reduce_print_num_node(node_t *n);

char * reduce_print_string_node(node_t *n);

//Punteros a las funciones de reducción
//Están en el mismo orden que el enum en node_t.
char * (*reduction_functions[])(node_t *) = {
    reduce_main_node,
    reduce_variable_node,
    reduce_num_node,
    reduce_string_node,
    reduce_boolean_node,
    reduce_print_num_node,
    reduce_print_string_node
};

#endif