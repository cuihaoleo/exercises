%{
#include "regex.tab.h"

struct st_node_record roots = {NULL, NULL};

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
\n         return EOL;
.          {
    yyerror("Illegal character"); 
    return(EOL);
}
%%

int main(int argc, char *argv[]) {
    char input[256];
    int return_value = 0;

    fgets(input, sizeof(input), stdin);

    YY_BUFFER_STATE buf = yy_scan_string(input);
    yy_switch_to_buffer(buf);

    return_value = yyparse();

    yy_delete_buffer(buf);
    yylex_destroy();

    if (return_value == 0) {
        printf("Parse Tree:\n");
        printTree(*(roots.pt_node));

        printf("\nSyntax Tree:\n");
        printTree(*(roots.st_node));
    }

    if (roots.pt_node)
        destroyTree(roots.pt_node);
    if (roots.st_node)
        destroyTree(roots.st_node);

    return return_value;
}
