#include"lexer.h"
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>

/* Finalize token macro   */
#define fin_token(symbol)  lexeme[i] = '\0';  \
              t = malloc(sizeof *t); \
              t->s = symbol;   \
              strcpy(t->lexeme,lexeme); \
              return t;

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


/* returns -1 if not a keyword else returns the keywords symbol */
int isKeyword(keywordTable kt, char * lexeme)
{
int hval,hashkey=60;//twice the no. of keywords
    hval=hash(lexeme,hashkey);
    while(1)
    {
        if(kt[hval].present==FALSE)
        {
            return -1;
        }
        else if(!strcmp(lexeme,kt[hval].keyword))
        {
          return kt[hval].s;
        }
        hval++;
        hval=hval%hashkey;
    }
}



tokenp getNextToken(int fp, keywordTable kt, bool *error, int * linenumber)
{
  tokenp t;
  static int state =1, back = 0;
  int i= 0;
  char lexeme[100] = {},c; //assuming lexemes to be not more that 100
                    //characters long
  while(1)
    {
      c = getNextChar(fp, &back);
      switch(state)
        {
        case 1:


          if((int)c == EOF) return NULL;
          else if(c == ':')
            {
              lexeme[i++] = c;
              fin_token(TK_ASSIGNOP);
            }
          else if(c == ';')
            {
              lexeme[i++] = c;
              fin_token(TK_SEM);
            }
          else if(c == ',')
            {
              lexeme[i++] = c;
              fin_token(TK_COMMA);
            }
          else if(c == '(')
            {
              lexeme[i++] = c;
              fin_token(TK_OP);
            }
          else if(c == ')')
            {
              lexeme[i++] = c;
              fin_token(TK_CL)
            }
          else if(c == '+')
            {
              lexeme[i++] = c;
              fin_token(TK_PLUS)
            }
          else if(c == '-')
            {
              lexeme[i++] = c;
              fin_token(TK_MINUS);
            }
          else if(c == '*')
            {
              lexeme[i++] = c;
              fin_token(TK_MUL);
            }
          else if(c == '/')
            {
              lexeme[i++] = c;
              fin_token(TK_DIV);
            }
          else if(c == '%')
            {
              lexeme[i++] = c;
              fin_token(TK_MOD);
            }
          else if(c == '&')
            {
              lexeme[i++] = c;
              fin_token(TK_AND);
            }
          else if(c == '|')
            {
              lexeme[i++] = c;
              fin_token(TK_OR);
            }
          else if(c == '[')
            {
              lexeme[i++] = c;
              fin_token(TK_SQL);
            }
          else if(c == ']')
            {
              lexeme[i++] = c;
              fin_token(TK_SQR);
            }
          else if(c == '.')
            {
              lexeme[i++] = c;
              fin_token(TK_DOT);
            }
          else if(c == '!')
            {
              lexeme[i++] = c;
              state = 2;
            }
          else if(c == '<')
            {
              lexeme[i++] = c;
              state = 3;
            }
          else if(c == '>')
            {
              lexeme[i++] = c;
              state = 4;
            }
          else if(c == '=')
            {
              lexeme[i++] = c;
              state = 5;
            }
          else if (c == '#')
            {
              lexeme[i++] = c;
              state = 6;
            }
          else if(isspace(c))
            {
              if(c == '\n')
                (*linenumber) ++;
            }
          else if(c == '"')
            {
              lexeme[i++]= c;
              state = 7;
              fin_token(TK_DQT);
              
            }
          else if(c == '\'')
            {
              lexeme[i++] = c;
              state = 8;
              fin_token(TK_SQT);
            }
          else if(isalpha(c) || c == '_')
            {
              lexeme[i++] = c;
              state = 11;
            }
          else if(isdigit(c))
            {
              lexeme[i++] = c;
              state = 12;
            }
          else
            {lexeme[i++] = c;
              *error =1;        /* we do not recognize the character */
              fin_token(TK_ERROR);
            }
          break;
        case 2:
          if(c != '=')
            {
              back = 1;
              state = 1;
              fin_token(TK_NOT);
            }
          else
            {
              lexeme[i++] = c;
              state = 1;
              fin_token(TK_EQ);
            }
          break;
        case 3:
          if(c != '=')
            {
              back = 1;
              state = 1;
              fin_token(TK_LT);
            }
          else
            {
              lexeme[i++] = c;
              state = 1;
              fin_token(TK_LE);
            }
          break;
        case 4:
          if(c != '=')
            {
              back = 1;
              state = 1;
              fin_token(TK_GT);
            }
          else
            {
              lexeme[i++] = c;
              state = 1;
              fin_token(TK_GE);
            }
          break;
        case 5:
          if(c != '=')
            {
              back = 1;
              state = 1;
              *error = 1;       /* = is an unrecognized lexeme */
              fin_token(TK_ERROR);
            }
          else
            {
              lexeme[i++] = c;
              state = 1;
              fin_token(TK_EQ);
            }
          break;
        case 6:                 /* comment case, comment started */
          if(c == '\n')
            {
              state = 1;
              back =1;
              fin_token(TK_COMMENT);
            }
          else
            {
              lexeme[i++] = c;
            }
          break;
        case 7:
          if (c != '"')
            {
              lexeme[i++] = c;
              if(c =='\n')
                (*linenumber)++;
            }
          else
            {back = 1;
              state = 9;
              fin_token(TK_STRING);
            }
          
          break;
        case 8:          /* single quote state */
          lexeme[i++] = c;
          state = 10;
          fin_token(TK_CHAR);
          break;
        case 9:                 /* finished reading a string */
          lexeme[i++] = c;
          state = 1;
          fin_token(TK_DQT);
          break;
        case 10:
          if (c != '\'')
            {lexeme[i++] = c;
              fin_token(TK_ERROR);
            }
          else{
            lexeme[i++] = c;
            state = 1;
            fin_token(TK_SQT);
          }
          break;
        case 11:
          if(isalnum(c) || c == '_')
            lexeme[i++] = c;
          else
            {
              back = 1;
              int  keyword = isKeyword(kt, lexeme); /* -1 if
                                                           keyword
                                                           else a symbol */
              if(keyword < 0)
                {
                  state = 1;
                  fin_token(TK_ID);
                }
              else
                {
                  state = 1;    /* TODO : handle different types of
                                   ids according to keywords that
                                   comes before */
                  fin_token(keyword);
                }
            }
          break;
        case 12: // number case
          if(isdigit(c))
            {
              lexeme[i++] = c;
            }
          else if(c == '.')
            {
              lexeme[i++] = c;
              state = 13 ;      /* real number state */
            }
          else
            {
              state = 1;
              back = 1;
              fin_token(TK_NUM);
            }
          break;
        case 13:
          if(isdigit(c))
            {
              lexeme[i++] = c;
            }
          else{
            back = 1;
            state = 1;
            fin_token(TK_RNUM);
          }
          break;
        }//switch


    }//while

  

}




tokenlistp getTokenlist(int fp, keywordTable kt)
{
  bool error;
  int linenumber=1;
  tokenlistp tl;
  int flag = 0;
  tokenlistp current;
  tokenp t = getNextToken(fp,kt,&error, &linenumber);
  while(t != NULL)
    {
#ifdef DEBUG
      printf("%s \n", symbolToStr(t->s));
#endif
      
      tokenlistp temp = malloc(sizeof *temp);
      temp->t = t;
      temp->linenumber = linenumber;
      temp->next = NULL;
      if(flag)
        {
          current->next = temp;
          current = current->next;
        }
      else
        {
          tl = temp;
          current = temp;
          flag++;
        }
       t = getNextToken(fp,kt,&error, &linenumber);
    }
  return tl;
}


char * symbolToStr(symbol s)
{
 switch(s)
   {
   case TK_ASSIGNOP:
     return "TK_ASSIGNOP";
   case TK_FIELDID:
     return "TK_FIELDID";
   case TK_ID:
     return "TK_ID";
   case TK_NUM:
     return "TK_NUM";
   case TK_RNUM:
     return "TK_RNUM";
   case TK_STRING:
     return "TK_STRING";
   case TK_FUNID:
     return "TK_FUNID";
   case TK_RECORDID:
     return "TK_RECORDID";
   case TK_ARRAYID:
     return "TK_ARRAYID";
   case TK_MAPID:
     return "TK_MAPID";
   case TK_MAPFIELD:
     return "TK_MAPFIELD";
   case TK_MAPINSERT:
     return "TK_MAPINSERT";
   case TK_MAPREMOVE:
     return "TK_MAPREMOVE";
   case TK_ASSIGN:
     return "TK_ASSIGN";
   case TK_VAR:
     return "TK_VAR";
   case TK_MAIN:
     return "TK_MAIN";
   case TK_ENDMAIN:
     return "TK_ENDMAIN";
   case TK_INT:
     return "TK_INT";
   case TK_REAL:
     return "TK_REAL";
   case TK_IF:
     return "TK_IF";
   case TK_ENDIF:
     return "TK_ENDIF";
   case TK_GLOBAL:
     return "TK_GLOBAL";
   case TK_INPUT:
     return "TK_INPUT";
   case TK_OUTPUT:
     return "TK_OUTPUT";
   case TK_WHILE:
     return "TK_WHILE";
   case TK_ENDWHILE:
     return "TK_ENDWHILE";
   case TK_CHAR:
     return "TK_CHAR";
   case TK_FUNCTION:
     return "TK_FUNCTION";
   case TK_ENDFUNCTION:
     return "TK_ENDFUNCTION";
   case TK_ELSEIF:
     return "TK_ELSEIF";
   case TK_ELSE:
     return "TK_ELSE";
   case TK_RECORD:
     return "TK_RECORD";
   case TK_ENDRECORD:
     return "TK_ENDRECORD";
   case TK_ARRAY:
     return "TK_ARRAY";
   case TK_MAP:
     return "TK_MAP";
   case TK_GET:
     return "TK_GET";
   case TK_PUT:
     return "TK_PUT";
   case TK_PUTS:
     return "TK_PUTS";
   case TK_RETURN:
     return "TK_RETURN";
   case TK_BREAK:
     return "TK_BREAK";
   case TK_CALL:
     return "TK_CALL";
   case TK_SQL:
     return "TK_SQL";
   case TK_SQR:
     return "TK_SQR";
   case TK_SEM:
     return "TK_SEM";
   case TK_COMMA:
     return "TK_COMMA";
   case TK_DOT:
     return "TK_DOT";
   case TK_OP:
     return "TK_OP";
   case TK_CL:
     return "TK_CL";
   case TK_DQT:
     return "TK_DQT";
   case TK_SQT:
     return "TK_SQT";
   case TK_PLUS:
     return "TK_PLUS";
   case TK_MINUS:
     return "TK_MINUS";
   case TK_MUL:
     return "TK_MUL";
   case TK_DIV:
     return "TK_DIV";
   case TK_MOD:
     return "TK_MOD";
   case TK_AND:
     return "TK_AND";
   case TK_OR:
     return "TK_OR";
   case TK_NOT:
     return "TK_NOT";
   case TK_LT:
     return "TK_LT";
   case TK_LE:
     return "TK_LE";
   case TK_EQ:
     return "TK_EQ";
   case TK_GT:
     return "TK_GT";
   case TK_GE:
     return "TK_GE";
   case TK_NE:
     return "TK_NE";
   case TK_COMMENT:
     return "TK_COMMENT";
   case TK_ERROR:
     return "TK_ERROR";
   }
}

void printTokenList(tokenlistp tl)
{
  while(tl != NULL)
    {
      printf("%d  %s %s \n", tl->linenumber, symbolToStr(tl->t->s), tl->t->lexeme);
      tl = tl->next;
    }

}
