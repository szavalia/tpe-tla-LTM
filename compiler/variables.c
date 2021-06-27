#include "variables.h"
#include <stdio.h>

#define FALSE 0 
#define TRUE 1

unsigned long var_count = 0;

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
        if( strcmp(variables[i].name, name) == 0 ){
            handle_error("Variable already defined: " , name);
            return FALSE;
        }
        if( variables[i].name == 0){
            variable = i;
            var_count++;
            variables[i].type = type;
            variables[i].declared = TRUE;
            return TRUE;
        } 
    }
}


int define_and_declare_variable(char * name , variable_type type){
    int variable = -1;
    for(int i = 0 ; i < MAX_VARIABLES && variable == -1 ; i ++){
        if( strcmp(variables[i].name, name) == 0 ){
            handle_error("Variable already defined: " , name); //error de compilacion, variable ya definida
            return FALSE;
        }
        if( variables[i].name == 0){
            variable = i;
            var_count++;
            variables[i].name= name;
            variables[i].declared = FALSE;
            variables[i].defined = TRUE;
            variables[i].type = type;
            return TRUE;
        }
    }
}

int define_variable(char * name , variable_type type ){
    int variable = -1;
    for( int i = 0 ; i < var_count && variable == -1 ; i++ ){
        if(strcmp(variables[i].name , name )){
            if( variables[i].type != type){
                handle_error("Incompatible variable type when assigning to: " , name );
                //error incompatible type
            }
            variables[i].defined = TRUE;
            return 1;
        }
    }
    handle_error("Variable not declared, first use of: " , name);
    return -2; //not declared, first use
}

//SET VA CON TRUE SI QUIERO DEFINIR LA VARIABLE
variable_type find_variable(char * name){
    int variable = -1;
    for( int i = 0 ; i < var_count && variable == -1 ; i++ ){
        if(strcmp(variables[i].name , name )){
            if(!variables[i].defined){
                handle_error("Variable declared but not defined : " , name);
                return -1; //declared but not defined
            }
            return variables[i].type;
        }
    }
    handle_error("Variable not declared, first use of: " , name);
    return -2; //not declared, first use
}

