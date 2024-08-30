%{
#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"

extern int yylineno;
extern int yylex();
SymbolTable *sym_table;

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}
%}

%union {
    char *str;
}

%token <str> IDENTIFIER NUMBER
%token ASSIGN SEMICOLON PLUS MINUS MULTIPLY DIVIDE LPAREN RPAREN

%type <str> expression term factor

%%

program:
    program statement
    | /* empty */
    ;

statement:
    IDENTIFIER ASSIGN expression SEMICOLON {
        printf("Assignment: %s = %s\n", $1, $3);
        free($1);
        free($3);
    }
    ;

expression:
    term
    | expression PLUS term {
        printf("Expression: %s + %s\n", $1, $3);
        $$ = strdup($1); // Simplified - you could implement actual computation logic here
        free($1);
        free($3);
    }
    | expression MINUS term {
        printf("Expression: %s - %s\n", $1, $3);
        $$ = strdup($1);
        free($1);
        free($3);
    }
    ;

term:
    factor
    | term MULTIPLY factor {
        printf("Term: %s * %s\n", $1, $3);
        $$ = strdup($1);
        free($1);
        free($3);
    }
    | term DIVIDE factor {
        printf("Term: %s / %s\n", $1, $3);
        $$ = strdup($1);
        free($1);
        free($3);
    }
    ;

factor:
    NUMBER {
        $$ = strdup($1);
        printf("Number: %s\n", $1);
        free($1);
    }
    | IDENTIFIER {
        $$ = strdup($1);
        printf("Identifier: %s\n", $1);
    }
    | LPAREN expression RPAREN {
        $$ = strdup($2);
        free($2);
    }
    ;

%%

int main() {
    sym_table = create_table();
    yyparse();
    print_symbol_table(sym_table);  // Print the symbol table at the end
    free_table(sym_table);
    return 0;
}

