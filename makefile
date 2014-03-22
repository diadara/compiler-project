
CC = clang -Wall  -o lex lexer.c driver.c 
ccd = $(CC)
ccd += -DDEBUG -g

driver: lexer.h lexer.c driver.c
	$(CC)
debug: lexer.h lexer.c driver.c
	$(ccd)
