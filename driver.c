#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include"lexer.h"
#include<stdio.h>
#include<stdlib.h>



int main(int argc, char* argv[])
{int fp,back=0;
  if(argc == 2)
     fp = open(argv[1],O_RDONLY);
  else
    { printf("no input file given");
      exit(1);
    }
  char c=' ';
  while(c != EOF)
    {
      printf("%c",c);
      c = getNextChar(fp,&back);
    }
    

  keywordTable kt = createKeywordTable();
  /* int i; */
  /* for(i = 0;i<60;i++) */
  /*   printf("%s %d\n", kt[i].keyword, kt[i].s); */
    

    return 0;
}

