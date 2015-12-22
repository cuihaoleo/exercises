%{
#include <stdio.h>
#include <stdarg.h>
#include "tree_node.h"

int yylex (void);
void yyerror (char const *);
%}

%code requires {
#include "tree_node.h"

struct st_node_record {
    TreeNode *pt_node;
    TreeNode *st_node;
};

extern struct st_node_record roots;
}

%union {
    struct st_node_record nodes;
    char charactor;
}

%token CHARACTOR
%token OR
%token STAR
%token EOL
%token LPAREN RPAREN

%type <nodes> regex concat atom
%type <charactor> CHARACTOR

%%
input   : regex EOL {
    roots = $1;
};

regex   : concat OR regex {
    $$.pt_node = mkNode("regex", 3, $1.pt_node, mkLeaf("OP_OR"), $3.pt_node);
    $$.st_node = mkNode("OP_OR", 2, $1.st_node, $3.st_node);
}
        | concat {
    $$.pt_node = mkNode("regex", 1, $1.pt_node);
    $$.st_node = $1.st_node;
};

concat  : atom concat {
    $$.pt_node = mkNode("concat", 3, $1.pt_node, \
                        mkLeaf("OP_CONCAT"), $2.pt_node);
    $$.st_node = mkNode("OP_CONCAT", 2, $1.st_node, $2.st_node);
}
        | atom {
    $$.pt_node = mkNode("concat", 1, $1.pt_node);
    $$.st_node = $1.st_node;
};

atom    : atom STAR {
    $$.pt_node = mkNode("atom", 2, $1.pt_node, mkLeaf("OP_STAR"));
    $$.st_node = mkNode("OP_STAR", 1, $1.st_node);
}
        | LPAREN regex RPAREN {

    $$.pt_node = mkNode("atom", 3, mkLeaf("OP_LPAREN"), \
                        $2.pt_node, mkLeaf("OP_RPAREN"));
    $$.st_node = $2.st_node;
}
        | CHARACTOR {
    char tmp[] = "CHAR(?)";
    tmp[5] = $1;
    $$.pt_node = mkNode("atom", 1, mkLeaf(tmp));
    $$.st_node = mkLeaf(tmp);
};
%%
