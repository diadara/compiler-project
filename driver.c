#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include"lexer.h"
#include"parser.h"
#include<stdio.h>
#include<stdlib.h>
#include "parseTable.h"


int main(int argc, char* argv[])
{
  int fp;
  bool error = FALSE;
  if(argc == 2)
     fp = open(argv[1],O_RDONLY);
  else
    { printf("no input file given");
      exit(1);
    }
  
    

  keywordTable kt = createKeywordTable();

  FILE * g = fopen("newGram.txt","r");
  
  if(g==NULL)
    {
        printf("Grammar file not found\n");
        return 0;
    }

#ifdef DEBUG
  printf("Grammar file opened\n");
#endif
  grammar G[200];
  keywordTable nt = createNtTable();
  int gno = createGrammar(g,G,nt);

#ifdef DEBUG
  printf("%d rules read from Grammar", gno);
#endif

 ParseTable PT  = getParseTable();


 //printRule(G,PT.T[globalStatements - program][TK_MAIN]);
   parseTree P = parseInputSourceCode(fp, kt, G,&error);

  /* FILE * pt = fopen("parsetree","w"); */
  
  /* printParseTree(P,pt); */
  
    return 0;
}

