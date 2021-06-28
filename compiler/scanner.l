%option noyywrap

%{
// declaraciones en C and what not
#include <stdio.h>
#include <stdlib.h>
#include "node_t.h"
#include "y.tab.h"
%}

stringregexp      \'[^\']*\'
varname         [A-Za-z_]+
valnum          [+-]?[0-9]+
spaces          \n[ \t\n\r]*
%%

    /*variables*/
"num"   {return INT; }
"s"     {return STRINGT; }
"if"    {return IF; }
"fi"    {return FI; }
"do"    {return DO; }
"ps"    {return PS; }
"pi"    {return PI; }
"w"     {return W; }
"b"     {return BOOL; }

    /*estados booleanos*/
"t"     {return TRUET; }
"f"     {return FALSET; }

    /*operadores */
"="     {return IGUAL; }
"add"     {return MAS; }
"sub"     {return MENOS; }
"mul"     {return POR; }
"div"     {return DIVIDIDO; }
"["     {return ABRACKET; }
"]"     {return CBRACKET; }

    /*comparadores*/
"eq"    {return EQ; }
"ne"    {return NE; }
"lt"    {return LT; }
"le"    {return LE; }
"gt"    {return GT; }
"ge"    {return GE; }
"and"   {return AND; }
"or"    {return OR; }
    /*caracteres nativos*/
[ \t]+     /*ignore whitespace*/

{spaces}  { return NEWLINE; }



    /*NAME*/
{varname}  {

        strcpy(yylval.buffer , yytext);
        return NAME;
    }
    /*VALNUM*/
{valnum}  {
        strcpy(yylval.buffer , yytext);
        return VALNUM;
    }

    /*VALSTRING*/
{stringregexp}    {
        int len= strlen(yytext);
        yytext[len -1] = 0;
        strcpy(yylval.buffer , yytext+1);
        return VALSTRING;
    }

%%



