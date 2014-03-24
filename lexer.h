#ifndef _LEXER
#define _LEXER

typedef enum 
  {
    TK_ASSIGNOP,
    TK_FIELDID,   
    TK_ID,        
    TK_NUM,       
    TK_RNUM,      
    TK_STRING,    
    TK_FUNID,     
    TK_RECORDID,  
    TK_ARRAYID,   
    TK_MAPID,     
    TK_MAPFIELD,  
    TK_MAPINSERT, 
    TK_MAPREMOVE, 
    TK_ASSIGN,    
    TK_VAR,       
    TK_MAIN,      
    TK_ENDMAIN,   
    TK_INT,       
    TK_REAL,      
    TK_IF,        
    TK_ENDIF,     
    TK_GLOBAL,    
    TK_INPUT,     
    TK_OUTPUT,    
    TK_WHILE,     
    TK_ENDWHILE,  
    TK_CHAR,      
    TK_FUNCTION,  
    TK_ENDFUNCTION,
    TK_ELSEIF,    
    TK_ELSE,      
    TK_RECORD,    
    TK_ENDRECORD, 
    TK_ARRAY,     
    TK_MAP,       
    TK_GET,       
    TK_PUT,       
    TK_PUTS,      
    TK_RETURN,    
    TK_BREAK,     
    TK_CALL,      
    TK_SQL,       
    TK_SQR,       
    TK_SEM,       
    TK_COMMA,     
    TK_DOT,       
    TK_OP,        
    TK_CL,        
    TK_DQT,       
    TK_SQT,       
    TK_PLUS,      
    TK_MINUS,
    TK_MUL,       
    TK_DIV,       
    TK_MOD,       
    TK_AND,       
    TK_OR,        
    TK_NOT,       
    TK_LT,        
    TK_LE,        
    TK_EQ,        
    TK_GT,        
    TK_GE,        
    TK_NE,
    TK_COMMENT,
    TK_ERROR,
    program,
    typeDefinition_s,
    mainFunction,
    typeDefinition,
    fieldDefinition_s,
    fieldDefinition,
    eps,
    moreFields,
    primitiveDatatype,
    moreField_ID,
    globalStatements,
    globalDeclare,
    globalAssign,
    dataType,
    var,
    otherFunctions,
    function,
    input_par,
    output_par,
    stmt_s,
    parameter_list,
    remaining_list,
    constructedDatatype,
    declaration_s,
    otherStmts,
    all_declaration,
    declaration,
    array_declaration,
    map_declaration,
    more_IDs,
    more_array_IDs,
    moreMapID,
    stmt,
    assignmentStmt,
    iterativeStmt,
    ioStmt,
    funCallStmt,
    mapStmt,
    SingleOrRecOrArrayId,
    arithmeticExpression,
    Other_Id,
    numorid,
    more_variables,
    operator,
    idList,
    more_ids,
    booleanExpression,
    conditionalStmt,
    else$elseif,
    elseifs,
    Else,
    elseif,
    allVar,
    Other_Var,
    bExp,
    variable,
    Op,
    logicalOp,
    relationalOp,
    Other_Variable,
    mapAdd,
    mapDelete
  } symbol;

typedef enum {FALSE, TRUE} bool;

typedef struct {
  symbol s;
   char lexeme[100];
} token;

typedef token * tokenp;

struct tokenlist{
  tokenp t;
  struct tokenlist* next;
  int linenumber;
};

  typedef struct tokenlist * tokenlistp;

//keywordtable
typedef struct
{
    bool present;
    symbol s;
    char keyword[100];
} keyword;
typedef keyword * keywordTable;
keywordTable createKeywordTable();

//**********************************

//buffer
typedef char * buffer;
typedef int buffersize;
char getNextChar(int,int*);
//**********************************


// lexer API
void initLex(char * filename);
tokenlistp getTokenlist(int fp, keywordTable kt);
tokenp getNextToken(int fp, keywordTable kt, bool *error, int * linenumber);
void printTokenList(tokenlistp tl);
//lexer helper function
  tokenp check_type(char * lexeme);


// helper functions


char * symbolToStr(symbol s);
int hash(char *keyword, int hashkey);//hash function

#endif

