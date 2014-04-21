#ifndef _AST
#define _AST

#include "parser.h"
typedef struct ast {
  tokenp t;
  int id;
  int lineno;
    struct ast *child[20];
    struct ast *parent;
  //    HashNode symtabentry; 
  //   SymNode funcsymtabentry;
    char* type_chk;
}ast;

typedef ast *AST;

AST A_T;
AST createAST(parseTree);
void initializeAST(parseTree);
void printAST(AST,FILE*);
AST malloc_ast();
void insertAST(parseTree,AST);
void update_ln(AST);
AST getAST(); 



#endif
