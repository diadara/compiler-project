#include"lexer.h"
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

int getStream(int fp, buffer B, buffersize k)//reads k characters from source file into buffer B
{
 
    int amtRead=0;
    amtRead = read(fp,B,k);
    return amtRead;


}


char getNextChar(int fp, int *back)//gets next character from source file at position x
{
    static int x=0,k=2000,y;
    static char cb1[2000];
    static char cb2[2000];
    buffer b1=cb1;
    buffer b2=cb2;
    int flag=0;
    x%=k*2;
    //printf("x = %d\n",x);
    if(*back>=1)
    {
        x-=*back;
        x+=k*2;
        x%=k*2;
        *back=0;
    }
    else
    {
        if(x==0)
        {
            y=getStream(fp, b1, k);
            flag=0;
        }
        else if(x==k)
        {
            y=getStream(fp, b2, k);
            flag=1;
        }
    }
    if(x>=y+flag*k&&y<k)
    {
        x++;
        return (char)EOF;
    }
    if(x<k)
        return b1[x++];
    return b2[x++ - k];
}


int hash(char *keyword, int hashkey)//hash function
{
    int hash=0,mul=3,i=0;
    while(keyword[i]!='\0')
        hash=(hash*mul+keyword[i++])%hashkey;
    return hash;
}

void addKeyword(keywordTable kt, char *keyword, symbol s)//recursively called to add keyword to keywordTable
{
    int hval,hashkey=60;//twice #no of keywords
    hval=hash(keyword,hashkey);
    while(kt[hval].present==TRUE)
        hval=(++hval)%hashkey;
    strcpy(kt[hval].keyword, keyword);
    kt[hval].present=TRUE;
    kt[hval].s=s;
}


keywordTable createKeywordTable()
{int n = 60;// almost twice as number of keywords
  keywordTable kt = malloc(n * sizeof *kt);
  int i;
  for(i=0;i<n;i++)
    (kt+i)->present = FALSE;

  addKeyword(kt, "map_insert", TK_MAPINSERT);
  addKeyword(kt, "map_remove",TK_MAPREMOVE);
  addKeyword(kt, "assign", TK_ASSIGN);
  addKeyword(kt, "var", TK_VAR);
  addKeyword(kt, "main", TK_MAIN);
  addKeyword(kt, "end_main", TK_ENDMAIN);
  addKeyword(kt, "if", TK_IF);
  addKeyword(kt, "end_if", TK_ENDIF);
  addKeyword(kt, "global", TK_GLOBAL);
  addKeyword(kt, "input", TK_INPUT);
  addKeyword(kt, "output", TK_OUTPUT);
  addKeyword(kt, "while", TK_WHILE);
  addKeyword(kt, "end_while", TK_ENDWHILE);
  addKeyword(kt, "int", TK_INT);
  addKeyword(kt, "real", TK_REAL);
  addKeyword(kt, "char", TK_CHAR);
  addKeyword(kt, "function", TK_FUNCTION);
  addKeyword(kt, "end_function", TK_ENDFUNCTION);
  addKeyword(kt, "elseif", TK_ELSEIF);
  addKeyword(kt, "else", TK_ELSE);
  addKeyword(kt, "record", TK_RECORD);
  addKeyword(kt, "end_record", TK_ENDRECORD);
  addKeyword(kt, "array", TK_ARRAY);
  addKeyword(kt, "map", TK_MAP);
  addKeyword(kt, "get", TK_GET);
  addKeyword(kt, "put", TK_PUT);
  addKeyword(kt, "puts", TK_PUTS);
  addKeyword(kt, "return", TK_RETURN);
  addKeyword(kt, "break", TK_BREAK);
  addKeyword(kt, "call", TK_CALL);
  
  return kt;
}

bool isKeyword(keywordTable kt, char * lexeme)
{
int hval,hashkey=60;//twice the no. of keywords
    hval=hash(lexeme,hashkey);
    while(1)
    {
        if(kt[hval].present==FALSE)
        {
            return FALSE;
        }
        else if(!strcmp(lexeme,kt[hval].keyword))
        {
          return TRUE;
        }
        hval++;
        hval=hval%hashkey;
    }
}


