%{
#include <stdio.h>
#include <stdlib.h>
#include "arithmetic.h"  // Include the shared header file
%}

/* Define YYSTYPE as Node* */
%union {
    int num;
    Node* node;
}

/* Update the type of the nonterminals */
%token <num> NUM
%type <node> expr

// Operator precedence
%left '+' '-'
%left '*' '/'
%left UMINUS

%%

expr:
    expr '+' expr  { $$ = createNode(0, '+', $1, $3); }
  | expr '-' expr  { $$ = createNode(0, '-', $1, $3); }
  | expr '*' expr  { $$ = createNode(0, '*', $1, $3); }
  | expr '/' expr  { $$ = createNode(0, '/', $1, $3); }
  | '-' expr %prec UMINUS { $$ = createNode(0, '-', NULL, $2); }
  | '(' expr ')'   { $$ = $2; }
  | NUM            { $$ = createNode($1, 0, NULL, NULL); }
  ;

%%

int main() {
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int yylex(void);

