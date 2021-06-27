#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include <string.h>
#include <stdlib.h>

#define MAX_VARIABLES 50

typedef enum {
    NUMBER = 0 ,
    STRING = 1
}variable_type;


typedef struct variable_t{
    variable_type type;
    char * name;
    int defined;
    int declared;
}variable_t;

variable_t variables[MAX_VARIABLES];

void initialize_variables();

int declare_variable(char * name ,variable_type type);

int define_and_declare_variable(char * name , variable_type type);

int define_variable(char * name ,variable_type type);

//SET VA CON TRUE SI QUIERO DEFINIR LA VARIABLE
variable_type find_variable(char * name );

#endif

