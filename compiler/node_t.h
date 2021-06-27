#ifndef _NODE_T_H
#define _NODE_T_H
#include "variables.h"

typedef enum{
    MAIN_NODE,
    VARIABLE_NODE,
    NUM_NODE,
    STRING_NODE,
    BOOLEAN_NODE,
    PRINT_NUM_NODE,
    PRINT_STRING_NODE,
    DECLARE_VAR_NODE,
    DEFINE_VAR_NODE,
    EXPRESSION_NODE
}node_type;

typedef enum{
    OP_SUM,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_NONE
}operation_type;


typedef struct node_t{
  node_type type;
}node_t;

typedef struct main_node_t{
    node_type type;
    node_t *first;
    node_t *second;
}main_node_t;


typedef struct declare_var_node_t{
    node_type type;
    char * name;
    variable_type var_type;
    node_t *value;
}declare_var_node_t;

typedef struct define_var_node_t{
    node_type type;
    char * name;
    node_t *value;
}define_var_node_t;


typedef struct variable_node_t{
    node_type type;
    char * name;
    node_t *value;
}variable_node_t;

typedef struct num_node_t{
    node_type type;
    char * number;
}num_node_t;

typedef struct string_node_t{
    node_type type;
    char * string;
}string_node_t;

typedef struct boolean_node_t{
    node_type type;
    char * boolean;
}boolean_node_t;

typedef struct print_num_node_t{
    node_type type;
    char *variable;
}print_num_node_t;

typedef struct print_string_node_t{
    node_type type;
    char *variable;
}print_string_node_t;

typedef struct expression_node_t{
    node_type type;
    node_t * left;
    node_t * right;
    operation_type operation;
}expression_node_t;

#endif
