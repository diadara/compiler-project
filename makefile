driver: lexer.h lexer.c driver.c
	clang -Wall -g -o lex lexer.c driver.c
