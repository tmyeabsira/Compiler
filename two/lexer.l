%{
#include "arithmetic.h"
#include "arithmetic.tab.h"
%}

%%

[0-9]+  { yylval.num = atoi(yytext); return NUMBER; }
[ \t]   ; /* ignore whitespace */
\n      return 0;
.       return yytext[0];

%%

int yywrap(void) {
    return 1;
}
