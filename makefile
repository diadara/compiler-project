
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
parsetable: parseTable.h parseTable.c
	$(CC) -c parseTable.c
clean:
	rm *.out *.o compile* firsts *.ps *.dot *.csv
parsetree: parsetree.dot
	dot -Tps  parsetree.dot -o parsetree.ps
