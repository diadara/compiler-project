
parseTree createAbstractSyntaxTree2(parseTree T)
{
  parseTree temp, A = NULL;
#define symbol(T) (T->t->s)
#define nextsymbol(T,j)  (T->next[j]->t->s)
  
  if(isTerminal(symbol(T)))
    {
      if(symbol(T) == TK_EPS || symbol(T) == TK_OP || symbol(T) == TK_CL || symbol(T) == TK_ASSIGNOP ||
         symbol(T) == TK_SEM || symbol(T) == TK_SQR || symbol(T) == TK_SQL || symbol(T) == TK_COMMA || 
         symbol(T) == TK_CALL || symbol(T) == TK_ENDMAIN || symbol(T) == TK_ENDIF || symbol(T) == TK_ENDWHILE ||
         symbol(T) == TK_ENDRECORD || symbol(T) == TK_ENDFUNCTION || symbol(T) == TK_ASSIGN ||
         symbol(T) == TK_GLOBAL)
        return NULL;
      else
        {
          A = createParseNode(T->t->s,T->lineno);
          A->parent=T->parent;
          copyTree(A,T);
          return A;
        }
      
    }
  
  int n = countChild(T);
  if(n==1)
    {
      return createAbstractSyntaxTree(T->next[0]);
    }

  switch(symbol(T))
    {
    case Operator:
      

    }
  
  
  int j = 0, k = 0;
  A = createParseNode(T->t->s,T->lineno);
  A->parent=T->parent;
  while(T->next[j]!=NULL)
    {
      temp = createAbstractSyntaxTree(T->next[j]);
      if(temp != NULL)
        {
          A->next[k] = temp;
          temp->parent = A;
          k++;
        }
      j++;
    }

  

  return A;
}
