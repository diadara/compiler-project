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
    
    TK_ERROR
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
#endif


// helper functions
char * symbolToStr(symbol s);
