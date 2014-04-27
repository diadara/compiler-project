#include "ast.h"
#include<string.h>
#include<stdio.h>


#define symbol(T) ((T)->t->s)
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
    {
#ifdef DEBUG
      printf("\n traverse: found %s", symbolToStr(symbol(P)));
#endif

      (*handler_function)(P,parent);
    }
  int i = 0;
  while(P->next[i])
    {
      traverse_parsetree(P->next[i],s, handler_function, parent);
      i++;
    }
}

AST handle_function(parseTree PT,AST A)
{

  A->child[0] = malloc_ast();
  A->child[0]->parent = A;
  copyPT_to_AST(PT->next[2],A->child[0]);
  fillchild(A->child[0],PT->next[2]); /* input */

  A->child[1] = malloc_ast();
    A->child[1]->parent = A;
  copyPT_to_AST(PT->next[3],A->child[1]);
  fillchild(A->child[1],PT->next[3]); /* output */

  A->child[2] = malloc_ast();
    A->child[2]->parent = A;
  copyPT_to_AST(PT->next[4],A->child[2]);
  fillchild(A->child[2],PT->next[4]); /* output */
  

   return A;
}


AST handle_id(parseTree PT,AST A)
{
  int i = 0;
  while(A->child[i] != NULL) i++;
  AST temp = malloc_ast();
  temp->t = PT->t;
  temp->parent =A;
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
      temp->child[0]->parent = temp;
      temp->child[0]->t = PT->next[2]->next[0]->next[1]->t;
      temp->child[0]->child[0] = malloc_ast();
      temp->child[0]->child[0]->parent = temp->child[0];
      temp->child[0]->child[0]->t = PT->next[3]->t;

#ifdef DEBUG
      printf("\nhandling %s %s",PT->next[3]->t->lexeme, symbolToStr(PT->next[3]->t->s));
#endif

      A->child[i] = temp;
      temp->parent = A;
    }
  else
    {
      temp->t = PT->next[2]->next[0]->next[0]->t;
      temp->child[0] = malloc_ast();
      temp->child[0]->parent = temp;
      temp->child[0]->t = PT->next[3]->t;
      A->child[i] = temp;
      temp->parent = A;
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
  A->child[i]->parent =A ;
  A->child[i]->t = PT->next[1]->next[0]->t;
  traverse_parsetree(PT,TK_ID,handle_id,A->child[i]);

  return A;  
}

AST handle_morevariable(parseTree PT,AST A)
{
    
  if(symbol(PT->next[0]) == TK_EPS)
    A=NULL;
  if(symbol(PT->next[0]) == variable)
    {
      if(symbol(PT->next[1]->next[0]) == arithmeticExpression)
      A = createAST(PT->next[0]);
      if(symbol(PT->next[1]->next[0]) == Operator)
        {
          A = malloc_ast();
          A->t = PT->next[1]->next[0]->next[0]->t;
          A->child[0] = createAST(PT->next[0]);
          A->child[1] = createAST(PT->next[1]->next[1]);
        }
      
    }
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
      /* A = malloc_ast(); */
      /* copyPT_to_AST(T,A); */
      /* traverse_parsetree(T,) */
      break;
    case function:
      A =  malloc_ast();
      copyPT_to_AST(T->next[1],A);
#ifdef DEBUG
      printf("\n in case function: handling %s", T->next[1]->t->lexeme);
#endif

        handle_function(T,A);
      break;
    case mainFunction:
      A =  malloc_ast();
      copyPT_to_AST(T,A);
      A->child[0] = malloc_ast();
      copyPT_to_AST(T->next[1],A->child[0]);
      fillchild(A->child[0], T->next[1]);
      break;
    case assignmentStmt:
      A =  malloc_ast();
      copyPT_to_AST(T->next[2],A);
      A->child[0] = createAST(T->next[1]);
      A->child[1] = createAST(T->next[3]);
   
      break;
       case arithmeticExpression:
#ifdef DEBUG
      printf("\n in case of arithmetic: handling %s", symbolToStr(symbol(T)));
#endif
         A = handle_morevariable(T,A);
         if(A != NULL)
           if(A->child[0] == NULL)
             A = NULL;
         break;
    case funCallStmt:
      A = malloc_ast();
      A->t = T->next[0]->t;
      A->child[0] = malloc_ast();
      A->child[0]->t = T->next[1]->t;
      A->child[1] = malloc_ast();
      A->child[1]->t = T->next[3]->t;
      traverse_parsetree(T->next[3],TK_ID, handle_id,A->child[1]);

      A->child[2] = malloc_ast();
      A->child[2]->t = T->next[6]->t;
      traverse_parsetree(T->next[6],TK_ID, handle_id,A->child[2]);
      break;
    default:
#ifdef DEBUG
      printf("\n in case: handling %s", symbolToStr(symbol(T)));
      if(symbol(T) == arithmeticExpression)
        printf("\n boo\n");
#endif
      A =  malloc_ast();
      copyPT_to_AST(T,A);
      
      fillchild(A,T);
      if(A->child[0] == NULL && !isTerminal(symbol(A)))
        {
          free(A);
          A=NULL;
        }

      break;
    }
  

  return A;
}
