// Narayan Periwal 2010B4A7690P
// Sagar Uprety 2010B5A7533P
#ifndef PARSERDEF
#define PARSERDEF
#define TotalTerminals 62
#define TotalNonTerminals 61
#define TotalRules 120
enum Terminals{
            TK_ASSIGNOP,TK_COMMENT,TK_ID,TK_NUM,TK_RNUM,TK_CHR,TK_STRING,TK_MAPINSERT,TK_MAPREMOVE,TK_ASSIGN,
            TK_VAR,TK_MAIN,TK_ENDMAIN,TK_INT,TK_REAL,TK_IF,TK_ENDIF,TK_GLOBAL,TK_INPUT,TK_OUTPUT,TK_WHILE,TK_ENDWHILE,
            TK_CHAR,TK_FUNCTION,TK_ENDFUNCTION,TK_ELSEIF,TK_ELSE,TK_RECORD,TK_ENDRECORD,TK_ARRAY,TK_MAP,TK_GET,
            TK_PUT,TK_PUTS,TK_RETURN,TK_BREAK,TK_CALL,TK_SQL,TK_SQR,TK_SEM,TK_COMMA,TK_DOT,TK_OP,TK_CL,TK_DQT,
            TK_SQT,TK_PLUS,TK_MINUS,TK_MUL,TK_DIV,TK_MOD,TK_AND,TK_OR,TK_NOT,TK_LT,TK_LE,TK_EQ,TK_GT,TK_GE,TK_NE,eps,$
}Term;//62
enum NonTerminals{
        program,typeDefinition_s,typeDefinition,fieldDefinition_s,fieldDefinition,moreField_ID,moreFields,
        primitiveDatatype,globalStatements,globalDeclare,globalAssign,var,otherFunctions,function,
        input_par,output_par,parameter_list,dataType,constructedDatatype,remaining_list,mainFunction,
        stmt_s,declaration_s,all_declaration,declaration,array_declaration,map_declaration,moreMapID,
        more_array_IDs,more_IDs,otherStmts,stmt,assignmentStmt,SingleOrRecOrArrayId,Other_Id,
        arithmeticExpression,more_variables,Operator,funCallStmt,idList,more_ids,iterativeStmt,
        conditionalStmt,elseif,Elseifs,Elseif,Else,ioStmt,allVar,Other_Var,numorid,booleanExpression,
        bExp,Op,variable,Other_Variable,logicalOp,relationalOp,mapStmt,mapAdd,mapDelete
}NonTerm;//61
static int First[][110]={
{TK_RECORD, TK_GLOBAL, TK_FUNCTION, TK_MAIN,-1},{TK_RECORD,eps,-1},{TK_RECORD,-1},
{TK_VAR,-1},{TK_VAR,-1},{TK_COMMA, eps,-1},{TK_VAR, eps,-1},{TK_INT, TK_REAL, TK_CHAR,-1},
{TK_GLOBAL, eps,-1},{TK_GLOBAL,-1},{TK_ASSIGN, eps,-1},{TK_NUM, TK_RNUM, TK_SQT,-1},
{TK_FUNCTION, eps,-1},{TK_FUNCTION,-1},{TK_INPUT,-1},{TK_OUTPUT,-1},{TK_VAR, eps,-1},
{TK_INT, TK_REAL, TK_CHAR,TK_RECORD,-1},{TK_RECORD,-1},{TK_COMMA, eps,-1},{TK_MAIN,-1},
{TK_VAR, TK_ARRAY, TK_MAP, TK_ASSIGN, TK_WHILE, TK_IF,-1},
{TK_GET, TK_PUT, TK_PUTS, TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, eps,-1},
{TK_VAR, TK_ARRAY, TK_MAP, eps,-1},{TK_VAR, TK_ARRAY, TK_MAP,-1},{TK_VAR,-1},{TK_ARRAY,-1},
{TK_MAP,-1},{TK_COMMA, eps,-1},{TK_COMMA, eps,-1},{TK_COMMA, eps,-1},
{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, eps,-1},
{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS ,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE,-1},
{TK_ASSIGN,-1},{TK_ID,-1},{TK_DOT, TK_SQL, eps,-1},{TK_OP, TK_ID, TK_NUM, TK_RNUM, TK_SQT, eps,-1},
{TK_OP, TK_ID, TK_NUM, TK_RNUM, TK_SQT, TK_PLUS, TK_MUL, TK_MINUS, TK_DIV, TK_MOD, eps,-1},
{TK_PLUS, TK_MUL, TK_MINUS, TK_DIV, TK_MOD,-1},{TK_CALL,-1},{TK_ID, eps,-1},{TK_COMMA, eps,-1},
{TK_WHILE,-1},{TK_IF,-1},{TK_ELSEIF, TK_ELSE, eps,-1},{TK_ELSEIF, eps,-1},{TK_ELSEIF,-1},{TK_ELSE, eps,-1},
{TK_GET, TK_PUT, TK_PUTS,-1},{TK_ID,-1},{TK_DOT, TK_SQL, eps,-1},{TK_NUM, TK_ID,-1},
{TK_OP, TK_NOT, TK_ID, TK_NUM, TK_RNUM, TK_SQT,-1},{TK_CL, TK_AND, TK_OR, TK_LT, TK_LE, TK_EQ, TK_GT,TK_GE, TK_NE ,-1},
{TK_AND, TK_OR, TK_LT, TK_LE, TK_EQ, TK_GT, TK_GE,  TK_NE,-1},{TK_ID, TK_NUM, TK_RNUM, TK_SQT,-1},{TK_SQL, TK_DOT, eps,-1},
{TK_AND, TK_OR,-1},{TK_LT, TK_LE, TK_EQ, TK_GT, TK_GE, TK_NE,-1},
{TK_MAPINSERT, TK_MAPREMOVE,-1},{TK_MAPINSERT,-1},{TK_MAPREMOVE,-1}
};
static int Follow[][140]={
	{$,-1},{TK_GLOBAL, TK_FUNCTION, TK_MAIN,-1},{TK_RECORD, TK_GLOBAL, TK_FUNCTION, TK_MAIN,-1},{TK_ENDRECORD,-1},{TK_VAR, TK_ENDRECORD,-1},{TK_SEM,-1},{TK_ENDRECORD,-1},{TK_ID,-1},{TK_FUNCTION, TK_MAIN,-1},{TK_ASSIGN, TK_FUNCTION, TK_MAIN,-1},{TK_FUNCTION, TK_MAIN,-1},{TK_SEM,-1},{TK_MAIN,-1},{TK_MAIN, TK_FUNCTION,-1},{TK_OUTPUT,-1},{TK_VAR, TK_ARRAY, TK_MAP, TK_ASSIGN, TK_WHILE,TK_IF, TK_GET, TK_PUT, TK_PUTS, TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDFUNCTION ,-1},{TK_SQR,-1},{TK_ID,-1},{TK_ID,-1},{TK_SQR,-1},{$,-1},{TK_ENDMAIN, TK_ENDFUNCTION,-1},{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION ,-1},{TK_VAR, TK_ARRAY, TK_MAP, TK_ASSIGN, TK_WHILE,TK_IF, TK_GET, TK_PUT, TK_PUTS, TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION,-1},{TK_VAR, TK_ARRAY, TK_MAP, TK_ASSIGN, TK_WHILE,TK_IF, TK_GET, TK_PUT, TK_PUTS, TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION,-1},{TK_VAR, TK_ARRAY, TK_MAP, TK_ASSIGN, TK_WHILE,TK_IF,
 TK_GET, TK_PUT, TK_PUTS, TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION,-1},{TK_VAR, TK_ARRAY, TK_MAP, TK_ASSIGN, TK_WHILE,TK_IF, TK_GET, TK_PUT, TK_PUTS, TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION,-1},{TK_SEM,-1},{TK_SEM,-1},{TK_SEM,-1},{TK_ENDMAIN, TK_ENDFUNCTION, TK_ENDWHILE,TK_ELSEIF, TK_ELSE, TK_ENDIF,-1},{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION, TK_ENDWHILE, TK_ELSEIF, TK_ELSE, TK_ENDIF,-1},{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION, TK_ENDWHILE, TK_ELSEIF, TK_ELSE, TK_ENDIF,-1},{TK_ASSIGNOP,-1},{TK_ASSIGNOP,-1},{TK_SEM, TK_CL,-1},{TK_SEM, TK_CL,-1},{TK_OP, TK_ID, TK_NUM, TK_RNUM, TK_SQT, TK_SEM, TK_CL,-1},{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION, TK_ENDWHILE, TK_ELSEIF, TK_ELSE, TK_ENDIF,-1},{TK_SQR, TK_SEM,-1},{TK_SQR, TK_SEM,-1},{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION, TK_ENDWHILE, TK_ELSEIF, TK_ELSE, TK_ENDIF,-1},{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION, TK_ENDWHILE, TK_ELSEIF, TK_ELSE, TK_ENDIF,-1},{TK_ENDIF,-1},{TK_ELSE, TK_ENDIF,-1},{TK_ELSEIF, TK_ELSE, TK_ENDIF,-1},{TK_ENDIF,-1},{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION, TK_ENDWHILE, TK_ELSEIF, TK_ELSE, TK_ENDIF,-1},{TK_SEM,-1},{TK_SEM,-1},{TK_SQR,-1},{TK_CL, TK_AND, TK_OR, TK_LT, TK_LE, TK_EQ, TK_GT,TK_GE, TK_NE, TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS, TK_CALL, TK_MAPINSERT, TK_MAPREMOVE,-1},{TK_CL, TK_AND, TK_OR, TK_LT, TK_LE, TK_EQ, TK_GT,TK_GE, TK_NE, TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS, TK_CALL, TK_MAPINSERT, TK_MAPREMOVE,-1},{TK_OP, TK_NOT, TK_ID, TK_NUM, TK_RNUM, TK_SQT,-1},{TK_CL, TK_AND, TK_OR, TK_LT, TK_LE, TK_EQ, TK_GT,TK_GE,
TK_NE, TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS, TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_SEM, TK_PLUS, TK_MUL, TK_MINUS, TK_DIV, TK_MOD, TK_ID, TK_NUM, TK_RNUM, TK_SQT, TK_OP,-1},{TK_CL, TK_AND, TK_OR, TK_LT, TK_LE, TK_EQ, TK_GT,TK_GE, TK_NE, TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS, TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_SEM, TK_PLUS, TK_MUL, TK_MINUS, TK_DIV, TK_MOD, TK_ID, TK_NUM, TK_RNUM, TK_SQT, TK_OP,-1},{TK_OP, TK_NOT, TK_ID, TK_NUM, TK_RNUM, TK_SQT,-1},{TK_OP, TK_NOT, TK_ID, TK_NUM, TK_RNUM, TK_SQT,-1},{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION, TK_ENDWHILE, TK_ELSEIF, TK_ELSE, TK_ENDIF,-1},{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION, TK_ENDWHILE, TK_ELSEIF, TK_ELSE, TK_ENDIF,-1},{TK_ASSIGN, TK_WHILE, TK_IF, TK_GET, TK_PUT, TK_PUTS,TK_CALL, TK_MAPINSERT, TK_MAPREMOVE, TK_ENDMAIN, TK_ENDFUNCTION, TK_ENDWHILE, TK_ELSEIF, TK_ELSE,
TK_ENDIF,-1}
};

char T[][25]={"TK_ASSIGNOP","TK_COMMENT","TK_ID","TK_NUM","TK_RNUM","TK_CHR","TK_STRING",
            "TK_MAPINSERT","TK_MAPREMOVE","TK_ASSIGN","TK_VAR","TK_MAIN","TK_ENDMAIN",
            "TK_INT","TK_REAL","TK_IF","TK_ENDIF","TK_GLOBAL","TK_INPUT","TK_OUTPUT","TK_WHILE",
            "TK_ENDWHILE","TK_CHAR","TK_FUNCTION","TK_ENDFUNCTION","TK_ELSEIF","TK_ELSE",
            "TK_RECORD","TK_ENDRECORD","TK_ARRAY","TK_MAP","TK_GET","TK_PUT","TK_PUTS",
            "TK_RETURN","TK_BREAK","TK_CALL","TK_SQL","TK_SQR","TK_SEM","TK_COMMA",
            "TK_DOT","TK_OP","TK_CL","TK_DQT","TK_SQT","TK_PLUS","TK_MINUS","TK_MUL","TK_DIV",
            "TK_MOD","TK_AND","TK_OR","TK_NOT","TK_LT","TK_LE","TK_EQ","TK_GT","TK_GE","TK_NE","TK_EPS","TK_DOLLAR"};
char NT[][30]={"program","typeDefinition_s","typeDefinition","fieldDefinition_s","fieldDefinition","moreField_ID",
                "moreFields","primitiveDatatype","globalStatements","globalDeclare","globalAssign","var",
                "otherFunctions","function","input_par","output_par","parameter_list","dataType",
                "constructedDatatype","remaining_list","mainFunction","stmt_s","declaration_s",
                "all_declaration","declaration","array_declaration","map_declaration","moreMapID",
                "more_array_IDs","more_IDs","otherStmts","stmt","assignmentStmt","SingleOrRecOrArrayId",
                "Other_Id","arithmeticExpression","more_variables","Operator","funCallStmt","idList","more_ids",
                "iterativeStmt","conditionalStmt","Elseandelseif","Elseifs","Elseif","Else","ioStmt","allVar","Other_Var",
                "numorid","booleanExpression","bExp","Op","variable","Other_Variable",
                "logicalOp","relationalOp","mapStmt","mapAdd","mapDelete"};
static int ParseTable[TotalNonTerminals][TotalTerminals];
static int Thvalue[TotalTerminals],NThvalue[TotalNonTerminals];

struct Rule_RHS{
	int Token_ID;
	struct Rule_RHS *next;
};


struct Rule {
	struct Rule_RHS *Node;
	int RHSisTerminal;   //LHSisTerminal=1 if the first element is a terminal of the
	int LHS_ID;			//expanded rule  else it is 0.
};

struct Rule Grammar[TotalRules+1];
#endif
