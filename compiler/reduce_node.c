#include "reduce_node.h"
#include "variables.h"
extern variable_t variables[];
#include <unistd.h>



static char * reduce_main_node(node_t *n);

static char * reduce_variable_node(node_t *n);

static char * reduce_num_node(node_t *n);

static char * reduce_string_node(node_t *n);

static char * reduce_boolean_node(node_t *n);

static char * reduce_print_num_node(node_t *n);

static char * reduce_print_string_node(node_t *n);

static char * reduce_declare_var_node(node_t *n);

static char * reduce_define_var_node(node_t *n);

static char * reduce_condition_state_node(node_t *n);

static char * reduce_variable_comp_node(node_t *n);

static char * reduce_if_node(node_t *n);

static char * reduce_while_node(node_t *n);

static char * reduce_expression_node(node_t *n);

static char * (*reduction_functions[])(node_t *) = {
    [MAIN_NODE] = reduce_main_node,
    [VARIABLE_NODE] = reduce_variable_node,
    [NUM_NODE] = reduce_num_node,
    [STRING_NODE] =reduce_string_node,
    [BOOLEAN_NODE] = reduce_boolean_node,
    [PRINT_NUM_NODE] = reduce_print_num_node,
    [PRINT_STRING_NODE] =reduce_print_string_node,
    [DECLARE_VAR_NODE] = reduce_declare_var_node,
    [DEFINE_VAR_NODE] = reduce_define_var_node,
    [CONDITION_STATE_NODE] = reduce_condition_state_node,
    [VARIABLE_COMP_NODE] = reduce_variable_comp_node,
    [IF_NODE] = reduce_if_node,
    [WHILE_NODE] = reduce_while_node,
    [EXPRESSION_NODE] = reduce_expression_node
};

char* declarations[] ={ "char *" , "int", "bool" };
char amogus[]="amogus_ඞ";
static void handle_error(char *message , char * variable) {
	fprintf(stderr, "%s%s\n\n", message , variable);
  	exit(1);
}

static void handle_warning(char *message , char * variable1 ,char * message2, char * variable2) {
	fprintf(stderr, "%s%s%s%s\n\n", message , variable1 ,message2, variable2 );
}

static variable_type get_var_type( node_t * n){
    switch(n->type){
        case NUM_NODE:
            return NUMBER;
            break;
        case STRING_NODE:
            return STRING;
            break;
        case BOOLEAN_NODE:
            return BOOLEAN;
            break;
        case EXPRESSION_NODE:
            return NUMBER;
            break;
        case CONDITION_STATE_NODE:
            return BOOLEAN;
            break;
        case VARIABLE_COMP_NODE:
            return BOOLEAN;
            break;
        default:
        return -1;
        break;
    }
    return -1;
}

char * handle_reduction(node_t *n){
    printf("en el handle reduction\n");
    if( n == 0 ){
        handle_error("falta una hoja!" , "");
    }
    printf("me dio de tipo %d\n" , n->type);
    return reduction_functions[n->type](n);
}

static char * reduce_main_node(node_t *n){
    printf(">reduce main\n");
    main_node_t *node = (main_node_t *) n;
    char * value1 = handle_reduction(node->first);
    if ( node->second != 0 ){
        char * value2 = handle_reduction(node->second);
    
        char * buffer = malloc(strlen(value1) + strlen(value2) + 2 );
        sprintf(buffer , "%s\n%s", value1, value2);
        printf("<reduce main con 2 \n");
        return buffer;
    }
    printf("tengo en el value 1: \n%s\n" , value1);
    printf("<reduce main con 1 \n");
    return value1;
}

static char * reduce_variable_node(node_t *n){
    variable_node_t * node = (variable_node_t *) n;
     printf(">reduce var\n");
     find_variable(node->name);
     printf("<reduce var\n");
    return node->name;
}

static char * reduce_num_node(node_t *n){
     printf(">reduce num\n");
	num_node_t *node = (num_node_t *) n;
    printf("<reduce num\n");
    return node->number;
}

static char * reduce_string_node(node_t *n){
     printf(">reduce string\n");
	string_node_t *node = (string_node_t *) n;
      printf("<reduce string\n");
      if ( strcmp(node->string, "sus") == 0 ){
          node->string = amogus;
      }
    return node->string;
}

static char * reduce_boolean_node(node_t *n){
     printf(">reduce boolean\n");
	boolean_node_t *node = (boolean_node_t *) n;
     printf("<reduce boolean\n");
	return node->boolean;
}

static char * reduce_print_num_node(node_t *n){
     printf(">reduce print num\n");
	print_num_node_t *node = (print_num_node_t *) n;
    char * value;
    if ( node->variable->type == VARIABLE_NODE){
        variable_node_t * var = (variable_node_t *) node->variable;
        variable_type type = find_variable(var->name);    
        if( type != NUMBER  ){
            handle_error("(pi) Incompatible variable type, required NUMBER. caused by variable :" , var->name);
        }    
        value = var->name;
    }else{
        printf("i wanted to get the type %d but i got %d\n" , EXPRESSION_NODE , node->variable->type);
        if ( get_var_type(node->variable) != NUMBER ){
            handle_error("(pi) Incompatible type, requeried NUMBER" ,"");
        }
        value = handle_reduction(node->variable);
    }
        char aux[] = "printf(\"%%d\\n\", %s);";
        char * buffer = malloc( strlen(value) + strlen(aux) - 2);
        sprintf(buffer, aux, value );
        printf("<reduce print num\n");
	return buffer;
}

static char * reduce_declare_var_node(node_t * n ){
     printf(">reduce declare var\n");
    declare_var_node_t * node = (declare_var_node_t*) n;
      printf("vivi\n");
    char * declaration;
    if( node->var_type == STRING){
        declaration = declarations[0];
    }else if(node->var_type == NUMBER){
        declaration = declarations[1];
    }
    else if(node->var_type == BOOLEAN){
        printf("me dio que era una variable booleana\n");
        declaration = declarations[2];
    }
    char * buffer;
    if ( node->value == 0 ){
        printf("no tenia value\n");
        declare_variable( node->name , node->var_type );
            char aux[] = "%s %s;";
            buffer = malloc( strlen(declaration) + 4 /* = */  + strlen(node->name) + 1 );
            sprintf(buffer , aux , declaration ,  node->name);    
        printf("<reduce declare var\n");
     return buffer; 

    }else{
        printf("si tenia value\n");
        printf("%ld\n" , node->value);
        define_and_declare_variable(node->name , node->var_type);
        printf("funciono el coso de variables\n");
        char * value = handle_reduction(node->value);
        printf("haciendo la redox\n");
        if ( node->var_type != STRING){
            printf("no era string\n");
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

static char * reduce_define_var_node(node_t * n ){
     printf(">reduce define var\n");
    define_var_node_t * node = (define_var_node_t*) n;
    printf("i got the varible: %s" , node->name);

    define_variable( node->name , get_var_type(node->value));
    char * value = handle_reduction(node->value);
    char aux[] = "%s = %s;";
    char * buffer = malloc( 3 /* = */ + strlen(value) + strlen(node->name) + 1 );
    sprintf(buffer , aux , node->name , value );
    printf("<reduce define var\n");
    return buffer; 
}

static char * reduce_print_string_node(node_t *n){
     printf(">reduce print string\n");
	print_string_node_t *node = (print_string_node_t *) n;
    char * value;
    if ( node->variable->type == VARIABLE_NODE){
        variable_node_t * var = (variable_node_t*) node->variable;
        variable_type type = find_variable(var->name);
        printf("viendo variables\n");
        if( type != STRING  ){
            handle_error("(ps) Incompatible variable type, required STRING. caused by variable :" , node->variable);
        }
        value = var->name;
        char aux[] = "printf(\"%%s\\n\", %s);";
        char * buffer = malloc(strlen(value) + strlen(aux)  /*porque el %s se reemplaza por el node->variable*/);
        sprintf(buffer , aux, value);
        printf("<reduce print string\n");
        return buffer;
    }else{
        if( get_var_type(node->variable) != STRING ){
            handle_error("(ps) Error ps expects STRING type\n" , "");
        }
        value = handle_reduction(node->variable);
        char aux[] = "printf(\"%s\\n\");";
        char * buffer = malloc(strlen(value) + strlen(aux)  /*porque el %s se reemplaza por el node->variable*/);
        sprintf(buffer , aux, value);
        
    printf("<reduce print string\n");
        return buffer;
    }
	
    return 0;
}

static char * reduce_condition_state_node(node_t *n){
    printf(">conditon state\n");
    condition_state_node_t *node = (condition_state_node_t * ) n;
    if ( node->condition[0] == 0){
        return handle_reduction(node->left);
    }
    if( node->condition[0] == '!'){
        char * left = handle_reduction(node->left);
        char * aux = "!(%s)";
        char * buffer = malloc( 3 + 1 + strlen(left));
        sprintf(buffer , aux , left );
        return buffer;
    }
    char * left = handle_reduction(node->left);
    char * right = handle_reduction(node->right);
    char * aux = "( %s %c%c %s )";
    char * buffer = malloc( 6 + 1 + strlen(left) + strlen(right) );
    sprintf(buffer , aux , left , node->condition[0] , node->condition[0] , right);
    return buffer;
    printf("<conditon state\n");
}
static char * get_expression_value(node_t * n){
    if(n == 0)
        handle_error("Null!", "");

    if(n->type != NUM_NODE && n->type != VARIABLE_NODE && n->type != EXPRESSION_NODE)
        handle_error("Incompatible type in expression", "");

    if(n->type == NUM_NODE){
        return handle_reduction(n);
    }
    else if(n->type == VARIABLE_NODE){
        puts("REDUCIENDO LA VARIABLE");
        variable_node_t *node = (variable_node_t *)n;
        if(find_variable(node->name) == NUMBER){
            return node->name;
        }
        else
            handle_error("Incompatible type in expression: ", node->name);
    }
    else{
        handle_reduction(n);
    }
}

static char * reduce_expression_node(node_t *n){
    expression_node_t * node = (expression_node_t *) n;
    char *buffer, *leftBuffer, *rightBuffer, operand;
    
    //Estp puede pasar, significa que estoy haciendo -x
    if(node->left != 0)
        leftBuffer = get_expression_value(node->left);
    else{
        leftBuffer = malloc(1);
        *leftBuffer = '\0';
    }
    if(node->right != 0)
        rightBuffer = get_expression_value(node->right);


    switch(node->operation){
        case OP_NONE: //right es null
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
              
    buffer = malloc(sizeof(leftBuffer)+ sizeof(rightBuffer) + 1 + 1);
    sprintf(buffer, "%s%c%s", leftBuffer, operand, rightBuffer);

    return buffer;
}

static char * get_comp_value( node_t * n , variable_type * type){
    if(n->type == NUM_NODE || n->type == BOOLEAN_NODE){
        if( n->type == NUM_NODE){
            *type = NUMBER;
        }else{
            *type = BOOLEAN;
        }
        return handle_reduction(n);
    }else if(n->type == VARIABLE_NODE){
        variable_node_t * node = (variable_node_t *) n;
        *type = find_variable(node->name);
        if( (*type != BOOLEAN) && (*type != NUMBER)){
           handle_error("Comparable types are BOOLEAN and NUMBER, uncopatible type of variable: " , node->name);
        }
        return node->name;
    }
}

static char *reduce_variable_comp_node(node_t *n){
    printf(">comp state\n");
    variable_comp_node_t * node = (variable_comp_node_t*) n;
    variable_type right_type;
    variable_type left_type; 
    char *right = get_comp_value( node->right , &right_type );
    char *left = get_comp_value(node->left , &left_type);
    if( right_type != left_type ) {
        handle_warning("WARNING: attempting to compare 2 different types of values: " , left , " and "  , right);
    }
    char * aux = "( %s %s %s )";
    char * buffer = malloc( 5 + 1 + strlen(left) + strlen(right) );
    sprintf(buffer , aux , left , node->condition, right);
    printf("<comp state\n");
    return buffer;
}

static char *reduce_if_node(node_t *n){
    printf(">if reduce\n");
    if_node_t * node = (if_node_t *)n;
    char * aux="if %s{\n%s\n}";
    char * condition = handle_reduction(node->condition);
    char * block = handle_reduction(node->block);
    char * buffer = malloc(strlen(condition) + strlen(block) + 8);
    sprintf(buffer , aux , condition, block); 
    printf("<if reduce\n");
    return buffer;
}

static char *reduce_while_node(node_t *n){
    printf(">while reduce\n");
    if_node_t * node = (if_node_t *) n;
    char * aux="do{\n%s\n}while%s;";
    char * condition = handle_reduction(node->condition);
    char * block = handle_reduction(node->block);
    char * buffer = malloc(strlen(condition) + strlen(block) + 17);
    sprintf(buffer , aux , block, condition ); 
    printf("<while reduce\n");
    return buffer;
}