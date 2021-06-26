%option noyywrap

%{
// declaraciones en C and what not
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

%}

stringregexp      \'[^\']*\'
varname         [A-Za-z0-9_-]+
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
[ \t]+       /*ignore whitespace*/
\n      {return NEWLINE; }



    /*NAME*/
varname  {
        //llamada a lo que haga salus para guardar strings
        return NAME;
    }
    /*VALNUM*/
valnum  {
        //llamada a lo que haga salus para guardar strings
        return VALNUM;
    }

    /*VALSTRING*/
stringregexp    {
        //llamada a lo que haga salus para guardar strings
        return VALSTRING;
    }

%%



