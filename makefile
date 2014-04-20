
CC = clang -I. -Wall

all: driver

debug: CC += -DDEBUG -g
debug: driver

driver: lexer driver.c  parser parsetable
	$(CC) lexer.o parser.o driver.c parseTable.o  -o compile
lexer: lexer.c lexer.h
	$(CC) -c lexer.c
parser: parser.c parser.h
	$(CC) -c parser.c
ast: ast.c ast.h
	$(CC) -c ast.c
parsetable: parseTable.h parseTable.c
	$(CC) -c parseTable.c
clean:
	rm *.out *.o compile* firsts *.ps *.dot *.csv
test3: debug 
	./compile test3.txt
	dot -Tps  parsetree.dot -o parsetree.ps
	dot -Tps ast.dot -o ast.ps

.PHONY: parser driver parsetree test3 lexer debug clean ast
