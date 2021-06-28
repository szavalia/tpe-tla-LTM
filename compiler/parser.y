%{
// declaraciones en C and what not
    #include <stdio.h>
    #include "make_node.h"
    #include <stdint.h>
    #include "code_generator.h"
    int yylex(void);
    void yyerror(node_t ** root , char *msg);
    char * COMP_STATES[] = { "==" , "!=" , "<" ,"<=" , ">" ,">="};
    char * LOGICAL_OPS[] = {"&" , "|"};
%}

%union {
    char buffer[1024];
    char * condition;
    node_t * node;
    node_t * root;
}

%parse-param {node_t ** root}
%token INT
%token STRINGT
%token IF
%token FI
%token DO
%token PS
%token PI
%token W
%token BOOL

%token TRUET
%token FALSET

%token IGUAL
%token MAS 
%token MENOS
%token POR
%token DIVIDIDO
%token MODULO
%token ABRACKET
%token CBRACKET

%token<contidion> EQ
%token<contidion> NE
%token<contidion> LT
%token<contidion> LE
%token<contidion> GT
%token<contidion> GE
%token<contidion> AND
%token<contidion> OR

%token NEWLINE

%token <buffer> NAME
%token <buffer> VALNUM
%token <buffer> VALSTRING



%type<root> start

%type<node> content_state
%type<node> main_state

%type<node> int_state
%type<node> string_state
%type<node> bool_state
%type<node> ps_state
%type<node> pi_state

%type<node> if_state
%type<node> do_state
%type<node> while_state

%type<node> redefine_state
%type<node> condition_state
%type<node> expression_state
%type<node> mul_state
%type<node> primary_state
%type<node> valstring_state
%type<node> bool_values
%type<node> variable_state


%type <condition> comp_state logical_state


%%

start:
    main_state { *(root) = $1 ;}
    ;

main_state:
        main_state content_state { $$ = make_main_node($1 , $2); }
    |   content_state  {$$ = make_main_node($1 , 0 ); }
    ;

int_state:
       NAME IGUAL expression_state NEWLINE {
           $$ =make_declare_var_node( $1 , $3 , NUMBER);
           }
    |  NAME NEWLINE {
        $$ = make_declare_var_node($1, 0 , NUMBER);
        }
    ;

string_state:
        NAME IGUAL valstring_state NEWLINE 
            {  
                $$ =make_declare_var_node($1 , $3 , STRING );
            }
    ;

valstring_state:
        VALSTRING 
            {
                $$ = make_string_node($1);
            }
    ;

bool_state:
        NAME IGUAL bool_values NEWLINE { $$ =make_declare_var_node($1, $3 , BOOLEAN);} 
    |   NAME IGUAL condition_state NEWLINE { $$= make_declare_var_node($1 , $3 , BOOLEAN);}
    ;

bool_values:    
        TRUET { $$ = make_boolean_node("t");}
    |   FALSET {$$ = make_boolean_node("f");}
    ;

if_state:
        condition_state NEWLINE main_state FI NEWLINE { $$ = make_if_node($1 , $3);}
    ;

do_state:
        NEWLINE main_state { $$ = $2;}
    ;

while_state:
        W condition_state NEWLINE { $$ = $2;}
    ;

content_state:
        INT int_state { $$ = $2; }
    |   STRINGT string_state { $$ = $2; }
    |   BOOL bool_state { $$ = $2; }
    |   IF if_state { $$ = $2; }
    |   DO do_state while_state { $$ = make_while_node($3 , $2); }
    |   PS ps_state  { $$ = $2; }
    |   PI pi_state { $$ = $2; }
    |   NAME IGUAL redefine_state   { 
        $$ = make_define_var_node($1, $3); }
    ;

ps_state:
        NAME NEWLINE     { $$ = make_print_string_node(make_variable_node($1)); }
    |   valstring_state NEWLINE { $$ = make_print_string_node($1); }
    ;

pi_state:
        NAME NEWLINE {$$ = make_print_num_node($1);}
    |   VALNUM NEWLINE 
    ;

redefine_state:
        VALNUM NEWLINE { $$ = make_num_node($1);}
    |   expression_state NEWLINE   { $$ = $1; }
    ;

condition_state:   
        ABRACKET variable_state comp_state variable_state CBRACKET { $$ = make_variable_comp_node($3 , $2 , $4); }
    |   ABRACKET condition_state logical_state condition_state CBRACKET { $$ = make_condition_state_node($3 , $2 , $4);}    
    ;

variable_state:
        NAME    {$$ = make_variable_node($1);}
    |   VALNUM  {$$ = make_num_node($1);}
    |   valstring_state {$$ = $1;}
    |   TRUET   {$$ = make_boolean_node("t");}
    |   FALSET  {$$ = make_boolean_node("f");}
    ;

comp_state:
        EQ  {$$ = COMP_STATES[0];}
    |   NE  {$$ = COMP_STATES[1];}
    |   LT  {$$ = COMP_STATES[2];}
    |   LE  {$$ = COMP_STATES[3];}
    |   GT  {$$ = COMP_STATES[4];}
    |   GE  {$$ = COMP_STATES[5];}
    ;

logical_state:
        AND   { $$ = LOGICAL_OPS[0];}
    |   OR    { $$ = LOGICAL_OPS[1];}
    ;
expression_state:
        expression_state MAS mul_state  { $$ = make_expression_node($1, $3, OP_SUM); }
    |   expression_state MENOS mul_state{ $$ = make_expression_node($1, $3, OP_SUB); }
    |   mul_state
    ;

mul_state:
        mul_state POR primary_state { $$ = make_expression_node($1, $3, OP_MUL); }
    |   mul_state DIVIDIDO primary_state { $$ = make_expression_node($1, $3, OP_DIV); }
    |   primary_state
    ;

primary_state:
        ABRACKET expression_state CBRACKET { $$ = make_expression_node($2, 0, OP_NONE); }
    |   MENOS primary_state	{ $$ = make_expression_node(0, $2, OP_SUB); }
	|	NAME	{ $$ = make_variable_node($1); }
    |   VALNUM  { $$ = make_num_node($1); }
    ;


%%

void yyerror(node_t ** root , char *msg) {
    printf("\n%s\n", msg);
  	exit(1);
}

int main () {
    node_t * root;
    yyparse(&root);
    char * buffer;
    generate_code(root , &buffer);
    FILE * out = fopen("./output/out.c" , "w+");
    fprintf(out , "#include <stdio.h>\n");
    fprintf(out , "#include <stdbool.h>\n");
    fprintf(out ,"int main(void){\n");
    for ( int i = 0 ; buffer[i] != 0 ; i ++){
        fprintf( out , "%c" , buffer[i]);
    }
    fprintf(out,"\nreturn 0;\n");
    fprintf(out , "}");
    pclose(out);
    //printf("%s\n" , generate_code(root));
    return 0;
}   
