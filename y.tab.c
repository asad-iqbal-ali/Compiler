#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140101

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "symbol.h"
	#define TABLESIZE 100
	#define WORDSIZE 4
	#define STLEN 32
	#define MAXEXPR 1024
	#define MAXSTRNGS 100
	#define MAXARGS 32

int yywrap(){
	return 1;
}

void yyerror(const char *str){
	fprintf(stderr, "error: %s\n",str);

}

sym_table *global_table;
sym_table *local_table;
char* glb_strings[MAXSTRNGS];
int str_counter = 0;

expr *tmp, *tmp2;
const expr *NOARG = 0;

instr *f_def, *current_block;

char current_function[MAXIDLEN];

symbol *tmp_sym, *tmp_sym2, *current_args;

#line 37 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
 char *a;
 int fn;
 struct expr *e;
 enum type_ t;
 enum compr{
	INFE,
	EGA,
	SU,
	INFEQUA,
	SUPEQUA,
	DIF
 } entier;
 struct symbol_ *s;
 struct instr *i;
 struct declar_ *d;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 79 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define INT 257
#define STRING 258
#define CONST_INT 259
#define CONST_STRING 260
#define IDENT 261
#define EXTERN 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define DO 266
#define RETURN 267
#define FOR 268
#define THEN 269
#define assignment 270
#define INF 271
#define EGAL 272
#define SUP 273
#define INFEQUAL 274
#define SUPEQUAL 275
#define DIFF 276
#define PLUS 277
#define MINUS 278
#define MULTI 279
#define DIV 280
#define SHIFTRIGHT 281
#define SHIFTLEFT 282
#define MODULO 283
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,   28,   28,   28,   17,    9,   13,   13,   16,
   16,   10,   10,   15,   15,   15,   14,   14,   12,   12,
   11,   18,   18,   18,   18,   18,   18,   20,   20,    8,
   19,   19,   19,   19,   29,   30,   25,   25,   22,   22,
   26,   21,   21,   21,   23,   24,   27,   27,   27,   27,
   27,   27,    2,    2,    2,    3,    3,    3,    6,    6,
    6,    6,    4,    4,    5,    5,    5,    7,    7,    1,
    1,    1,    1,
};
static const short yylen[] = {                            2,
    1,    2,    1,    2,    1,    3,    3,    1,    1,    1,
    3,    1,    2,    1,    3,    1,    3,    4,    1,    3,
    2,    1,    1,    1,    1,    1,    1,    2,    2,    3,
    4,    3,    3,    2,    1,    1,    1,    2,    2,    4,
    4,    5,    6,    9,    3,    3,    1,    1,    1,    1,
    1,    1,    1,    3,    3,    1,    3,    3,    1,    3,
    3,    3,    1,    2,    1,    4,    3,    1,    3,    1,
    1,    1,    3,
};
static const short yydefred[] = {                         0,
    8,    9,    0,    0,    3,    0,    5,    1,    4,    0,
    2,    0,    0,   10,    0,   16,    0,    0,   35,    6,
    0,    7,    0,   71,   72,    0,    0,    0,   65,    0,
    0,   59,   63,    0,   17,   19,    0,    0,    0,    0,
    0,    0,    0,    0,   22,   36,    0,    0,   12,    0,
   37,   23,   24,   25,   26,   27,    0,    0,   34,   11,
    0,   64,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   18,   21,    0,    0,    0,    0,    0,    0,   28,
   29,   13,    0,   32,   38,   33,    0,   67,    0,    0,
   73,    0,    0,    0,    0,   60,   61,   62,   20,    0,
    0,    0,    0,    0,   45,    0,    0,   31,    0,    0,
   66,   49,   47,   50,   51,   52,   48,    0,   41,    0,
    0,    0,   40,    0,    0,   42,    0,    0,   43,    0,
    0,    0,   44,
};
static const short yydgoto[] = {                          4,
   29,   47,   31,   32,   33,   34,   90,   48,    5,   50,
   36,   37,   10,   16,   14,   15,    7,   51,   52,   53,
   54,   55,   56,  102,   57,   58,  118,    8,   21,   59,
};
static const short yysindex[] = {                      -192,
    0,    0, -173, -192,    0, -235,    0,    0,    0, -235,
    0,   -7,  -76,    0,  -21,    0,   50,  -40,    0,    0,
   58,    0, -235,    0,    0,   14,   50,   50,    0, -194,
 -185,    0,    0, -223,    0,    0,  -22, -172,   -6,   29,
   54,  100,   50,   56,    0,    0,  -57,   38,    0,   58,
    0,    0,    0,    0,    0,    0,   72,  100,    0,    0,
   96,    0,  -30,   50,   50,   50,   50,   50,   50,   50,
 -173,    0,    0,   50,   50,   50, -163,  -55, -150,    0,
    0,    0,   72,    0,    0,    0, -146,    0, -194,    4,
    0, -185, -185, -223, -223,    0,    0,    0,    0, -194,
 -168,   78,   79,   81,    0, -148,   64,    0,  100,   50,
    0,    0,    0,    0,    0,    0,    0,   50,    0,  100,
   50,   50,    0, -194, -194,    0,   83,   66,    0, -150,
   87,  100,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -15,   -9,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -41,    0,    0,    0,   -8,
    8,    0,    0,  -28,    0,    0,    0,    0,  102,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   86,    0,   30,    0,
    0,   20,   32,  -16,   -4,    0,    0,    0,    0,  -32,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   34,  -27,    0,    0,    0,    0,    0,
    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,   25,   45,   12,    0,   49,    0,  -72,    9,    0,
   59,    0,    6,  121,  106,    0,    0,  -37,  119,    0,
    0,    0,    0,  -59,   84,    0,    0,  129,    0,  -42,
};
#define YYTABLESIZE 385
static const short yytable[] = {                         70,
   35,   80,   70,  105,   77,    6,  107,   84,   30,    6,
   91,    9,   56,   46,   86,   56,  103,   70,   72,   85,
   87,   71,   23,   38,   57,   12,   30,   57,   14,   49,
   56,   46,   18,   61,   16,   15,   58,   22,   62,   58,
  108,   30,   57,   14,  111,   85,   19,  110,   53,   16,
   15,   53,   63,   61,   58,   68,   69,  131,   82,   70,
   55,  127,  128,   55,    1,    2,   53,   78,   75,    3,
   68,  123,   54,   68,   69,   54,   38,   69,   55,   96,
   97,   98,  126,    1,    2,   89,   64,   65,   73,   28,
   54,   66,   67,   76,  133,   79,   81,   28,  100,  101,
  101,  104,  112,  113,  114,  115,  116,  117,   92,   93,
  106,   28,   64,   65,   94,   95,   45,  109,  119,  120,
  121,   74,  122,  129,  130,   39,   13,  132,   60,   99,
   45,   20,   11,   83,  124,   28,   88,    0,    0,   28,
    0,    0,  125,    0,   39,  101,  101,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   45,    0,
   70,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   19,    0,   46,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   19,    0,   46,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   39,    0,
   39,    0,    0,    0,    0,    0,    1,    2,    0,    0,
    0,    0,   19,   64,   65,   64,   65,    0,    0,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   56,   56,   56,   56,   56,   56,   56,   56,
   64,   65,   56,   56,   57,   57,   57,   57,   57,   57,
   57,   57,   17,   74,   57,   57,   58,   58,   58,   58,
   58,   58,   58,   58,    0,    0,   58,   58,   53,   53,
   53,   53,   53,   53,    0,    0,    0,    0,   53,   53,
   55,   55,   55,   55,   55,   55,    0,    0,    0,    0,
   55,   55,   54,   54,   54,   54,   54,   54,   24,   25,
   26,    0,   54,   54,    1,    2,   24,   25,   39,    0,
   40,    0,   41,   42,   43,   44,    0,   27,    0,    0,
   24,   25,   39,    0,   40,   27,   41,   42,   43,   44,
    0,    0,    0,    0,   39,   39,   39,    0,   39,   27,
   39,   39,   39,   39,   24,   25,   26,    0,   24,   25,
   39,    0,   40,   39,   41,   42,   43,   44,    0,    0,
    0,    0,    0,   27,    0,    0,    0,   27,   70,   70,
   70,   70,   70,   70,   70,
};
static const short yycheck[] = {                         41,
   41,   59,   44,   59,   42,    0,   79,   50,   41,    4,
   41,    3,   41,   41,   57,   44,   76,   59,   41,   57,
   58,   44,   44,   18,   41,  261,   59,   44,   44,   21,
   59,   59,   40,   40,   44,   44,   41,   59,   27,   44,
   83,   17,   59,   59,   41,   83,  123,   44,   41,   59,
   59,   44,   28,   40,   59,  279,  280,  130,   50,  283,
   41,  121,  122,   44,  257,  258,   59,   43,   40,  262,
   41,  109,   41,   44,   41,   44,   71,   44,   59,   68,
   69,   70,  120,  257,  258,   61,  281,  282,  261,   40,
   59,  277,  278,   40,  132,   40,   59,   40,   74,   75,
   76,  265,  271,  272,  273,  274,  275,  276,   64,   65,
  261,   40,  281,  282,   66,   67,   59,  264,   41,   41,
   40,  270,   59,   41,   59,   40,    6,   41,   23,   71,
   59,   13,    4,   50,  110,   40,   41,   -1,   -1,   40,
   -1,   -1,  118,   -1,   59,  121,  122,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,   -1,
   59,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  123,   -1,  125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  123,   -1,  125,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,
  125,   -1,   -1,   -1,   -1,   -1,  257,  258,   -1,   -1,
   -1,   -1,  123,  281,  282,  281,  282,   -1,   -1,  271,
  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,  283,  271,  272,  273,  274,  275,  276,  277,  278,
  281,  282,  281,  282,  271,  272,  273,  274,  275,  276,
  277,  278,  270,  270,  281,  282,  271,  272,  273,  274,
  275,  276,  277,  278,   -1,   -1,  281,  282,  271,  272,
  273,  274,  275,  276,   -1,   -1,   -1,   -1,  281,  282,
  271,  272,  273,  274,  275,  276,   -1,   -1,   -1,   -1,
  281,  282,  271,  272,  273,  274,  275,  276,  259,  260,
  261,   -1,  281,  282,  257,  258,  259,  260,  261,   -1,
  263,   -1,  265,  266,  267,  268,   -1,  278,   -1,   -1,
  259,  260,  261,   -1,  263,  278,  265,  266,  267,  268,
   -1,   -1,   -1,   -1,  259,  260,  261,   -1,  263,  278,
  265,  266,  267,  268,  259,  260,  261,   -1,  259,  260,
  261,   -1,  263,  278,  265,  266,  267,  268,   -1,   -1,
   -1,   -1,   -1,  278,   -1,   -1,   -1,  278,  277,  278,
  279,  280,  281,  282,  283,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 283
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? (YYMAXTOKEN + 1) : (a))
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,0,"';'",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"INT",
"STRING","CONST_INT","CONST_STRING","IDENT","EXTERN","IF","ELSE","WHILE","DO",
"RETURN","FOR","THEN","assignment","INF","EGAL","SUP","INFEQUAL","SUPEQUAL",
"DIFF","PLUS","MINUS","MULTI","DIV","SHIFTRIGHT","SHIFTLEFT","MODULO",
"illegal-symbol",
};
static const char *yyrule[] = {
"$accept : program",
"program : external_declaration",
"program : program external_declaration",
"external_declaration : declaration",
"external_declaration : EXTERN declaration",
"external_declaration : function_definition",
"function_definition : type function_declarator compound_instruction",
"declaration : type declarator_list ';'",
"type : INT",
"type : STRING",
"declarator_list : declarator",
"declarator_list : declarator_list ',' declarator",
"declaration_list : declaration",
"declaration_list : declaration_list declaration",
"declarator : IDENT",
"declarator : IDENT assignment expression",
"declarator : function_declarator",
"function_declarator : IDENT '(' ')'",
"function_declarator : IDENT '(' parameter_list ')'",
"parameter_list : parameter_declaration",
"parameter_list : parameter_list ',' parameter_declaration",
"parameter_declaration : type IDENT",
"instruction : ';'",
"instruction : compound_instruction",
"instruction : expression_instruction",
"instruction : iteration_instruction",
"instruction : select_instruction",
"instruction : jump_instruction",
"expression_instruction : expression ';'",
"expression_instruction : assignment_expression ';'",
"assignment_expression : IDENT assignment expression",
"compound_instruction : block_start declaration_list instruction_list block_end",
"compound_instruction : block_start declaration_list block_end",
"compound_instruction : block_start instruction_list block_end",
"compound_instruction : block_start block_end",
"block_start : '{'",
"block_end : '}'",
"instruction_list : instruction",
"instruction_list : instruction_list instruction",
"select_instruction : cond_instruction instruction",
"select_instruction : cond_instruction instruction ELSE instruction",
"cond_instruction : IF '(' condition ')'",
"iteration_instruction : WHILE '(' condition ')' instruction",
"iteration_instruction : DO instruction WHILE '(' condition ')'",
"iteration_instruction : FOR '(' assignment_expression ';' condition ';' assignment_expression ')' instruction",
"jump_instruction : RETURN expression ';'",
"condition : expression comparison_operator expression",
"comparison_operator : EGAL",
"comparison_operator : DIFF",
"comparison_operator : INF",
"comparison_operator : SUP",
"comparison_operator : INFEQUAL",
"comparison_operator : SUPEQUAL",
"expression : expression_additive",
"expression : expression SHIFTLEFT expression_additive",
"expression : expression SHIFTRIGHT expression_additive",
"expression_additive : expression_multiplicative",
"expression_additive : expression_additive PLUS expression_multiplicative",
"expression_additive : expression_additive MINUS expression_multiplicative",
"expression_multiplicative : unary_expression",
"expression_multiplicative : expression_multiplicative MULTI unary_expression",
"expression_multiplicative : expression_multiplicative DIV unary_expression",
"expression_multiplicative : expression_multiplicative MODULO unary_expression",
"unary_expression : expression_postfixee",
"unary_expression : MINUS unary_expression",
"expression_postfixee : primary_expression",
"expression_postfixee : IDENT '(' argument_expression_list ')'",
"expression_postfixee : IDENT '(' ')'",
"argument_expression_list : expression",
"argument_expression_list : argument_expression_list ',' expression",
"primary_expression : IDENT",
"primary_expression : CONST_INT",
"primary_expression : CONST_STRING",
"primary_expression : '(' expression ')'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 826 "parser.y"

int main(void) {

	global_table = malloc(sizeof(sym_table));
	global_table->table = malloc(sizeof(symbol *)*TABLESIZE);
	global_table->prev = NULL;
	global_table->next = NULL;


	local_table = global_table;
	
	
	yyparse();
	
	while(local_table != NULL)
		local_table = destroy_table(local_table);
		
	return 0;
}

int hash_sym(char *sym){
	unsigned int hash = 0;
	int i;

	for(i = 0; sym[i] != '\0'; ++i)
		hash = sym[i] + (hash << 6) + (hash << 16) - hash;
	return hash % TABLESIZE;
}

int find_symbol(char *sym, symbol **out, sym_table *t){
	symbol *track;
	sym_table *ti = t;
	int depth = 0;
	
	int i = hash_sym(sym);
	
	while(ti != NULL){
		track = ti->table[i];
		while(track != NULL){
			if(!strcmp(track->id, sym)){
				*out = track;
				return depth;
			}
			else track = track->next;
		}
		ti = ti->prev;
		++depth;
	}
	*out = NULL;
	return -1;

}






symbol *add_symbol(char *name, enum type_ t, enum type_ *a, sym_table *tbl){
	symbol *symb = malloc(sizeof(symbol));
	symb->id = name;
	symb->type = t;
	symb->args = a;
	symb->next = NULL;

	int i = hash_sym(symb->id);
	
	symbol *track = tbl->table[i];
	symbol *prev = track;

	if(track == NULL){
		tbl->table[i] = symb;
		if(symb->args == NULL){
			switch(t){
				case INTEG:
					tbl->size += WORDSIZE;
					symb->location = tbl->size;
					break;
				case STRIN:
					tbl->size += WORDSIZE*STLEN;
					symb->location = tbl->size;
					break;
				case ARG_INTEG:
					tbl->arg_size += WORDSIZE;
					symb->location = tbl->arg_size;
					break;
				case ARG_STRIN:
					tbl->arg_size += WORDSIZE*STLEN;
					symb->location = tbl->arg_size;
					break;

			}
			
			
		}
		return symb;
	}

	while(track != NULL){
		if(!strcmp(track->id, symb->id)){
			if(symb->type != track->type){
				yyerror("Conflicting definitions");
				return NULL;
			}
			if(track->args != NULL || symb->args != NULL){
				if(track->args == NULL || symb->args == NULL){
						yyerror("Conflicting function definitions");
						return NULL;
					}
				else{
					i = 0;
					while(track->args[i] != VOID && symb->args[i] != VOID){
						if(track->args[i] != symb->args[i]){
							yyerror("Conflicting function definitions");
							return NULL;
						}
					}
					if(track->args[i] != VOID || symb->args[i] != VOID){
							yyerror("Conflicting function definitions");
							return NULL;
					}
					
				}
			}
			return track;
		}
		prev = track;
		track = track->next;
	}
	
	track = prev;
	
	track->next = symb; 
	if(symb->args == NULL){
			switch(t){
				case INTEG:
					tbl->size += WORDSIZE;
					symb->location = tbl->size;
					break;
				case STRIN:
					tbl->size += WORDSIZE*STLEN;
					symb->location = tbl->size;
					break;
				case ARG_INTEG:
					tbl->arg_size += WORDSIZE;
					symb->location = tbl->arg_size;
					break;
				case ARG_STRIN:
					tbl->arg_size += WORDSIZE*STLEN;
					symb->location = tbl->arg_size;
					break;
			}
			
			
	}
	return symb;



}


sym_table *create_table(sym_table *loc){
	
	
	if(loc->next != NULL){
		yyerror("Creating table in middle of list");
		return NULL;
	}
	
	loc->next = malloc(sizeof(sym_table));
	loc->next->table = malloc(sizeof(symbol *)*TABLESIZE);
	loc->next->prev = loc;
	loc->next->next = NULL;
	loc->next->size = 0;
	loc->next->arg_size = 0;
	return loc->next;

}

sym_table *destroy_table(sym_table *loc){
	
	symbol *s_track, *s_next;
	
	sym_table *ret = loc->prev;
	
	int i;
	for(i = 0; i < TABLESIZE; ++i){
		s_track = loc->table[i];
		while(s_track != NULL){
			free(s_track->args);
			s_next = s_track->next;
			free(s_track);
			s_track = s_next;
		}
	}
	
	free(loc->table);
	free(loc);
	return ret;
	
}

void print_instructions(instr *block){

	if(block->prev == NULL)
		printf(".globl %s\n\t.type %s,@function\n%s:\n", block->function, block->function, block->function);

	printf("  enter $%d, $0," block->stack_size);



}
/*

char *print_type(enum type_ t){
	switch(t){
		case INTEG:
		 return "integer";
		case STRIN:
		 return "string";
		case FUNCTION:
		 return "function";
		case VOID:
		 return "void";
		default:
		 return "unknown";
	}

}

void print_table(sym_table *t){


	int i;
	symbol *s;
	arg *a;

	printf("Symbol table");
	if(t->func != NULL)
		printf(" for function %s\n", t->func->id);
	else if(t->prev == NULL)
		printf(" GLOBAL\n");
	else printf("\n");

	printf("\n");

	printf("ID\t\t| type\t\t\t| Arguments\n");
	printf("------------------------------------------------------\n");

	for(i = 0; i < TABLESIZE; ++i){
		s = t->table[i];
		while(s != NULL){
			printf("%s\t\t| %s\t\t| ", s->id, print_type(s->type));
			if(s->type == FUNCTION){
				a = s->alist;
				while(a != NULL){
					printf("%s ", print_type(a->type));
					a = a->next;
				}
			}
			printf("\n");
			s = s->next;

		}


	}
	printf("\n");
}

void print_sym(char *symb, symbol **table){

	symbol *track = table[hash_sym(symb)];
	arg *argument;

	while(track != NULL){
		if(!strcmp(track->id, symb)){
			printf("Function: %s\n", track->id);
			printf("Arguments: ");
			argument = track->alist;
			while(argument != NULL){
				printf("%s ",argument->id);
				argument = argument->next; 
			}
			printf("\n");
			return;
		}
		else track = track->next;
	}
	return;


}
*/
#line 729 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 4:
#line 102 "parser.y"
	{printf(" as extern\n");}
break;
case 6:
#line 107 "parser.y"
	{
						print_instructions(f_def);
						f_def = NULL;
						current_args = NULL;

						}
break;
case 7:
#line 118 "parser.y"
	{
					declar *t = yystack.l_mark[-1].d;
					int argcount = 0;
					enum type_ *argtypes = NULL;
					expr *last_instruction = NULL;
					expr *first_instruction;

					while(t != NULL){
						if(t->args == NULL)
							tmp_sym = add_symbol(t->id, yystack.l_mark[-2].t, NULL, local_table);
							if(t->set != NULL){
								if(last_instruction == NULL){
									last_instruction = t->set;
									first_instruction = t->set;
								}
								else 	
									last_instruction->next = t->set;

								int i = find_symbol(yystack.l_mark[-2].t, tmp_sym, local_table);
								
								if(tmp_sym->type != t->set->type){
									yyerror("conflicting types in assignment expression");
									return -1;
								}
									
								tmp = t->set;
								while(tmp != NULL){
									tmp2 = tmp;
									tmp = tmp->next;			
								}
								tmp2 = malloc(sizeof(expr));
								tmp2->type = SET;
		
								tmp2->data = malloc(sizeof(char)*MAXEXPR);
								tmp2->data[0] = '\0';
								if(i == 0){
									if(tmp_sym->type == INTEG)
										snprintf(tmp2->data, MAXEXPR, "  popl -%d(%%rbp)\n", tmp_sym->location);
									else
										snprintf(tmp2->data, MAXEXPR, "  leal -%d(%%rbp), %%eax\n  pushl %%eax\n  call strncpy\n  movb $0, %d(%%eax)\n  addl $12, %%esp\n", tmp_sym->location, (WORDSIZE*STRLEN)-1);
								}
								else{
									char *cur = tmp2->data;
									char *end = cur + MAXEXPR;
									cur += snprintf(tmp2->data, MAXEXPR, "  leal (%%rbp), %%ecx\n");
									while(i > 1){
										cur += snprintf(cur, end-cur,"  leal (%%ecx), %%ecx\n");
										--i;
									}
									if(tmp_sym->type == INTEG)
										cur += snprintf(cur, end-cur, "  popl -%d(%%ecx)\n", tmp_sym->location);
									else
										snprintf(tmp2->data, MAXEXPR, "  leal -%d(%%ecx), %%eax\n  pushl %%eax\n  call strncpy\n  movb $0, %d(%%eax)\n  addl $12, %%esp\n", tmp_sym->location, (WORDSIZE*STRLEN)-1);
		
								}
	


								tmp2->args = NULL;

								while(last_instruction->next != NULL)
									last_instruction = last_instruction-> next;
							}
						else{
							tmp_sym = t->args;
							if(tmp_sym == NOARGS){
								argtypes = malloc(sizeof(enum type_));
								*argtypes = VOID;
							}
							else{
								while(tmp_sym != NULL){
									argcount++;
									tmp_sym = tmp_sym->next;
								}
								argtypes = malloc(sizeof(enum type_)*argcount);
								argcount = 0;
								while(tmp_sym != NULL){
									argtypes[argcount] = tmp_sym->type;
									argcount++;
									tmp_sym = tmp_sym->next;
								}
							}
							tmp_sym = add_symbol(t->id, yystack.l_mark[-2].t, argtypes, local_table);


						}
						t = t->next;
						
					}
					yyval.e = last_instruction;
					tmp = current_block->list;
					if(tmp == NULL)
						current_block->list = first_instruction;
					else{
						while(tmp->next != NULL)
							tmp = tmp->next;
						tmp->next = first_instruction;

					}
					
				}
break;
case 8:
#line 222 "parser.y"
	{yyval.t = INTEG;}
break;
case 9:
#line 223 "parser.y"
	{yyval.t = STRIN;}
break;
case 10:
#line 227 "parser.y"
	{yyval.d = yystack.l_mark[0].d;}
break;
case 11:
#line 228 "parser.y"
	{declar *t = yystack.l_mark[-2].d;
				while(t->next != NULL)
					t = t->next;
				t->next = yystack.l_mark[0].d;
				yyval.d = yystack.l_mark[-2].d;}
break;
case 12:
#line 236 "parser.y"
	{yyval.e = yystack.l_mark[0].e;}
break;
case 13:
#line 237 "parser.y"
	{
					

			
				}
break;
case 14:
#line 245 "parser.y"
	{
				int i = find_symbol(yystack.l_mark[0].a, &tmp_sym, local_table);
				if(tmp_sym != NULL){
					yyerror("symbol already declared");
					return -1;
				}
				
				yyval.d = malloc(sizeof(declar));
			 	strcpy(yyval.d->id, yystack.l_mark[0].a);
				yyval.d->set = NULL;
				yyval.d->args = NULL;
				yyval.d->next = NULL;
			}
break;
case 15:
#line 258 "parser.y"
	{
				int i = find_symbol(yystack.l_mark[-2].a, &tmp_sym, local_table);
				if(tmp_sym != NULL){
					yyerror("symbol already declared");
					return -1;
				}
				
				yyval.d = malloc(sizeof(declar));
			 	strcpy(yyval.d->id, yystack.l_mark[-2].a);
				yyval.d->set = yystack.l_mark[0].e;
				yyval.d->args = NULL;
				yyval.d->next = NULL;
				}
break;
case 16:
#line 271 "parser.y"
	{yyval.d = yystack.l_mark[0].d;}
break;
case 17:
#line 275 "parser.y"
	{
					strcpy(current_function, yystack.l_mark[-2].a);
				
					yyval.d = malloc(sizeof(declar));
			 		strcpy(yyval.d->id, yystack.l_mark[-2].a);
					yyval.d->set = NULL;
					yyval.d->args = NOARG;
					yyval.d->next = NULL;
	
				}
break;
case 18:
#line 285 "parser.y"
	{
					strcpy(current_function, yystack.l_mark[-3].a);
					current_args = yystack.l_mark[-1].s;

					
					yyval.d = malloc(sizeof(declar));
			 		strcpy(yyval.d->id, yystack.l_mark[-3].a);
					yyval.d->set = NULL;
					yyval.d->args = yystack.l_mark[-1].s;
					yyval.d->next = NULL;
	
				}
break;
case 19:
#line 300 "parser.y"
	{yyval.s = yystack.l_mark[0].s;}
break;
case 20:
#line 301 "parser.y"
	{
						tmp_sym = yystack.l_mark[-2].s;
						while(tmp->next != NULL)
							tmp = tmp->next;
						tmp->next= malloc(sizeof(symbol));
						tmp->next->type = yystack.l_mark[0].s->type;
						tmp->next->next = NULL;
						yyval.s = yystack.l_mark[-2].s;
					}
break;
case 21:
#line 312 "parser.y"
	{
					yyval.s = malloc(sizeof(symbol);
					yyval.s->type = yystack.l_mark[-1].t;
					strcpy(yyval.s->id, yystack.l_mark[0].a);
					yyval.s->next = NULL;
				}
break;
case 22:
#line 322 "parser.y"
	{yyval.i = NULL;}
break;
case 23:
#line 323 "parser.y"
	{yyval.i=yystack.l_mark[0].i;}
break;
case 24:
#line 324 "parser.y"
	{yyval.i=yystack.l_mark[0].i;}
break;
case 25:
#line 325 "parser.y"
	{yyval.i=yystack.l_mark[0].i;}
break;
case 26:
#line 326 "parser.y"
	{yyval.i=yystack.l_mark[0].i;}
break;
case 27:
#line 327 "parser.y"
	{yyval.i=yystack.l_mark[0].i;}
break;
case 28:
#line 331 "parser.y"
	{
			tmp = current_block->list;
			if(tmp == NULL)
				current_block->list = yystack.l_mark[-1].e;
			else{
				while(tmp->next != NULL)
					tmp = tmp->next;
				tmp->next = yystack.l_mark[-1].e;

			}
			yyval.i = yystack.l_mark[-1].e;
		}
break;
case 29:
#line 343 "parser.y"
	{
				tmp = current_block->list;
				if(tmp == NULL)
					current_block->list = yystack.l_mark[-1].e;
				else{
					while(tmp->next != NULL)
						tmp = tmp->next;
					tmp->next = yystack.l_mark[-1].e;

				}
				yyval.i = yystack.l_mark[-1].e;
			    }
break;
case 30:
#line 358 "parser.y"
	{ 
					int i = find_symbol(yystack.l_mark[-2].a, tmp_sym, local_table);
					if(tmp_sym == NULL){
						yyerror("symbol not found");
						return -1;
					}
					if(tmp_sym->type != yystack.l_mark[0].e->type){
						yyerror("conflicting types in assignment expression");
						return -1;
					}
					if(tmp_sym->args != NULL){
						yyerror("assigning value to function");
						return -1;
					}
					tmp = yystack.l_mark[0].e;
					while(tmp != NULL){
						tmp2 = tmp;
						tmp = tmp->next;			
					}
					tmp2 = malloc(sizeof(expr));
					tmp2->type = SET;
		
					tmp2->data = malloc(sizeof(char)*MAXEXPR);
					tmp2->data[0] = '\0';
					if(i == 0){
						if(tmp_sym->type == INTEG || tmp_sym->type == ARG_INTEG)
							snprintf(tmp2->data, MAXEXPR, "  popl %s%d(%%rbp)\n", (tmp_sym->type == ARG_INTEG? "","-")tmp_sym->location);
						else
							snprintf(tmp2->data, MAXEXPR, "  leal %s%d(%%rbp), %%eax\n  pushl %%eax\n  call strncpy\n  movb $0, %d(%%eax)\n  addl $12, %%esp\n", (tmp_symp->type == ARG_STRIN? "","-")tmp_sym->location, (WORDSIZE*STRLEN)-1);
					}
					else{
						char *cur = tmp2->data;
						char *end = cur + MAXEXPR;
						cur += snprintf(tmp2->data, MAXEXPR, "  leal (%%rbp), %%ecx\n");
						while(i > 1){
							cur += snprintf(cur, end-cur,"  leal (%%ecx), %%ecx\n");
							--i;
						}
						if(tmp_sym->type == INTEG || tmp_sym->type == ARG_INTEG)
							cur += snprintf(cur, end-cur, "  popl %s%d(%%ecx)\n", (tmp_sym->type == ARG_INTEG? "","-")tmp_sym->location);
						else
							snprintf(tmp2->data, MAXEXPR, "  leal %s%d(%%ecx), %%eax\n  pushl %%eax\n  call strncpy\n  movb $0, %d(%%eax)\n  addl $12, %%esp\n", (tmp_symp->type == ARG_STRIN? "","-")tmp_sym->location, (WORDSIZE*STRLEN)-1);
		
					}
	


					tmp2->args = NULL;
					yyval.e = yystack.l_mark[0].e;
				}
break;
case 31:
#line 411 "parser.y"
	{yyval.i=yystack.l_mark[-1].i;}
break;
case 32:
#line 412 "parser.y"
	{yyval.i = yystack.l_mark[-1].e;}
break;
case 33:
#line 413 "parser.y"
	{yyval.i=yystack.l_mark[-1].i;}
break;
case 34:
#line 414 "parser.y"
	{yyval.i = NULL;}
break;
case 35:
#line 419 "parser.y"
	{


		local_table = create_table(local_table);
		if(f_def == NULL){
			f_def = malloc(sizeof(instr);
			f_def->prev = NULL;
			f_def->prev_ins = NULL;
			current_block = f_def;
			f_def->function = current_function;
			f_def->args = current_args;
			tmp_sym = current_args;
			while(tmp_sym != NULL){
				if(tmp_sym->type == STRIN)
					add_symbol(tmp_sym->id,ARG_STRIN,NULL,local_table);
				else add_symbol(tmp_sym->id,ARG_INTEG,NULL,local_table);

			}
			
		}
		else{
			tmp = current_block->list;
			if(tmp != NULL){			
				while(tmp->next != NULL){
					tmp = tmp->next;
				}
				tmp->next = malloc(sizeof(expr));
				tmp = tmp->next;
			}
			else tmp = malloc(sizeof(expr));
			tmp->type = BLOCK_JUMP;
			tmp->next = NULL;
			tmp->block = malloc(sizeof(instr));
			tmp->block->prev = current_block;
			current_block = tmp->block;
			current_block->prev_ins = tmp;
			current_block->list = NULL;
		}


	}
break;
case 36:
#line 463 "parser.y"
	{
		if(local_table == global_table){
			yyerror("No block to close");
			return -1;
		}
		current_block->stack_size = local_table->size;
		current_block = current_block->prev;
		local_table = destroy_table(local_table);

	 
	 
	}
break;
case 37:
#line 478 "parser.y"
	{yyval.i=yystack.l_mark[0].i;}
break;
case 38:
#line 479 "parser.y"
	{
					tmp = yystack.l_mark[-1].i;
					while(tmp != NULL){
						tmp = tmp->next;
					}

					tmp->next = yystack.l_mark[0].i;
					yyval.i = yystack.l_mark[-1].i;
				}
break;
case 41:
#line 496 "parser.y"
	{yyval.i=yystack.l_mark[-1].i;}
break;
case 42:
#line 500 "parser.y"
	{printf("while loop\n");}
break;
case 43:
#line 501 "parser.y"
	{printf("do/while loop\n");}
break;
case 44:
#line 502 "parser.y"
	{printf("for loop ");}
break;
case 45:
#line 506 "parser.y"
	{
			instr *t = malloc(sizeof(instr);
			t->next = NULL;
			yyval.i = t;

			tmp = yystack.l_mark[-1].e;
			while(tmp != NULL){
				tmp2 = tmp;
				tmp = tmp->next;			
			}
			tmp2 = malloc(sizeof(expr));
			tmp2->type = RETURN;
			tmp2->data = NULL;
			tmp2->args = NULL;				
			tmp2->next = NULL;
	
			if(tmp != NULL){
				tmp->next = tmp2;
				yyval.i->list = yystack.l_mark[-1].e;
			}
			else yyval.i->list = tmp2;
			}
break;
case 46:
#line 531 "parser.y"
	{printf("comparison\n");}
break;
case 47:
#line 535 "parser.y"
	{yyval.entier=EGA;}
break;
case 48:
#line 536 "parser.y"
	{yyval.entier=DIF;}
break;
case 49:
#line 537 "parser.y"
	{yyval.entier=INFE;}
break;
case 50:
#line 538 "parser.y"
	{yyval.entier=SU;}
break;
case 51:
#line 539 "parser.y"
	{yyval.entier=INFEQUA;}
break;
case 52:
#line 540 "parser.y"
	{yyval.entier=SUPEQUA;}
break;
case 53:
#line 544 "parser.y"
	{yyval.e=yystack.l_mark[0].e;}
break;
case 54:
#line 545 "parser.y"
	{
								if(yystack.l_mark[-2].e->type != INTEG || yystack.l_mark[0].e->type != INTEG){
								 	yyerror("left shift requires two integer values");
									return -1;
								}
								tmp = yystack.l_mark[0].e;
			 					tmp2 = tmp->next;
								while(tmp2 != NULL){
									tmp = tmp2;
									tmp2 = tmp2->next;
			 					}
			 					tmp->next = yystack.l_mark[-2].e;
								while(tmp->next != NULL)
								tmp = tmp->next;
								tmp->next = malloc(sizeof(expr));
								tmp->next->type = LSHIFT;
								tmp->next->data = NULL;
								tmp->next->args = NULL;				
								tmp->next->next = NULL;
								yyval.e = yystack.l_mark[0].e;

							}
break;
case 55:
#line 567 "parser.y"
	{
								if(yystack.l_mark[-2].e->type != INTEG || yystack.l_mark[0].e->type != INTEG){
								 	yyerror("right shift requires two integer values");
									return -1;
								}
								tmp = yystack.l_mark[0].e;
			 					tmp2 = tmp->next;
								while(tmp2 != NULL){
									tmp = tmp2;
									tmp2 = tmp2->next;
			 					}
			 					tmp->next = yystack.l_mark[-2].e;
								while(tmp->next != NULL)
								tmp = tmp->next;
								tmp->next = malloc(sizeof(expr));
								tmp->next->type = RSHIFT;
								tmp->next->data = NULL;
								tmp->next->args = NULL;				
								tmp->next->next = NULL;
								yyval.e = yystack.l_mark[0].e;

							}
break;
case 56:
#line 591 "parser.y"
	{yyval.e=yystack.l_mark[0].e;}
break;
case 57:
#line 592 "parser.y"
	{
								
								tmp = yystack.l_mark[0].e;
			 					tmp2 = tmp->next;
								while(tmp2 != NULL){
									tmp = tmp2;
									tmp2 = tmp2->next;
			 					}
			 					tmp->next = yystack.l_mark[-2].e;
								while(tmp->next != NULL)
								tmp = tmp->next;
								tmp->next = malloc(sizeof(expr));
								tmp->next->type = ADD;
								tmp->next->data = NULL;
								tmp->next->args = NULL;				
								tmp->next->next = NULL;
								yyval.e = yystack.l_mark[0].e;

							}
break;
case 58:
#line 611 "parser.y"
	{
								if(yystack.l_mark[-2].e->type != INTEG || yystack.l_mark[0].e->type != INTEG){
								 	yyerror("subtraction requires two integer values");
									return -1;
								}
								tmp = yystack.l_mark[0].e;
			 					tmp2 = tmp->next;
								while(tmp2 != NULL){
									tmp = tmp2;
									tmp2 = tmp2->next;
			 					}
			 					tmp->next = yystack.l_mark[-2].e;
								while(tmp->next != NULL)
								tmp = tmp->next;
								tmp->next = malloc(sizeof(expr));
								tmp->next->type = SUB;
								tmp->next->data = NULL;
								tmp->next->args = NULL;				
								tmp->next->next = NULL;
								yyval.e = yystack.l_mark[0].e;

							}
break;
case 59:
#line 635 "parser.y"
	{yyval.e=yystack.l_mark[0].e;}
break;
case 60:
#line 636 "parser.y"
	{
								if(yystack.l_mark[-2].e->type != INTEG || yystack.l_mark[0].e->type != INTEG){
								 	yyerror("multiplication requires two integer values");
									return -1;
								}
								tmp = yystack.l_mark[0].e;
			 					tmp2 = tmp->next;
								while(tmp2 != NULL){
									tmp = tmp2;
									tmp2 = tmp2->next;
			 					}
			 					tmp->next = yystack.l_mark[-2].e;
								while(tmp->next != NULL)
								tmp = tmp->next;
								tmp->next = malloc(sizeof(expr));
								tmp->next->type = MULT;
								tmp->next->data = NULL;
								tmp->next->args = NULL;				
								tmp->next->next = NULL;
								yyval.e = yystack.l_mark[0].e;

							}
break;
case 61:
#line 658 "parser.y"
	{
								if(yystack.l_mark[-2].e->type != INTEG || yystack.l_mark[0].e->type != INTEG){
								 	yyerror("division requires two integer values");
									return -1;
								}
								tmp = yystack.l_mark[0].e;
			 					tmp2 = tmp->next;
								while(tmp2 != NULL){
									tmp = tmp2;
									tmp2 = tmp2->next;
			 					}
			 					tmp->next = yystack.l_mark[-2].e;
								while(tmp->next != NULL)
								tmp = tmp->next;
								tmp->next = malloc(sizeof(expr));
								tmp->next->type = DIV;
								tmp->next->data = NULL;
								tmp->next->args = NULL;				
								tmp->next->next = NULL;
								yyval.e = yystack.l_mark[0].e;

							}
break;
case 62:
#line 680 "parser.y"
	{
								if(yystack.l_mark[-2].e->type != INTEG || yystack.l_mark[0].e->type != INTEG){
								 	yyerror("modulo requires two integer values");
									return -1;
								}
								tmp = yystack.l_mark[0].e;
			 					tmp2 = tmp->next;
								while(tmp2 != NULL){
									tmp = tmp2;
									tmp2 = tmp2->next;
			 					}
			 					tmp->next = yystack.l_mark[-2].e;
								while(tmp->next != NULL)
								tmp = tmp->next;
								tmp->next = malloc(sizeof(expr));
								tmp->next->type = MOD;
								tmp->next->data = NULL;
								tmp->next->args = NULL;				
								tmp->next->next = NULL;
								yyval.e = yystack.l_mark[0].e;

							}
break;
case 63:
#line 706 "parser.y"
	{yyval.e=yystack.l_mark[0].e;}
break;
case 64:
#line 707 "parser.y"
	{
			 	yyval.e=yystack.l_mark[0].e;
			
				strcat(yyval.e->data, "  pop %%edx\n  movl $0, %%ecx\n  subl %%edx, ecx\n  push %%ecx\n");
				}
break;
case 65:
#line 715 "parser.y"
	{yyval.e=yystack.l_mark[0].e;}
break;
case 66:
#line 716 "parser.y"
	{

					int i = find_symbol(yystack.l_mark[-3].a, tmp_sym, local_table);
					if(tmp_sym == NULL){
						yyerror("symbol not found");
						return -1;
					}
					yyval.e = malloc(sizeof(expr));
					if(tmp_sym->args == NULL){
						yyerror("expected function call");
						return -1;
					}
					yyval.e->type = tmp_symb->type;
					yyval.e->data = yystack.l_mark[-3].a;
					yyval.e->next = NULL;
					yyval.e->args = yystack.l_mark[-1].e;

					tmp = yyval.e->args;
					i = 0;
					while(tmp!= NULL || tmp_sym->args[i] != VOID){
						if(tmp== NULL || tmp_sym->args[i] == VOID || tmp->type != tmp_sym->args[i]){
							yyerror("function call types do not match function declaration");
							return -1;
						}
						tmp = tmp->next;
						++i;
					}}
break;
case 67:
#line 743 "parser.y"
	{
						int i = find_symbol(yystack.l_mark[-2].a, tmp_sym, local_table);
						if(tmp_sym == NULL){
							yyerror("symbol not found");
							return -1;
						}
						yyval.e = malloc(sizeof(expr));
						if(tmp_sym->args == NULL){
							yyerror("expected function call");
							return -1;
						}
						if(tmp_sym->args[1] != VOID){
							yyerror("function call types do not match function declaration");
							return -1;
						}
						yyval.e->type = tmp_symb->type;
						yyval.e->data = yystack.l_mark[-2].a;
						yyval.e->next = NULL;
						yyval.e->args = NOARG;
					}
break;
case 68:
#line 766 "parser.y"
	{yyval.e = yystack.l_mark[0].e;}
break;
case 69:
#line 767 "parser.y"
	{tmp = yystack.l_mark[-2].e;
			 while(tmp->next != NULL)
				tmp = tmp->next;
			tmp->next= yystack.l_mark[0].e;
			yyval.e = yystack.l_mark[-2].e;}
break;
case 70:
#line 775 "parser.y"
	{
	int i = find_symbol(yystack.l_mark[0].a, tmp_sym, local_table);
	if(tmp_sym == NULL){
		yyerror("symbol not found");
		return -1;
	}
	yyval.e = malloc(sizeof(expr));
	yyval.e->type = tmp_sym->type;
	if(tmp_sym->args == NULL){
		
		yyval.e->data = malloc(sizeof(char)*MAXEXPR);
		yyval.e->data[0] = '\0';
		if(i == 0)
			snprintf(yyval.e->data, MAXEXPR, "  pushl %s%d(%%rbp)\n", (tmp_sym->type == ARG_INTEG || tmp_symp->type == ARG_STRIN? "","-"), tmp_sym->location);
		else{
			char *cur = yyval.e->data;
			char *end = cur + MAXEXPR;
			cur += snprintf(yyval.e->data, MAXEXPR, "  leal (%%rbp), %%ecx\n");
			while(i > 1){
				cur += snprintf(cur, end-cur,"  leal (%%ecx), %%ecx\n");
				--i;
			}
			cur += snprintf(cur, end-cur, "  pushl %s%d(%%ecx)\n", (tmp_sym->type == ARG_INTEG || tmp_symp->type == ARG_STRIN? "","-"), tmp_sym->location);
		
		}
		yyval.e->args = NULL;
	}

	else yyval.e->data = yystack.l_mark[0].a;
	yyval.e->next = NULL; }
break;
case 71:
#line 805 "parser.y"
	{
		yyval.e = malloc(sizeof(expr));
		yyval.e->type = INTEG;
		yyval.e->args = NULL;
		yyval.e->data = malloc(sizeof(char)*MAXEXPR);
		snprintf(yyval.e->data, MAXEXPR, "  pushl $%d\n", yystack.l_mark[0].fn);
		yyval.e->next = NULL;
		}
break;
case 72:
#line 813 "parser.y"
	{
		yyval.e = malloc(sizeof(expr));
		yyval.e->type = STRIN;
		yyval.e->args = NULL;
		glb_strings[str_counter] = yystack.l_mark[0].a;
		snprintf(yyval.e->data, MAXEXPR, "  pushl $%d\n  pushl $.s%d\n", WORDSIZE*STRLEN, str_counter);
		++str_counter;
		yyval.e->next = NULL;
		}
break;
case 73:
#line 822 "parser.y"
	{yyval.e = yystack.l_mark[-1].e;}
break;
#line 1761 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
