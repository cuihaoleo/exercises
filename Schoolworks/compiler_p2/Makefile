SRC	 = src
BIN	 = bin
CC       = gcc -g3 -I$(SRC)
LEX      = flex -i -I 
YACC     = bison -d -y

all: regex

regex:
	$(YACC) -b $@ -o $(SRC)/$@.tab.c $@.y
	$(LEX) -o $(SRC)/$@.lex.c $@.lex
	$(CC) -o $(BIN)/$@ $(SRC)/tree_node.c $(SRC)/$@.lex.c $(SRC)/$@.tab.c -ll

clean:
	rm -f $(SRC)/*.tab.h $(SRC)/*.tab.c
	rm -f $(SRC)/*.lex.c *.out
	rm -f $(BIN)/*
