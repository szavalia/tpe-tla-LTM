#include "reduce_node.h"
#include "variables.h"
extern variable_t variables[];
#include <unistd.h>

char* declarations[] ={ "char *" , "double", "int" };

static void handle_error(char *message , char * variable) {
	fprintf(stderr, "%s%s\n\n", message , variable);
  	exit(1);
}

variable_type get_var_type( node_t * n){
    switch(n->type){
        case NUM_NODE:
            return NUMBER;
            break;
        case STRING_NODE:
            return STRING;
            break;
        return -1;
    }

}

char * handle_reduction(node_t *n){
    //printf("en el handle reduction\n");
    if( n == 0 ){
        handle_error("falta una hoja!" , "");
    }
    return reduction_functions[n->type](n);
}

char * reduce_main_node(node_t *n){
    printf(">reduce main\n");
    main_node_t *node = (main_node_t *) n;
    char * value1 = handle_reduction(node->first);
    if ( node->second != 0 ){
        char * value2 = handle_reduction(node->second);
    
        char * buffer = malloc(strlen(value1) + strlen(value2) + 2 );
        sprintf(buffer , "%s\n%s", value1, value2);
        printf("\n tengo en el buffer este: \n%s\n" , buffer);
        
        printf("el buffer es %ld\n" , buffer);
        printf("<reduce main con 2 \n");
        return buffer;
    }
    printf("tengo en el value 1: \n%s\n" , value1);
    printf("<reduce main con 1 \n");
    return value1;
}

char * reduce_variable_node(node_t *n){
     printf(">reduce var\n");
    variable_node_t *node = (variable_node_t *) n; 
    char * value = handle_reduction(node->value);
       printf("<reduce var\n");
    return value;
}

char * reduce_num_node(node_t *n){
     printf(">reduce num\n");
	num_node_t *node = (num_node_t *) n;
    printf("<reduce num\n");
    return node->number;
}

char * reduce_string_node(node_t *n){
     printf(">reduce string\n");
	string_node_t *node = (string_node_t *) n;
      printf("<reduce string\n");
    return node->string;
}

char * reduce_boolean_node(node_t *n){
     printf(">reduce boolean\n");
	boolean_node_t *node = (boolean_node_t *) n;
     printf("<reduce boolean\n");
	return node->boolean;
}

char * reduce_print_num_node(node_t *n){
     printf(">reduce print num\n");
	print_num_node_t *node = (print_num_node_t *) n;

    variable_type type = find_variable(node->variable);
    if( type != NUMBER  ){
        handle_error("(pn) Incompatible variable type, required NUMBER. caused by variable :" , node->variable);
    }
	char aux[] = "printf(\"%%f\\n\", %s);";
	char * buffer = malloc( strlen(node->variable) + strlen(aux) - 2);
	sprintf(buffer, aux, node->variable);
    printf("<reduce print num\n");
	return buffer;
}

char * reduce_declare_var_node(node_t * n ){
     printf(">reduce declare var\n");
    declare_var_node_t * node = (declare_var_node_t*) n;
    char * declaration;
    if( node->var_type == STRING){
        declaration = declarations[0];
    }else if(node->var_type == NUMBER){
        declaration = declarations[1];
    }
    else if(node->var_type == BOOLEAN){
        declaration = declarations[2];
    }
    char * buffer;
    if ( node->value == 0 ){
        declare_variable( node->name , node->var_type );
            char aux[] = "%s %s;";
            buffer = malloc( strlen(declaration) + 4 /* = */  + strlen(node->name) + 1 );
            sprintf(buffer , aux , declaration ,  node->name);    
        printf("<reduce declare var\n");
     return buffer; 

    }else{
        //TODO: AGREGAR LOS " " cuando es string
        define_and_declare_variable(node->name , node->var_type);
            char * value = handle_reduction(node->value);
        if ( node->var_type != STRING){
            char aux[] = "%s %s = %s;";
            buffer = malloc( strlen(declaration) + 5 /*  = */ + strlen(value) + strlen(node->name) + 1 );
            sprintf(buffer , aux , declaration ,  node->name , value );    
        }else{
        char aux[] = "%s %s = \"%s\";";
        buffer = malloc( strlen(declaration) + 7 /*  = "" */  + strlen(value) + strlen(node->name) + 1 );
        sprintf(buffer , aux , declaration ,  node->name , value);    
        }
        
     printf("<reduce declare var\n");
     return buffer; 
   
    }
}

char * reduce_define_var_node(node_t * n ){
     printf(">reduce define var\n");
    define_var_node_t * node = (define_var_node_t*) node;
    define_variable( node->name , get_var_type(node->value));
    char * value = handle_reduction(node->value);
    char aux[] = "%s = %s";
    char * buffer = malloc( 3 /* = */ + strlen(value) + strlen(node->name) + 1 );
    sprintf(buffer , aux , node->name , value );
    printf("<reduce define var\n");
    return buffer; 
}

char * reduce_print_string_node(node_t *n){
    printf(">reduce print string\n");
	print_string_node_t *node = (print_string_node_t *) n;
    variable_type type = find_variable(node->variable);
    printf("viendo variables\n");
    if( type != STRING  ){
        handle_error("(ps) Incompatible variable type, required STRING. caused by variable :" , node->variable);
    }
	char aux[] = "printf(\"%%s\\n\", %s);";
    char * buffer = malloc(strlen(node->variable) + strlen(aux)  /*porque el %s se reemplaza por el node->variable*/);
    sprintf(buffer , aux, node->variable);
     printf("<reduce print string\n");
    return buffer;
}

char * reduce_expression_node(node_t *n){
    expression_node_t * node = (expression_node_t *) n;
    char *buffer, *leftBuffer, *rightBuffer, operand;
    
    //Estp puede pasar, significa que estoy haciendo -x
    if(node->left != 0)
        leftBuffer = handle_reduction(node->left);
    else{
        leftBuffer = malloc(1);
        *leftBuffer = '\0';
    }

    switch(node->operation){
        case OP_NONE: //right es null

            leftBuffer = handle_reduction(node->left);
            buffer = malloc(sizeof(leftBuffer) + 2 /* () */ + 1);
            sprintf(buffer, "(%s)", leftBuffer);
            return buffer;
        break;

        case OP_SUB:                  
            operand = '-';
        break;
        
        case OP_SUM:
            operand = '+';
        break;
        
        case OP_MUL:
            operand = '*';
        break;

        case OP_DIV:
            if(*leftBuffer == '0'){
                handle_error("División por cero", leftBuffer);
            }
            operand = '/';
            
        break;
    }
              
    rightBuffer = handle_reduction(node->right);
    buffer = malloc(sizeof(leftBuffer)+ sizeof(rightBuffer) + 1 + 1);
    sprintf(buffer, "%s%c%s", leftBuffer, operand, rightBuffer);

    return buffer;
}


char * generate_code(node_t * root , char ** buffer){
    char * code = handle_reduction(root);
    printf("%ld\n" , code);
    printf("%s\n" , code);
    printf("%ld\n" , code);
    *buffer = code;
    return code;
}
