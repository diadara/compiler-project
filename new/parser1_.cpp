// Narayan Periwal 2010B4A7690P
// Sagar Uprety 2010B5A7533P
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include<iostream>
#include "parserDef.h"
FILE *op;
using namespace std;
//void createParseTable(grammar G, table T)
//parseTree  parseInputSourceCode(char *testcaseFile, table T)
//void printParseTree(parseTree  PT, char *outfile)
//void createAbstractSyntaxtree(parseTree T, abstractSyntaxTree A)
//void printAST(abstractSyntaxTree A, char *outFile, int *totalAllocatedMemory)
void intialize_ParseTable(void){
	int i=0,j=0;
	for(i=0;i<TotalNonTerminals;i++)
		for(j=0;j<TotalTerminals;j++)
			ParseTable[i][j]=-1;
}
struct Rule_RHS * createRNode(void){
	struct Rule_RHS *node=(struct Rule_RHS*)malloc(sizeof(struct Rule_RHS));
	node->Token_ID=-1;
	node->next=NULL;
	return node;
}
void hashfunction() {
	int i,j,len,hash=5381;
	for(i=0;i<TotalTerminals;i++){
		hash=5381;
		len=strlen(T[i]);
		for(j=0;j<len;j++)
			hash+=(hash*33+T[i][j])%1000;
		Thvalue[i]=hash%10000;
		//cout<<T[i]<<" "<<Thvalue[i]<<len<<endl;
	}

	for(i=0;i<TotalNonTerminals;i++){
		hash=5381;
		len=strlen(NT[i]);
		for(j=0;j<len;j++)
			hash+=(hash*33+NT[i][j])%1000;
		NThvalue[i]=hash%10000;
		//cout<<NT[i]<<" "<<NThvalue[i]<<len<<endl;
  	}
}

int stringToEnumlookup(char *str){
    //printf("%s\n",str);
	int len=strlen(str),i,hash=5381;
	//cout<<len<<endl;
	for(i=0;i<len;i++)
		hash+=(hash*33+str[i])%1000;
	hash%=10000;
	i=0;
	//cout<<hash<<endl;
		while(hash!=Thvalue[i] && i<TotalTerminals)
			i++;
        //cout<<"heyy"<<endl;
		if(hash!=Thvalue[i]){
		    i=0;
		   // cout<<"nonterminal"<<endl;
		while(hash!=NThvalue[i])
			i++;}
			//else
			//cout<<"terminal"<<endl;
		return i;
}
void populate_Grammar(FILE *fp){
	int ruleNumber=0,lookupvalue;
	char str[250]={'\0'};
	char c;
    int i,flag=0;;
	struct Rule_RHS *Tail;
    //printf("hello5\n");
	while(!feof(fp)){
		fscanf(fp,"%s",str);
		fprintf(op,"start %s\n",str);
		//printf("start %s\n ",str);
        lookupvalue=stringToEnumlookup(str);
        //printf("hello7\n");
		Grammar[ruleNumber].LHS_ID=lookupvalue;
		Grammar[ruleNumber].Node=createRNode();
		do{
		fscanf(fp,"%c",&c);
		}while(c==' ');
		i=0;
		while(c!='\n' && c!=EOF && c!=' ')
        {
            str[i++]=c;
            fscanf(fp,"%c",&c);
            //cout<<c<<" ";
        }
        str[i]='\0';
       // printf("%s\n",str);
		lookupvalue=stringToEnumlookup(str);
		Grammar[ruleNumber].Node->Token_ID=lookupvalue;
		//cout<<"lookup"<<endl;
        //cout<<lookupvalue<<endl;
		if((str[0]=='T'&&str[1]=='K'&&str[2]=='_'))
			Grammar[ruleNumber].RHSisTerminal=1;
		else
			Grammar[ruleNumber].RHSisTerminal=0;
		Tail=Grammar[ruleNumber].Node;
		flag=0;
		if(c=='\n')
		{   ruleNumber++;
		    fprintf(op,"%d\n",ruleNumber+1);
		    printf("%d\n",ruleNumber);
		    continue;
		}
		do{
		fscanf(fp,"%c",&c);
		}while(c==' ');
        while(c != '\n' && c != '*' && c!=EOF){
            // fscanf(fp," %s",str);
            i=0;
            while(c != ' ' && c != '*'&&c!='\n' && c!=EOF){
                str[i++]=c;
                fscanf(fp,"%c",&c);
            }
            str[i]='\0';
            Tail->next=createRNode();
            lookupvalue=stringToEnumlookup(str);
            if(c=='*') break;
            //printf("%s %d\n",str,lookupvalue);
            Tail->next->Token_ID=lookupvalue;
            Tail=Tail->next;
            while(c==' ')
                fscanf(fp,"%c",&c);
        }
        ruleNumber++;
        //cout<<ruleNumber<<endl;
        if(ruleNumber==120) break;
        fprintf(op,"%d\n",ruleNumber);


    }
    //printf("end of populate grammar\n");
}
void print_Grammar(void){
	int i=0;
	struct Rule_RHS * traverse=NULL;
	for(i=0;i<120;i++){
		traverse=Grammar[i].Node;
		printf("#%d# %d ==> ",i+1,Grammar[i].LHS_ID );
		while(traverse!=NULL){
			printf("%d ",traverse->Token_ID);
			traverse=traverse->next;
		}
		printf("\n");
	}
}
void fill_PT_forNT(int lhsNTnumber,int rhsNTnumber,int RuleNum ){
	int elements_in_Fset,elements_in_FLset,k=0,flag=0;
	while(First[rhsNTnumber][k]!=-1)
		k++;
	elements_in_Fset=k;
	k=0;
	while(Follow[lhsNTnumber][k]!=-1)
		k++;
	elements_in_FLset=k;
	k=0;
	while(k < elements_in_Fset){
		if(First[rhsNTnumber][k]==eps)
			{flag=1;printf("set for %d\n",lhsNTnumber);}
		k++;
    }
    switch(flag){
    	case 1:{ k=0;printf("in case 1 for id=%d\n",lhsNTnumber);
    		while(k < elements_in_FLset){
    			ParseTable[lhsNTnumber][Follow[lhsNTnumber][k]]=RuleNum;
    			k++;
    		}
    	}
    	case 0:{ k=0;
    		while(k < elements_in_Fset){
    			ParseTable[lhsNTnumber][First[rhsNTnumber][k]]=RuleNum;
    			k++;
    		}
    	}
    }
}

void createParseTable(){
	intialize_ParseTable();
	int ArrayNonTerminal[TotalNonTerminals];
	int i=0,j=0;
	int terminal=0;
	for(i=0;i<TotalNonTerminals;i++){
		j=0;
		ArrayNonTerminal[i]=i;
		while(j<TotalRules){
			if(Grammar[j].LHS_ID==ArrayNonTerminal[i]){
				if(Grammar[j].RHSisTerminal==1)
					ParseTable[i][Grammar[j].Node->Token_ID]=j;
				else
					fill_PT_forNT(i,Grammar[j].Node->Token_ID,j);
				}
			j++;
		}
	}
}
int main(){
    op=fopen("output.txt","w");
	FILE *fp=fopen("newGram.txt","r");
	FILE *fp1=fopen("parse.txt","w");
	hashfunction();
	char c;
	populate_Grammar(fp);
	//printf("hello_grammar is populated\n");
	print_Grammar();
	createParseTable();
		int i=0,j=0;
		for(j=0;j<TotalTerminals;j++)
			printf("%d ",j);
			printf("\n");

	printf("--------------------------------------------------------------------------------\n");
		 i=0,j=0;
	/*for(i=0;i<TotalNonTerminals;i++)
		{printf("#%d#\n",i);
			for(j=0;j<TotalTerminals;j++){
			printf("%d ",ParseTable[i][j]);
			fprintf(fp1,"%d ",ParseTable[i][j]);
			fprintf(fp1,"%d ",ParseTable[i][j]);}
			printf("\n");
			fprintf(fp1,"\n");
			printf("--------------------------------------------------------------------------------\n");
			fprintf(fp1,"--------------------------------------------------------------------------------\n");
		c=getchar();
		}*/
    fclose(fp);
    fclose(fp1);
    fclose(op);
	return 0;
}

