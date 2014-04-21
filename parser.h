
#ifndef _PARSER
#define _PARSER
#include "lexer.h"
#include<stdlib.h> 
#include<stdio.h>


typedef struct
{
    symbol nt;
    int ruleNumber;
    symbol list[20];
    int listno;

} grammar;

typedef int Table;

struct parsetree
{
    tokenp t;
    int ruleno;//used by AST to know which grammar rule was applied for the non-terminal,for terminals it is -1
    int lineno;
    struct parsetree* parent;
    bool visited;
  int pull;
  int nochild;
  int id; // for identifying while  drawing parsetree
    struct parsetree* next[20];//assuming length of RHS of rules is bounded by 20 
};

typedef struct parsetree* parseTree;



struct stackNode
{
    parseTree tree;//to Parse Tree 
    struct stackNode* next;
};

typedef struct
{
    struct stackNode* top;
    int size;
}Stack;


keywordTable createNtTable();
parseTree parseInputSourceCode(int fp, keywordTable kt, grammar g[], bool*error);
void printParseTree(parseTree  PT, FILE *outfile);
symbol toSym(char *a, keywordTable nt);//return Symbol for given string
int createGrammar(FILE * fp,grammar G[], keywordTable nt);//load grammar from text file
void addNt(keywordTable nt, char *keyword, symbol s);//recursively called to add non-terminal to non-terminal Table
void initNt(keywordTable nt);//initialize non-terminals table
void initTable(Table T[][200]);//initialize parser table with no rule
void addtoTable(symbol nt, symbol t, int ruleno, Table T[][200]);//insert rule in table
bool isTerminal(symbol s);//returns true if given symbol is terminal
void printRule(grammar G[], int ruleno);
parseTree createParseNode(symbol s,int lineno);
struct stackNode* createStackNode(parseTree tree);
Stack push(Stack S,parseTree tree);
Stack pop(Stack S);
void copyTree(parseTree A , parseTree B);
parseTree parseInputSourceCode(int fp, keywordTable kt, grammar g[], bool*error);





#endif
