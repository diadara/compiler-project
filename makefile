
CC = clang -I.
ccd = $(CC)
ccd += -DDEBUG -g -Wall

driver: lexer driver.c  parser
	$(CC) lexer.o parser.o driver.c -o compile
debug: lexer driver.c  parser
	$(ccd) lexer.o parser.o driver.c -o compiledebug
lexer: lexer.c lexer.h
	$(CC) -c lexer.c
parser: parser.c parser.h
	$(CC) -c parser.c
clean:
	rm *.out *.o compile*
