%{
#include "symbol_table.h"
#include "parser.tab.h"

extern int yylineno;
extern SymbolTable *sym_table;
%}

digit       [0-9]
letter      [a-zA-Z_]
identifier  {letter}({letter}|{digit})*
number      {digit}+(\.{digit}+)?([eE][+-]?{digit}+)?

%%

{identifier}  {
    yylval.str = strdup(yytext);
    // For this example, assume all identifiers are variables with global scope
    add_symbol(sym_table, yytext, VARIABLE, GLOBAL, yylval.str[0] * 100, yylineno);
    return IDENTIFIER;
}

{number} {
    yylval.str = strdup(yytext);
    return NUMBER;
}

"=" {
    return ASSIGN;
}

";" {
    return SEMICOLON;
}

"+" {
    return PLUS;
}

"-" {
    return MINUS;
}

"*" {
    return MULTIPLY;
}

"/" {
    return DIVIDE;
}

"(" {
    return LPAREN;
}

")" {
    return RPAREN;
}

\n    { yylineno++; }

[ \t]+  ; // Ignore whitespace

.     { return yytext[0]; }

%%

int yywrap() {
    return 1;
}

