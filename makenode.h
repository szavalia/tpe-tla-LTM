#include "node_t.h"

/*
typedef enum{
    MAIN_NODE = 0,
    VARIABLE_NODE = 1,
    NUM_NODE = 2,
    STRING_NODE = 3,
    PRINT_NUM_NODE = 4,
    PRINT_STRING_NODE = 5
}node_type;
*/

main_node_t * make_main_node();

variable_node_t * make_variable_node(char * name);

num_node_t * make_num_node(char * num);

string_node_t * make_string_node(char * string);

print_num_node_t * make_print_num_node(char * variable);

print_string_node_t * make_print_string_node(char * variable);
