%{
// declaraciones en C and what not
    #include <stdio.h>
    #include "make_node.h"

    int yylex(void);

    void yyerror(char *msg);
%}

%union {
    char buffer[250];
    node_t * node;
    node_t * root;
}
%parse-param {node_t ** root}
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


%type <node> main_state 
%type <node> int_state
%type <node> string_state
%type <node> content_state
%%

start:
    main_state { *(root) = $1 ;}
    ;

main_state:
        main_state content_state { $$ = make_main_node($1 , $ 2); }
    |   content_state  {$$ = make_main_node($1 , 0 ); }
    ;

int_state:
       NAME IGUAL expression_state NEWLINE {$$ = make_define_node($1 , $3 , NUMBER);}
    |  NAME NEWLINE {$$ = make_declare_node($1, 0 , NUMBER);}
    ;

string_state:
        NAME IGUAL VALSTRING NEWLINE {$$ = make_define_node($1)}
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
    |   PS ps_state     {$$ = $2}
    |   PI pi_state
    |   NAME IGUAL redefine_state
    ;

ps_state:
        NAME NEWLINE     { $$ = make_print_string_state($1);}
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
    |   TRUE
    |   FALSE
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
    |   VALNUM  {
                    $$ = make_num_node($1);
                    printf("ya me llegó y procesé el valnum \n");
                }
    ;


%%

void yyerror(char *msg) {
    printf("\n%s\n", msg);
  	exit(1);
}


int main () {
    node_t * root;
    yyparse(&root);
    printf("%s\n" , generate_code(root));
    return 0;
}   
