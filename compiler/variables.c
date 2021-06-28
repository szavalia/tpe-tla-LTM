#include "variables.h"
#include <stdio.h>
#define FALSE 0 
#define TRUE 1

unsigned long var_count = 0;

variable_t variables_ltm[MAX_VARIABLES];

void initialize_variables(){
    memset(variables , 0 , sizeof(variables));
}


static void handle_error(char *message , char * variable) {
	fprintf(stderr, "%s%s\n\n", message , variable);
  	exit(1);
}

int declare_variable(char * name , variable_type type){
    int variable = -1;
    for(int i = 0 ; i < MAX_VARIABLES && variable == -1 ; i ++){
        if( variables_ltm[i].name == 0){
            variable = i;
            var_count++;
            variables_ltm[i].type = type;
            variables_ltm[i].declared = TRUE;
            return TRUE;
        } 
        if( strcmp(variables_ltm[i].name, name) == 0 ){
            handle_error("Variable already defined: " , name);
            return FALSE;
        }
    }
    return FALSE;
}


int define_and_declare_variable(char * name , variable_type type){
    int variable = -1;
    for(int i = 0 ; i < MAX_VARIABLES && variable == -1 ; i ++){
         if( variables_ltm[i].name == 0){
            variable = i;
            var_count++;
            variables_ltm[i].name= name;
            variables_ltm[i].declared = FALSE;
            variables_ltm[i].defined = TRUE;
            variables_ltm[i].type = type;
            return TRUE;
        }
        if( strcmp(variables[i].name, name) == 0 ){
            handle_error("Variable already defined: " , name); //error de compilacion, variable ya definida
            return FALSE;
        }
       
    }
    return FALSE;
}

int define_variable(char * name , variable_type type ){
    int variable = -1;
    for( int i = 0 ; i < MAX_VARIABLES && variable == -1 ; i++ ){
        if(variables_ltm[i].name  == 0 ){
            handle_error("variable not found: " , name);
        }
        if(strcmp(variables_ltm[i].name , name ) == 0){
            if( variables_ltm[i].type != type){
                handle_error("Incompatible variable type when assigning to: " , name );
                //error incompatible type
            }
            variables_ltm[i].defined = TRUE;
            return 1;
        }
    }
    handle_error("Variable not declared, first use of: " , name);
    return -2; //not declared, first use
}

//SET VA CON TRUE SI QUIERO DEFINIR LA VARIABLE
variable_type find_variable(char * name){
    int variable = -1;
    for( int i = 0 ; i < MAX_VARIABLES && variable == -1 ; i++ ){
        if(variables_ltm[i].name == 0 ){
            handle_error("Variable not declared, first use of: " , name);        
        }
        printf("pasando por el i: %d\n" , i );
        if(strcmp(variables_ltm[i].name , name ) == 0){
            if(!variables_ltm[i].defined){
                handle_error("Variable declared but not defined : " , name);
                return -1; //declared but not defined
            }
            return variables_ltm[i].type;
        }
    }
    handle_error("Variable not declared, first use of: " , name);
    return -2; //not declared, first use
}

