
CC = clang -I. -Wall

all: driver

debug: CC += -DDEBUG -g
debug: driver

driver: lexer driver.c  parser
	$(CC) lexer.o parser.o driver.c -o compile
lexer: lexer.c lexer.h
	$(CC) -c lexer.c
parser: parser.c parser.h
	$(CC) -c parser.c
clean:
	rm *.out *.o compile*
