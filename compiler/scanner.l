%option noyywrap

%{
// declaraciones en C and what not
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

%}

stringregexp      \'[^\']+\'
varname         [A-Za-z_]+
valnum          [+-]?([0-9]*[.])?[0-9]+

%%

    /*variables*/
"num"   {return INT; }
"s"     {return STRING; }
"if"    {return IF; }
"fi"    {return FI; }
"do"    {return DO; }
"ps"    {return PS; }
"pi"    {return PI; }
"w"     {return W; }
    /*operadores */
"="     {return IGUAL; }
"+"     {return MAS; }
"-"     {return MENOS; }
"*"     {return POR; }
"/"     {return DIVIDIDO; }
"%"     {return MODULO; }
"["     {return ABRACKET; }
"]"     {return CBRACKET; }
    /*comparadores*/
"eq"    {return EQ; }
"ne"    {return NE; }
"lt"    {return LT; }
"le"    {return LE; }
"gt"    {return GT; }
"ge"    {return GE; }
    /*caracteres nativos*/
[ \t]+     /*ignore whitespace*/
\n      { printf("llegue al barra n \n");
    return NEWLINE; }



    /*NAME*/
{varname}  {
        printf("recibi un name \n");
        return NAME;
    }
    /*VALNUM*/
{valnum}  {
        printf("recibi un num \n");
        return VALNUM;
    }

    /*VALSTRING*/
{stringregexp}    {
        printf("recibi un string \n");
        return VALSTRING;
    }

%%



