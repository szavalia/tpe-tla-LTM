#include "reduce_node.h"
#include "variables.h"
extern variable_t variables[];

static void handle_error(char *message , char * variable) {
	fprintf(stderr, "%s%s\n\n", message , variable);
  	exit(1);
}

variable_type get_var_type( node_t * n){
    switch(n->type){
        case: NUM_NODE
            return NUMBER;
            break;
        case: STRING_NODE
            return STRING;
            break;
        return -1;
    }

}

char * handle_reduction(node_t *n){
    if( n == 0 ){
        handle_error("que mierda paso!" , "");
    }
    return reduction_functions[n->type](n);
}

char * reduce_main_node(node_t *n){
    main_node_t *node = (main_node_t *) n;
}

char * reduce_variable_node(node_t *n){
    variable_node_t *node = (variable_node_t *) n; 
    char * value = handle_reduction(node->value);
    return value;
}

char * reduce_num_node(node_t *n){
	num_node_t *node = (num_node_t *) n;
    return node->number;
}

char * reduce_string_node(node_t *n){
	string_node_t *node = (string_node_t *) n;
    return node->string;
}

char * reduce_boolean_node(node_t *n){
	boolean_node_t *node = (boolean_node_t *) n;
	return node->boolean;
}

char * reduce_print_num_node(node_t *n){

	print_num_node_t *node = (print_num_node_t *) n;

    variable_type type = find_variable(node->variable);
    if( type != NUMBER  ){
        handle_error("(pn) Incompatible variable type, required NUMBER. caused by variable :" , node->variable);
    }
	char aux[] = "printf(\"%%f\", %s);";
	char * buffer = malloc( strlen(node->variable) + strlen(aux) - 2);
	sprintf(buffer, aux, node->variable);
	return buffer;
}
    
char * reduce_define_var_node(node_t * n ){
    define_var_node_t * node = (define_var_node_t*) node;
    define_variable( node->name , get_var_type(node->variable));
}

char * reduce_print_string_node(node_t *n){
	print_string_node_t *node = (print_string_node_t *) n;
    
    variable_type type = find_variable(node->variable);
    if( type != STRING  ){
        handle_error("(ps) Incompatible variable type, required STRING. caused by variable :" , node->variable);
    }
	char aux[] = "printf(\"%%s\", %s);";
    char * buffer = malloc(strlen(node->variable) + strlen(aux) - 2 /*porque el %s se reemplaza por el node->variable*/);
    sprintf(buffer , aux, node->variable);
    return buffer;
}


