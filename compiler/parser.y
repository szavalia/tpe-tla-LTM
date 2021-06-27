%{
// declaraciones en C and what not
    #include <stdio.h>
    int yylex(void);

    void yyerror(char *msg);
%}

%union {

}

%token INT
%token STRING
%token IF
%token FI
%token DO
%token PS
%token PI
%token W
%token BOOL

%token TRUE
%token FALSE

%token IGUAL
%token MAS 
%token MENOS
%token POR
%token DIVIDIDO
%token MODULO
%token ABRACKET
%token CBRACKET

%token EQ
%token NE
%token LT
%token LE
%token GT
%token GE

%token NEWLINE

%token NAME
%token VALNUM
%token VALSTRING

%%
main_state:
        main_state content_state
    |   content_state
    ;

int_state:
       NAME IGUAL expression_state NEWLINE {printf("Termine con el estado int \n");}
    |  NAME NEWLINE
    ;

string_state:
        NAME IGUAL VALSTRING NEWLINE
    ;

bool_state:
        NAME IGUAL bool_values NEWLINE
    ;

bool_values:
        TRUE
    |   FALSE
    ;

if_state:
        condition_state NEWLINE main_state FI NEWLINE
    ;

do_state:
        NEWLINE main_state
    ;

while_state:
        W condition_state NEWLINE
    ;

content_state:
        INT int_state
    |   STRING string_state
    |   BOOL bool_state
    |   IF if_state
    |   DO do_state while_state
    |   PS ps_state
    |   PI pi_state
    |   NAME IGUAL redefine_state
    ;

ps_state:
        NAME NEWLINE     {/*hay que chequear que name sea una string variable*/}
    |   VALSTRING NEWLINE
    ;

pi_state:
        NAME NEWLINE
    |   VALNUM NEWLINE    
    ;

redefine_state:
        expression_state NEWLINE
    ;

condition_state:
        ABRACKET variable_state comp_state variable_state CBRACKET
    |   ABRACKET variable_state comp_state condition_state CBRACKET
    |   ABRACKET condition_state comp_state variable_state CBRACKET
    |   ABRACKET condition_state comp_state condition_state CBRACKET
    ;

variable_state:
        NAME
    |   VALNUM
    |   VALSTRING
    ;

comp_state:
        EQ
    |   NE
    |   LT
    |   LE
    |   GT
    |   GE
    ;

expression_state:
        expression_state MAS mul_state
    |   expression_state MENOS mul_state
    |   mul_state
    ;

mul_state:
        mul_state POR primary_state
    |   mul_state DIVIDIDO primary_state
    |   primary_state
    ;

primary_state:
        ABRACKET expression_state CBRACKET
    |   MENOS primary_state
    |   VALNUM  {printf("ya me llegó y procesé el valnum \n");}
    ;


%%

void yyerror(char *msg) {
    printf("\n%s\n", msg);
  	exit(1);
}


int main () {
    yyparse();
    return 0;
}   
