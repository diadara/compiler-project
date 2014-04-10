#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include"lexer.h"
#include"parser.h"
#include"parseTable.h"

extern bool any_error;


symbol toSym(char *a, keywordTable nt)//return Symbol for given string
{
    int hval,hashkey=300;
    hval=hash(a,hashkey);
    symbol s;
    while(1)
    {
        if(nt[hval].present==FALSE)
        {
            s=TK_ERROR;
#ifdef DEBUG
            printf("\nunknown: %s", a);
#endif
            return s;
        }
        else if(!strcmp(a,nt[hval].keyword))
        {
            s=nt[hval].s;
            return s;
        }
        hval++;
        hval=hval%hashkey;
    }
}

void addNt(keywordTable nt, char *keyword, symbol s)//recursively called to add keyword to keywordTable
{
    int hval,hashkey=300;
    hval=hash(keyword,hashkey);
    while(nt[hval].present==TRUE)
        hval=(++hval)%hashkey;
    strcpy(nt[hval].keyword, keyword);
    nt[hval].present=TRUE;
    nt[hval].s=s;
}

keywordTable  createNtTable()
{
  int n = 300;// almost twice as number of keywords
  keywordTable kn = malloc(n * sizeof *kn);
  int i;
  for(i=0;i<n;i++)
    (kn+i)->present = FALSE;

    addNt(kn,"program",program);
    addNt(kn,"TK_ASSIGNOP",TK_ASSIGNOP);
    addNt(kn,"TK_COMMENT",TK_COMMENT);
    addNt(kn,"TK_ID",TK_ID);
    addNt(kn,"TK_NUM",TK_NUM);
    addNt(kn,"TK_RNUM",TK_RNUM);
    addNt(kn,"TK_CHR",TK_CHR);
    addNt(kn,"TK_STRING",TK_STRING);
    addNt(kn,"TK_MAPINSERT",TK_MAPINSERT);
    addNt(kn,"TK_MAPREMOVE",TK_MAPREMOVE);
    addNt(kn,"TK_ASSIGN",TK_ASSIGN);
    addNt(kn,"TK_VAR",TK_VAR);
    addNt(kn,"TK_MAIN",TK_MAIN);
    addNt(kn,"TK_ENDMAIN",TK_ENDMAIN);
    addNt(kn,"TK_INT",TK_INT);
    addNt(kn,"TK_REAL",TK_REAL);
    addNt(kn,"TK_IF",TK_IF);
    addNt(kn,"TK_ENDIF",TK_ENDIF);
    addNt(kn,"TK_GLOBAL",TK_GLOBAL);
    addNt(kn,"TK_INPUT",TK_INPUT);
    addNt(kn,"TK_OUTPUT",TK_OUTPUT);
    addNt(kn,"TK_WHILE",TK_WHILE);
    addNt(kn,"TK_ENDWHILE",TK_ENDWHILE);
    addNt(kn,"TK_CHAR",TK_CHAR);
    addNt(kn,"TK_FUNCTION",TK_FUNCTION);
    addNt(kn,"TK_ENDFUNCTION",TK_ENDFUNCTION);
    addNt(kn,"TK_ELSEIF",TK_ELSEIF);
    addNt(kn,"TK_ELSE",TK_ELSE);
    addNt(kn,"TK_RECORD",TK_RECORD);
    addNt(kn,"TK_ENDRECORD",TK_ENDRECORD);
    addNt(kn,"TK_ARRAY",TK_ARRAY);
    addNt(kn,"TK_MAP",TK_MAP);
    addNt(kn,"TK_GET",TK_GET);
    addNt(kn,"TK_PUT",TK_PUT);
    addNt(kn,"TK_PUTS",TK_PUTS);
    addNt(kn,"TK_RETURN",TK_RETURN);
    addNt(kn,"TK_BREAK",TK_BREAK);
    addNt(kn,"TK_CALL",TK_CALL);
    addNt(kn,"TK_SQL",TK_SQL);
    addNt(kn,"TK_SQR",TK_SQR);
    addNt(kn,"TK_SEM",TK_SEM);
    addNt(kn,"TK_COMMA",TK_COMMA);
    addNt(kn,"TK_DOT",TK_DOT);
    addNt(kn,"TK_OP",TK_OP);
    addNt(kn,"TK_CL",TK_CL);
    addNt(kn,"TK_DQT",TK_DQT);
    addNt(kn,"TK_SQT",TK_SQT);
    addNt(kn,"TK_PLUS",TK_PLUS);
    addNt(kn,"TK_MINUS",TK_MINUS);
    addNt(kn,"TK_MUL",TK_MUL);
    addNt(kn,"TK_DIV",TK_DIV);
    addNt(kn,"TK_MOD",TK_MOD);
    addNt(kn,"TK_AND",TK_AND);
    addNt(kn,"TK_OR",TK_OR);
    addNt(kn,"TK_NOT",TK_NOT);
    addNt(kn,"TK_LT",TK_LT);
    addNt(kn,"TK_LE",TK_LE);
    addNt(kn,"TK_EQ",TK_EQ);
    addNt(kn,"TK_GT",TK_GT);
    addNt(kn,"TK_GE",TK_GE);
    addNt(kn,"TK_NE",TK_NE);
    addNt(kn,"TK_ERROR",TK_ERROR);
    addNt(kn,"TK_EPS",TK_EPS);
    addNt(kn,"$",$);
    addNt(kn,"program",program);
    addNt(kn,"typeDefinition_s",typeDefinition_s);
    addNt(kn,"typeDefinition",typeDefinition);
    addNt(kn,"fieldDefinition_s",fieldDefinition_s);
    addNt(kn,"fieldDefinition",fieldDefinition);
    addNt(kn,"moreField_ID",moreField_ID);
    addNt(kn,"moreFields",moreFields);
    addNt(kn,"primitiveDatatype",primitiveDatatype);
    addNt(kn,"globalStatements",globalStatements);
    addNt(kn,"globalDeclare",globalDeclare);
    addNt(kn,"globalAssign",globalAssign);
    addNt(kn,"var",var);
    addNt(kn,"otherFunctions",otherFunctions);
    addNt(kn,"function",function);
    addNt(kn,"input_par",input_par);
    addNt(kn,"output_par",output_par);
    addNt(kn,"parameter_list",parameter_list);
    addNt(kn,"dataType",dataType);
    addNt(kn,"constructedDatatype",constructedDatatype);
    addNt(kn,"remaining_list",remaining_list);
    addNt(kn,"mainFunction",mainFunction);
    addNt(kn,"stmt_s",stmt_s);
    addNt(kn,"declaration_s",declaration_s);
    addNt(kn,"all_declaration",all_declaration);
    addNt(kn,"declaration",declaration);
    addNt(kn,"array_declaration",array_declaration);
    addNt(kn,"map_declaration",map_declaration);
    addNt(kn,"moreMapID",moreMapID);
    addNt(kn,"more_array_IDs",more_array_IDs);
    addNt(kn,"more_IDs",more_IDs);
    addNt(kn,"otherStmts",otherStmts);
    addNt(kn,"stmt",stmt);
    addNt(kn,"assignmentStmt",assignmentStmt);
    addNt(kn,"SingleOrRecOrArrayId",SingleOrRecOrArrayId);
    addNt(kn,"Other_Id",Other_Id);
    addNt(kn,"arithmeticExpression",arithmeticExpression);
    addNt(kn,"more_variables",more_variables);
    addNt(kn,"Operator",Operator);
    addNt(kn,"funCallStmt",funCallStmt);
    addNt(kn,"idList",idList);
    addNt(kn,"more_ids",more_ids);
    addNt(kn,"IterativeStmt",IterativeStmt);
    addNt(kn,"conditionalStmt",conditionalStmt);
    addNt(kn,"Elseandelseif",Elseandelseif);
    addNt(kn,"Elseifs",Elseifs);
    addNt(kn,"Elseif",Elseif);
    addNt(kn,"Else",Else);
    addNt(kn,"ioStmt",ioStmt);
    addNt(kn,"allVar",allVar);
    addNt(kn,"Other_Var",Other_Var);
    addNt(kn,"numorid",numorid);
    addNt(kn,"booleanExpression",booleanExpression);
    addNt(kn,"bExp",bExp);
    addNt(kn,"Op",Op);
    addNt(kn,"variable",variable);
    addNt(kn,"Other_Variable",Other_Variable);
    addNt(kn,"logicalOp",logicalOp);
    addNt(kn,"relationalOp",relationalOp);
    addNt(kn,"mapStmt",mapStmt);
    addNt(kn,"mapAdd",mapAdd);
    addNt(kn,"mapDelete",mapDelete);
    return kn;
}

int createGrammar(FILE * fp,grammar G[], keywordTable nt)//load grammar from text file
{
    char a[40];
    int k = 0;
    int ruleNumber = 0;
    int listno = 0;
    while(1)
    {
        fscanf(fp,"%s",a);
        if(feof(fp))break;
        if(k==0)
        {
            G[ruleNumber].ruleNumber = ruleNumber;
            G[ruleNumber].nt = toSym(a,nt);
            k++;
            listno = 0;
        }
        else if(k==1)
        {
            if(strcmp(a,".")==0)
            {
                k=0;
                G[ruleNumber].listno = listno;
                ruleNumber++;
                continue;
            }
            G[ruleNumber].list[listno++] = toSym(a,nt);
        }
    }
    return ruleNumber;
}





/* Sets */


/* Parse Table */



bool isTerminal(symbol s)//returns true if given symbol is terminal
{
    if((int)(s-program)<0) return 1;
    return 0;
}



/* Parsing */


Stack push(Stack S,parseTree tree)
{
  if(S.top==NULL)
        S.top=createStackNode(tree);
    else{
        struct stackNode* newnode=createStackNode(tree);
        newnode->next=S.top;
        S.top=newnode;
    }
    S.size++;

#ifdef DEBUG
  printf("\n pushing %s to stack (%d)", symbolToStr(tree->t->s), S.size);
#endif

    return S;
}

Stack pop(Stack S)
{

#ifdef DEBUG
  printf("\n poping  %s from stack", symbolToStr(S.top->tree->t->s));
#endif

  struct stackNode* p;
    p=S.top;
    S.top=S.top->next;
    free(p);
    S.size--;
    printf("(%d)", S.size);
    return S;
}

struct stackNode* createStackNode(parseTree tree)
{
    struct stackNode* newnode;
    newnode=(struct stackNode*)malloc(sizeof(struct stackNode));
    newnode->tree=tree;
    newnode->next=NULL;
    return newnode;
}


parseTree createParseNode(symbol s,int lineno)
{ static int k;
    int i;
    tokenp t;
    t=malloc(sizeof *t);
    t->s=s;
    parseTree newnode;
    newnode = malloc(sizeof *newnode);
    newnode->t=t;
    newnode->lineno=lineno;
    newnode->parent=NULL;
    newnode->nochild = 0;
    newnode->id = k++;
    for(i=0;i<20;i++)
        newnode->next[i]=NULL;
    return newnode;
    
}


void printRule(grammar G[], int ruleno)
{
  if(ruleno < 0) {
  printf("\n invalid rule \n");
  return;

  }
  printf("\n rule no:%d %s -> ",ruleno, symbolToStr(G[ruleno].nt));
  int i = G[ruleno].listno;
  while(i--)
    {
      printf(" %s ",symbolToStr(G[ruleno].list[i]));
    }

  printf("\n");
  
}


void printParseTree_helper(parseTree PT, FILE * of)
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
      
    for(i=0;i<20 && PT->next[i]!=NULL;i++)
      fprintf(of, "%s%d%s%s%d\n",parent, PT->id, join,symbolToStr(PT->next[i]->t->s), PT->next[i]->id);
    for(i=0;i<20 && PT->next[i]!=NULL;i++) printParseTree_helper(PT->next[i],of);


    
  }

void printParseTree(parseTree  PT, FILE *of)
{

      fprintf(of, "graph G { \n");
      printParseTree_helper(PT, of);     
      fprintf(of, "\n}\n");
}


parseTree parseInputSourceCode(int fp, keywordTable kt, grammar g[], bool*error)
{
  ParseTable PT = getParseTable();
  
#ifdef DEBUG
  printf("\n started parsing pushing program to stack: error %d", *error);
#endif
    tokenp t;
    parseTree P;
    parseTree parent,child;
    int lineno=1 , i , k;
    Stack S;
    S.size=0;
    S.top=NULL;
    P=createParseNode(program,lineno);
    S=push(S,P);

    t = getNextToken(fp, kt, error, &lineno);
#ifdef DEBUG
    printf("\n got %s , error %d , size %d", symbolToStr(t->s), *error, S.size);
#endif

    
    while(*error==FALSE && t!=NULL && S.size!=0){
      if(isTerminal(S.top->tree->t->s))
        {
          if(t->s==S.top->tree->t->s)
            {
              S.top->tree->ruleno=-1;
              if(t->s==TK_ID || t->s==TK_NUM)
                strcpy(S.top->tree->t->lexeme,t->lexeme);
            free(t);
            S.top->tree->lineno=lineno;          
            S=pop(S);
            t = getNextToken(fp, kt, error, &lineno);
#ifdef DEBUG
 if(t)
   printf("\n got %s , error %d , size %d", symbolToStr(t->s), *error, S.size);
#endif

            }
        else if(S.top->tree->t->s==TK_EPS){
            S.top->tree->ruleno=-1;
            S=pop(S);
        }
        else{
            *error=1;
            printf("\n %d: %s expected near %s.\n",lineno,symbolToStr(S.top->tree->t->s),symbolToStr(t->s));
            free(t);
            break;
        }
    }
      else{
#ifdef DEBUG
        //    printf("\n going to check %d %d %s %s", (S.top->tree-t->s - program), t->s, symbolToStr(S.top->tree-t->s),symbolToStr(t->s));
#endif
        i=PT.T[S.top->tree->t->s-program][t->s]; // might segfault
        if(i==-1){
            *error=1;
            printf("\n %d: Unxpected symbol  %s.",lineno,symbolToStr(t->s));
            break;
        }
#ifdef DEBUG
        printRule(g,i);
#endif
        parent=S.top->tree;
        parent->ruleno=i;        
        S=pop(S);
        parent->nochild = g[i].listno;
        for(k=g[i].listno -1 ;k>=0;k--) {
          child=createParseNode(g[i].list[k],lineno);
            child->parent = parent;            
            S=push(S,child);
            parent->next[k]=child;//need to preserve order
        }

      }   
    }
    
if(t==NULL && *error==1)
    printf("\n %d: Unknown/invalid token.\n",lineno); 
else if(t!=NULL && S.size==0)
    printf("\n %d: Program expected to end near %s",lineno,symbolToStr(t->s));
return P;

}


void copyTree(parseTree A , parseTree B)
{
    int i=0;
    A->t->s = B->t->s;
    A->lineno = B->lineno;
    if(isTerminal(B->t->s))
    {
        strcpy(A->t->lexeme,B->t->lexeme);
    }
    while(B->next[i]!=NULL)
    {
        A->next[i] = B->next[i];
        i++;
    }
    A->next[i] = NULL;
}

parseTree createAbstractSyntaxTree(parseTree T)
{
    int n = 0;
    parseTree A = NULL;
    while(T->next[n] != NULL)
        n++;
    if(n==1)
    {
        return createAbstractSyntaxTree(T->next[0]);
    }
    else if(n==0)
    {

#define symbol(T) (T->t->s)
      if(symbol(T) == TK_EPS || symbol(T) == TK_OP || symbol(T) == TK_CL || symbol(T) == TK_ASSIGNOP ||
         symbol(T) == TK_SEM || symbol(T) == TK_SQR || symbol(T) == TK_SQL || symbol(T) == TK_COMMA || 
         symbol(T)==TK_CALL || symbol(T) == TK_ENDMAIN || symbol(T) == TK_ENDIF || symbol(T) == TK_ENDWHILE
         || symbol(T) == TK_ENDRECORD || symbol(T) == TK_ENDFUNCTION)
            return NULL;
        if(isTerminal(T->t->s))
        {
            A = createParseNode(T->t->s,T->lineno);
            A->parent=T->parent;
            copyTree(A,T);
        }
        return A;
    }
    else
    {
        int j=0,k=0;
        A = createParseNode(T->t->s,T->lineno);
        A->parent=T->parent;
        parseTree temp;
        while(T->next[j]!=NULL)
        {
#define nextsymbol(T,j)  (T->next[j]->t->s)
          if(nextsymbol(T,j) == TK_EPS || nextsymbol(T,j) == TK_OP || nextsymbol(T,j) == TK_CL || nextsymbol(T,j) == TK_ASSIGNOP ||
             nextsymbol(T,j) == TK_SEM || nextsymbol(T,j) == TK_SQR || nextsymbol(T,j) == TK_SQL || nextsymbol(T,j) == TK_COMMA || 
             nextsymbol(T,j)==TK_CALL || nextsymbol(T,j) == TK_ENDMAIN || nextsymbol(T,j) == TK_ENDIF || nextsymbol(T,j) == TK_ENDWHILE
             || nextsymbol(T,j) == TK_ENDRECORD || nextsymbol(T,j) == TK_ENDFUNCTION)
            {
                j++;
                continue;
            }
            temp = createAbstractSyntaxTree(T->next[j]);
            if(temp != NULL)
            {
                A->next[k] = temp;
                temp->parent = A;
                k++;
            }
            j++;
        }
        j = 0;
        int m = 0, f=0;
        while(A->next[j] != NULL)
        {
          if((nextsymbol(A,j) == TK_PLUS || nextsymbol(A,j)==TK_MINUS || nextsymbol(A,j) == TK_MUL || nextsymbol(A,j)==TK_DIV || 
              nextsymbol(A,j)==TK_LE || nextsymbol(A,j)==TK_LT || nextsymbol(A,j)==TK_GT || nextsymbol(A,j)==TK_GE || 
              nextsymbol(A,j)==TK_NE || nextsymbol(A,j)==TK_EQ || nextsymbol(A,j)==TK_AND || nextsymbol(A,j)==TK_OR) && (!A->next[j]->pull))
            {
                f = 1;
                m = j;
            }
            j++;
        }
        if(j==1)
        {
            if(!isTerminal(A->t->s))
            {
                copyTree(A,A->next[0]); 
            }
        }
        else if(j==0)
        {
            free(A);
            return NULL;
            
        }
        else if(f)
        {
            A->t->s = A->next[m]->t->s;
            A->lineno = A->next[m]->lineno;
            if(isTerminal(A->next[m]->t->s))
            {
                strcpy(A->t->lexeme,A->next[m]->t->lexeme);
            }
            A->pull = 1;
            m++;
            while(A->next[m] != NULL)
            {
                A->next[m-1] = A->next[m];
                m++;
            }
            A->next[m-1] = NULL;
        }
        return A;
    }
}

