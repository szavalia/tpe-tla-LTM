#ifndef _MAKE_NODE_H
#define _MAKE_NODE_H
#include "node_t.h"

node_t * make_main_node();

node_t * make_variable_node(char * name);

node_t * make_num_node(char * num);

node_t * make_string_node(char * string);

node_t * make_print_num_node(char * variable);

node_t * make_print_string_node(node_t * variable);

node_t * make_define_var_node(char * variable, node_t * value);

node_t * make_declare_var_node(char * variable, node_t * value , variable_type type);

node_t * make_boolean_node(char * boolean);

node_t * make_if_node(node_t * condition , node_t * block);

node_t * make_while_node(node_t * condition , node_t * block);

node_t * make_expression_node(node_t * left, node_t * right, operation_type type);

node_t * test_node();

node_t * make_condition_state_node(char * condition , node_t * left , node_t * right);

node_t * make_variable_comp_node( char * condition , node_t * left , node_t * right);

#endif