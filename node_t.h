#ifndef _NODE_T_H
#define _NODE_T_H

typedef enum{
    MAIN_NODE = 0,
    VARIABLE_NODE = 1,
    NUM_NODE = 2,
    STRING_NODE = 3,
    PRINT_NUM_NODE = 4,
    PRINT_STRING_NODE = 5
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

typedef struct print_num_node_t{
    node_type type;
    char *variable;
}print_num_node_t;

typedef struct print_string_node_t{
    node_type type;
    char *variable;
}print_string_node_t;



#endif
