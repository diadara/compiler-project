#include "ast.h"
#include<string.h>
#include<stdio.h>


#define symbol(T) (T->t->s)
#define nextsymbol(T,j)  (T->next[j]->t->s)


void printAST_helper(AST PT, FILE * of)
  {
    int i;
    if(PT==NULL)
      {
        return;
      }
    char parent[20];
    strcpy(parent, symbolToStr(PT->t->s));
    
    char join[10];
    if(PT->t->s == TK_ID || PT->t->s == TK_NUM || PT->t->s == TK_RNUM || PT->t->s == TK_CHR )
      fprintf(of,"%s%d[label=\"%s\"]\n",parent, PT->id, PT->t->lexeme);
    else if (PT->t->s == TK_EPS)
      fprintf(of,"%s%d[label=\"%s\"]\n",parent, PT->id, "eps");
    else
      fprintf(of,"%s%d[label=\"%s\"]\n",parent, PT->id, parent);
      strcpy(join," -- ");
      
    for(i=0;i<20 && PT->child[i]!=NULL;i++)
      fprintf(of, "%s%d%s%s%d\n",parent, PT->id, join,symbolToStr(PT->child[i]->t->s), PT->child[i]->id);
    for(i=0;i<20 && PT->child[i]!=NULL;i++) printAST_helper(PT->child[i],of);


    
  }

void printAST(AST  PT, FILE *of)
{

      fprintf(of, "graph AST { \n");
      printAST_helper(PT, of);     
      fprintf(of, "\n}\n");
}


AST malloc_ast()
{AST A;
  static int id;
   A=malloc(sizeof*A);
  A->id = id++;
   A->parent=NULL;
   int i;
   for(i=0;i<20;i++)
     A->child[i] = NULL;
   //   A->symtabentry=NULL;
   //   A->funcsymtabentry=NULL;
   A->type_chk=NULL;
   return A;
}

void copyPT_to_AST(parseTree PT,AST A)
{
  A->t = PT->t;
  A->lineno = PT->lineno;;
}

void fillchild(AST A, parseTree P)
{
  int i,j=0;
  AST temp;
  for(i=0;i<20;i++)
    {
      if(P->next[i] == NULL) break;
      else{
        temp = createAST(P->next[i]);
        if(temp != NULL)
          {
            temp->parent = A;
            A->child[j++]  = temp;
          }
      }
    }
 }

void  traverse_parsetree(parseTree P, symbol s,AST (*handler_function)(parseTree,AST), AST parent)
{
  if(symbol(P) == s)
    (*handler_function)(P,parent);
  int i = 0;
  while(P->next[i])
    {
      traverse_parsetree(P->next[i],s, handler_function, parent);
      i++;
    }
}

AST handle_id(parseTree PT,AST A)
{
  int i = 0;
  while(A->child[i] != NULL) i++;
  AST temp = malloc_ast();
  temp->t = PT->t;
   A->child[i] = temp;
#ifdef DEBUG
   printf("\nhandling %s %s %d to astnode: %d",symbolToStr(symbol(PT)), PT->t->lexeme, i,A->id);
#endif

   return A;
}

AST handle_globalDeclare(parseTree PT,AST A)
{

#ifdef DEBUG
  printf("\nhandling %s",symbolToStr(symbol(PT)));
#endif
 
  int i = 0;
  while(A->child[i] != NULL) i++;
  AST temp = malloc_ast();
    
  if(PT->next[2]->next[0]->t->s == constructedDatatype)
    {
      temp->t = PT->next[2]->next[0]->next[0]->t;
      temp->child[0] = malloc_ast();
      temp->child[0]->t = PT->next[2]->next[0]->next[1]->t;
      temp->child[0]->child[0] = malloc_ast();
      temp->child[0]->child[0]->t = PT->next[3]->t;

#ifdef DEBUG
      printf("\nhandling %s %s",PT->next[3]->t->lexeme, symbolToStr(PT->next[3]->t->s));
#endif

      A->child[i] = temp;
    }
  else
    {

    }
  return A;
}
AST handle_fieldDefenition(parseTree PT, AST A)
{
#ifdef DEBUG
  printf("\nhandling %s",symbolToStr(symbol(PT)));
#endif
  int i=0;
    while(A->child[i] != NULL) i++;
  A->child[i] = malloc_ast();
  A->child[i]->t = PT->next[1]->next[0]->t;
  traverse_parsetree(PT,TK_ID,handle_id,A->child[i]);

  return A;  
}

AST handle_typedefinitions(parseTree PT, AST A)
{
#ifdef DEBUG
  printf("\nhandling %s",symbolToStr(symbol(PT)));
#endif
  int i=0;
  while(A->child[i] != NULL) i++;
  AST temp = malloc_ast();
  temp->t = PT->next[0]->t;
  temp->child[0] = malloc_ast();
  temp->child[0]->t = PT->next[1]->t;
  temp->child[0]->child[0] = malloc_ast();
  temp->child[0]->child[0]->t = malloc(sizeof(token));
  temp->child[0]->child[0]->t->s = fieldDefinition_s;
  traverse_parsetree(PT->next[2],fieldDefinition,handle_fieldDefenition,temp->child[0]->child[0]);
   A->child[i] = temp;
  return A;
}


AST createAST(parseTree T)
{
  AST A = NULL; 

  switch(symbol(T))
    {
    case program:
      A =  malloc_ast();
      copyPT_to_AST(T,A);
      fillchild(A,T);
      break;
    case typeDefinition_s:
      A =  malloc_ast();
      copyPT_to_AST(T,A);
      traverse_parsetree(T,typeDefinition,handle_typedefinitions,A);
      if(A->child[0] == NULL)
        {
          free(A);
          A=NULL;
        }
      break;
    case globalStatements:
      A =  malloc_ast();
      copyPT_to_AST(T,A);
      traverse_parsetree(T,globalDeclare,handle_globalDeclare,A);
      if(A->child[0] == NULL)
        {
          free(A);
          A=NULL;
        }
      break;
    default:
      A =  malloc_ast();
      copyPT_to_AST(T,A);
      fillchild(A,T);
      if(A->child[0] == NULL)
        {
          free(A);
          A=NULL;
        }
      break;
      

    }
  

  return A;
}
