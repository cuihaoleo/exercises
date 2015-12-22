%{
#include "regex.tab.h"

void yyerror(char const *message) {
    printf("%s\n",message);
}
%}

%%
[a-zA-Z0-9.] {
    yylval.charactor = *yytext;
    return CHARACTOR;
}
"|"        return OR;
"*"        return STAR;
"("        return LPAREN;
")"        return RPAREN;
<<EOF>>    return EOL;
"\n"       return EOL;
.          return UNKNOWN;
%%

int main(int argc, char *argv[]) {
    int return_value = yyparse();
    yylex_destroy();
    return return_value;
}
