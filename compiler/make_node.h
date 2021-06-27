#ifndef _MAKE_NODE_H
#define _MAKE_NODE_H
#include "node_t.h"

main_node_t * make_main_node();

variable_node_t * make_variable_node(char * name);

num_node_t * make_num_node(char * num);

string_node_t * make_string_node(char * string);

print_num_node_t * make_print_num_node(char * variable);

print_string_node_t * make_print_string_node(char * variable);

define_var_node_t * make_define_var_node(char * variable, node_t * value);

declare_var_node_t * make_declare_var_node(char * variable, node_t * value , variable_type type);

boolean_node_t * make_boolean_node(char * boolean);

if_node_t * make_if_node(node_t * condition , node_t * block);

while_node_t * make_while_node(node_t * condition , node_t * block);

node_t * test_node();

condition_state_node_t * make_condition_state_node(char * condition , node_t * left , node_t * right);

variable_comp_node_t * make_variable_comp_node( char * condition , node_t * left , node_t * right);

#endif