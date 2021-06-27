#include "make_node.h"
#include "node_t.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

main_node_t * make_main_node( node_t * first , node_t * second){
    main_node_t * node = malloc(sizeof(main_node_t));
    node->type = MAIN_NODE;
    node->first = first;
    node->second = second; 
    return node;
}

variable_node_t * make_variable_node(char * name){
    variable_node_t * node = malloc(sizeof(variable_node_t));
    node->name = calloc(strlen(name)+1, sizeof(char));
    strcpy(node->name, name);
    node->type = VARIABLE_NODE;
    node->value = 0;
    
    return node;
}

num_node_t * make_num_node(char * num){
    num_node_t * node = malloc(sizeof(num_node_t));
    node->number = calloc(strlen(num)+1, sizeof(char));;
    strcpy(node->number, num );
    node->type = NUM_NODE;
    return node;
}

string_node_t * make_string_node(char * string){
    string_node_t * node = malloc(sizeof(string_node_t));
    node->string = calloc(strlen(string)+1, sizeof(char));
    strcpy(node->string, string);
    node->type = STRING_NODE;
    return node;
}

boolean_node_t * make_boolean_node(char * boolean){
    boolean_node_t * node = malloc(sizeof(boolean_node_t));
    node->boolean=calloc(strlen(boolean)+1, sizeof(char));
    strcpy(node->boolean, boolean);
    node->type = BOOLEAN_NODE;
    return node;
}

print_num_node_t * make_print_num_node(char * variable){
    print_num_node_t * node = malloc(sizeof(print_num_node_t));
    node->type = PRINT_NUM_NODE;
    node->variable = calloc(strlen(variable)+1, sizeof(char));
    strcpy(node->variable, variable);
    return node;
}

print_string_node_t * make_print_string_node(char * variable){
    print_string_node_t * node = malloc(sizeof(print_string_node_t));
    node->type = PRINT_STRING_NODE;
    node->variable = calloc(strlen(variable)+1, sizeof(char));
    strcpy(node->variable, variable);
    return node;
}

declare_var_node_t * make_declare_var_node(char * name , node_t * value , variable_type type){
    declare_var_node_t * node = malloc(sizeof(declare_var_node_t));
    node->type = DECLARE_VAR_NODE;
    node->var_type = type;
    node->name = calloc(strlen(name) + 1 , sizeof(char));
    strcpy(node->name , name);
    if ( value != 0 ){
        node->value = value;
    }
}
define_var_node_t * make_define_var_node(char * name , node_t * value){
    define_var_node_t * node = malloc(sizeof(define_var_node_t));
    node->type = DEFINE_VAR_NODE;
    node->name = calloc(strlen(name) + 1 , sizeof(char));
    strcpy(node->name , name);
    node->value = value;
}

int main(int argc , char ** argv){
    print_string_node_t * node = make_print_string_node(argv[1]);
    printf("printf(\"%%s\", %s );\n" , node->variable);
    return 0;
}