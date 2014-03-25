#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include"lexer.h"
#include"parser.h"
#include"parseTable.h"

extern bool any_error;

extern int T[][61];

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
    addNt(kn,"elseif",elseif);
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
    return S;
}

Stack pop(Stack S)
{
    struct stackNode* p;
    p=S.top;
    S.top=S.top->next;
    free(p);
    S.size--;
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
{
    int i;
    tokenp t;
    t=malloc(sizeof(tokenp));
    t->s=s;
    parseTree newnode;
    newnode = malloc(sizeof(struct parsetree));
    newnode->t=t;
    newnode->lineno=lineno;
    newnode->parent=NULL;
    newnode->pull=0;
    for(i=0;i<20;i++)
        newnode->next[i]=NULL;
    return newnode;
}




void printParseTree(parseTree  PT, FILE *outfile)
{
    int i;
    char empty[10], yes[20], no[20];
    strcpy(empty,"----");
    strcpy(yes, "yes");
    strcpy(no, "no");
    if(PT==NULL)
    {
        printf("Parse tree is invalid\n");
        return;
    }
    if(PT->next[0]==NULL)
        printf( "%-31s", PT->t->lexeme);
    else
        printf( "%-31s", empty);
    printf( "%-5d%-20s", PT->lineno, symbolToStr(PT->t->s));
    if(PT->t->s==TK_NUM || PT->t->s==TK_RNUM)
        printf( "%-21s", PT->t->lexeme);
    else
        printf( "%-21s", empty);
    if(PT->parent!=NULL)
        printf( "%-21s", symbolToStr(PT->parent->t->s));
    else
        printf( "%-21s", empty);
    if(PT->next[0]==NULL)
        printf( "%-5s", yes);
    else
        printf( "%-5s", no);
    if(!isTerminal(PT->t->s))
        printf( "%-21s\n", symbolToStr(PT->t->s));
    else
        printf( "%-21s\n", empty);
    for(i=0;i<20 && PT->next[i]!=NULL;i++)   printParseTree(PT->next[i],outfile);
}



parseTree parseInputSourceCode(int fp, keywordTable kt, grammar g[], bool*error)
{
    tokenp t;
    parseTree P;
    parseTree parent,child;
    int lineno=1 , i , k,q;
    Stack S;
    S.size=0;
    S.top=NULL;

    P=createParseNode(program,lineno);
    S=push(S,P);
    while(1)
    {
        t = getNextToken(fp, kt, error, &lineno);
        if(t==NULL || *error || t->s != TK_COMMENT)
        {
            if(*error)
            {
                if(t->s==TK_ERROR)
                {
                    printf("ERROR: Unknown pattern %s\n at line %d\n", t->lexeme, lineno);
                  
                }
                return NULL;
            }
            break;
        }
    }

    while(!(*error) && S.size && t )
    {
        if(isTerminal(S.top->tree->t->s))
        {
            if(t->s==S.top->tree->t->s)
            {
                S.top->tree->ruleno=-1;
                strcpy(S.top->tree->t->lexeme,t->lexeme);
                //free(t);
                S.top->tree->lineno=lineno;
                S=pop(S);
                while(1)
                {
                    t = getNextToken(fp, kt, error, &lineno);
                    if(t==NULL || *error==1 || t->s != TK_COMMENT)
                    {
                        if(*error)
                        {
                            if(t->s==TK_ERROR)
                                printf("ERROR: Unknown pattern %s at line %d\n", t->lexeme, lineno);
                           
                            return NULL;
                        }
                        break;
                    }
                   
                }
            }
            else if(S.top->tree->t->s==TK_EPS)
            {
                S.top->tree->ruleno=-1;
                S=pop(S);
            }
            else
            {
                *error=1;
                if(*error)
                {
                    printf("ERROR: The token %s for lexeme %s does not match at line %d. ",symbolToStr(t->s), t->lexeme, lineno);
                    
                }
                //free(t);
                break;
            }
        }
        else
        {
            i=T[S.top->tree->t->s-program][t->s];
            if(i==-1)
            {
                *error=1;
                if(*error)
                {
                    printf("ERROR: The token %s for lexeme %s does not match at line %d.is ",symbolToStr(t->s), t->lexeme, lineno);
          
                }
                break;
            }
            parent=S.top->tree;
            parent->ruleno=i;
            S=pop(S);
            for(k=g[i].listno -1 ;k>=0;k--)
            {
                child=createParseNode(g[i].list[k],lineno);
                child->parent = parent;
                S=push(S,child);
                parent->next[k]=child;
            }
        }
    }

    if(!t && *error)
    {
        if(t->s==TK_ERROR)
            printf("ERROR: Unknown pattern %sat line %d\n", t->lexeme, lineno);
        return NULL;
    }
    else if(t && !S.size)
      printf("ERROR: %d: Program did not end prperly. It expected to end near %s\n",lineno,symbolToStr(t->s));
    return P;
}
