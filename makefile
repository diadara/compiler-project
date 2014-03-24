
CC = clang -Wall  
ccd = $(CC)
ccd += -DDEBUG -g

driver: lexer driver.c  parser
	$(CC) lexer.o parser.o driver.c
driver: lexer driver.c  parser
	$(ccd) lexer.o parser.o driver.c
lexer: lexer.c lexer.h
	$(CC) -c lexer.c
parser: parser.c parser.h
	$(CC) -c parser.c
clean:
	rm *.out *.o
