#ifndef _NODE_T_H
#define _NODE_T_H

typedef enum{
    MAIN_NODE,
    VARIABLE_NODE,
    NUM_NODE,
    STRING_NODE,
    BOOLEAN_NODE,
    PRINT_NUM_NODE,
    PRINT_STRING_NODE
}node_type;


typedef struct node_t{
  node_type type;
}node_t;

typedef struct main_node_t{
    node_type type;
    node_t *first;
    node_t *second;
}main_node_t;

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



#endif
