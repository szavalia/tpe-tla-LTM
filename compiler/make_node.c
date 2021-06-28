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
char * bool_states[] = { "true" , "false" };
boolean_node_t * make_boolean_node(char * boolean){
    boolean_node_t * node = malloc(sizeof(boolean_node_t));
     node->type = BOOLEAN_NODE;
    int index = (boolean[0] == 't')? 0 : 1;
    node->boolean=calloc(strlen(bool_states[index])+1, sizeof(char));
    strcpy(node->boolean, bool_states[index]);
    printf("im on a boolean\n");
    printf("%s\n" , node->boolean);
    printf("%ld\n" , node);
    return node;
}

print_num_node_t * make_print_num_node(char * variable){
    print_num_node_t * node = malloc(sizeof(print_num_node_t));
    node->type = PRINT_NUM_NODE;
    node->variable = calloc(strlen(variable)+1, sizeof(char));
    strcpy(node->variable, variable);
    return node;
}

print_string_node_t * make_print_string_node(node_t * variable){
    print_string_node_t * node = malloc(sizeof(print_string_node_t));
    node->type = PRINT_STRING_NODE;
    node->variable = variable;
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
    }else{
        fprintf(stderr , "no me llego value bro\n");
    }
    return node;
}
define_var_node_t * make_define_var_node(char * name , node_t * value){
    define_var_node_t * node = malloc(sizeof(define_var_node_t));
    node->type = DEFINE_VAR_NODE;
    node->name = calloc(strlen(name) + 1 , sizeof(char));
    strcpy(node->name , name);
    node->value = value;
    return node;
}

if_node_t * make_if_node(node_t * condition , node_t * block){
    if_node_t * node = malloc(sizeof(if_node_t));
    node->type = IF_NODE;
    node->condition = condition;
    node->block = block;
    return node;
}


while_node_t * make_while_node(node_t * condition , node_t * block){
    while_node_t * node = malloc(sizeof(while_node_t));
    node->type = WHILE_NODE;
    node->condition = condition;
    node->block = block;
    return node;
}
condition_state_node_t * make_condition_state_node(char * condition , node_t * left , node_t * right){
    condition_state_node_t * node = malloc(sizeof(condition_state_node_t));
    node->type = CONDITION_STATE_NODE;
    node->left = left;
    node->right = right;
    node->condition[0] = condition[0];
    node->condition[1] = 0;
    return node;
}

variable_comp_node_t * make_variable_comp_node( char * condition , node_t * left , node_t * right){
    variable_comp_node_t * node = malloc(sizeof(variable_comp_node_t));
    node->type = VARIABLE_COMP_NODE;
    node->left = left;
    node->right = right;
    node->condition[0] = condition[0];
    node->condition[1] = condition[1];
    node->condition[2] = 0;
    return node;
}

node_t * make_expression_node(node_t * left, node_t * right, operation_type optype){
    expression_node_t * node = malloc(sizeof(expression_node_t));
    node->type = EXPRESSION_NODE;
    node->operation = optype;
    node->left = left;
    node->right = right;
    return (node_t *)node;
}

node_t * test_node(){
    return malloc(sizeof(node_t));
}
/*
int main(int argc , char ** argv){
    print_string_node_t * node = make_print_string_node(argv[1]);
    printf("printf(\"%%s\", %s );\n" , node->variable);
    return 0;
}*/