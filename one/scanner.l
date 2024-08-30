%{
#include <stdio.h>
#include <ctype.h>

void yyerror(char *s);
int yylex(void);
%}

/* Regular Definitions */
DIGIT   [0-9]
LETTER  [a-zA-Z_]
ID      {LETTER}({LETTER}|{DIGIT})*
KEYWORD "int"|"float"|"return"|"if"|"else"|"while"|"for"
CONST   {DIGIT}+(\.{DIGIT}+)?([eE][-+]?{DIGIT}+)?
STRING  \"([^\\\"]|\\.)*\"
OP      "+"|"-"|"*"|"/"|"="|"<"|">"|"=="|"<="|">="|"!="
SYMBOL  ";"|","|"("|")"|"{"|"}"

/* Rules Section */
%%
{KEYWORD}   { printf("Keyword: %s\n", yytext); }
{ID}        { printf("Identifier: %s\n", yytext); }
{CONST}     { printf("Constant: %s\n", yytext); }
{STRING}    { printf("String: %s\n", yytext); }
{OP}        { printf("Operator: %s\n", yytext); }
{SYMBOL}    { printf("Symbol: %s\n", yytext); }

[ \t\n]+    ;  /* Ignore whitespace */
.           { printf("Unknown: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}

int main(int argc, char **argv) {
    yylex();
    return 0;
}

