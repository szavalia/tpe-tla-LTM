#ifndef _NODE_T_H
#define _NODE_T_H
#include "variables.h"

typedef enum{
    MAIN_NODE = 0,
    VARIABLE_NODE = 1,
    NUM_NODE = 2,
    STRING_NODE = 3,
    BOOLEAN_NODE = 4,
    PRINT_NUM_NODE = 5 ,
    PRINT_STRING_NODE = 6,
    DECLARE_VAR_NODE = 7,
    DEFINE_VAR_NODE = 8,
    IF_NODE = 9,
    WHILE_NODE = 10,
    CONDITION_STATE_NODE = 11,
    VARIABLE_COMP_NODE = 12,
    EXPRESSION_NODE = 13
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
    node_t* variable;
}print_string_node_t;

typedef struct while_node_t{
    node_type type;
    node_t * condition;
    node_t * block;
}while_node_t;

typedef struct if_node_t{
    node_type type;
    node_t * condition;
    node_t * block;
}if_node_t;

typedef struct condition_state_node_t{
    node_type type;
    char condition[2];
    node_t * left;
    node_t * right;
}condition_state_node_t;

typedef struct variable_comp_node_t{
    node_type type;
    char condition[3];
    node_t * left;
    node_t * right;
}variable_comp_node_t;

typedef struct expression_node_t{
    node_type type;
    node_t * left;
    node_t * right;
    operation_type operation;
}expression_node_t;

#endif
