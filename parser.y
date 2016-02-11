%{
	#include<stdio.h>
	#include<string.h>
	#define TABLESIZE 100

int yywrap(){
	return 1;
}

void yyerror(const char *str){
	fprintf(stderr, "error: %s\n",str);

}

enum type_ {
	INTEGER,
	STRING,
	FUNCTION,
	VOID
};

typedef struct arg_{
	char *id;
	enum type_ type;
	union element{
		char *str;
		int i;
	} val;
	struct arg_ *next;
} arg;


typedef struct symbol_{
	char* id;
	enum type_ type;
	enum type_ ret_type;
	arg* alist;
	union element{
		char *str;
		int i;
	} val;
	struct symbol_ *next;
} symbol;

typedef struct sym_table_ {
	symbol **table;
	sym_table_ *prev;
	sym_table_ *next;
} sym_table;


int hash_sym(char *sym);
symbol *find_symbol(char *sym, sym_table t);
void print_sym(char *sym, sym_def **table);
symbol *add_symbol(symbol *symb, symbol **table);

sym_table *create_table(sym_table *loc);
sym_table *destroy_table(sym_table *loc);

sym_table *global_table;
sym_table *local_table;

arg *tmp;
arg *current_args;

symbol *tmp_sym, *tmp_sym2;

%}
%union{
 char *a;
 int fn;
 struct arg_ *g;
 enum type_ t;
 enum compr{
	INF,
	EGAL,
	SUP,
	INFEQUAL,
	SUPEQUAL,
	DIFF
 } entier;
 struct symbol_ *s;
}
%token <t> INT
%token <t> STRING
%token <fn> CONST_INT
%token <a> CONST_STRING

%token <a> IDENT

%token EXTERN

%token IF
%token ELSE
%token WHILE
%token DO
%token RETURN
%token FOR
%token THEN

%token assignment
%token INF
%token EGAL
%token SUP
%token INFEQUAL
%token SUPEQUAL
%token DIFF

%token PLUS
%token MINUS
%token MULTI
%token DIV

%token SHIFTRIGHT
%token SHIFTLEFT
%token MODULO

%type <arg> primary_expression expression expression_additive unary_expression expression_postfixee expression_multiplicative argument_expression_list assignment_expression expression_instruction parameter_declaration parameter_list
%type <t> type
%type <s> function_declarator declarator declarator_list declaration declaration_list
%%

program :  
external_declaration 
| program external_declaration 
;

external_declaration :  
declaration 	// Declaration Global			
| EXTERN declaration // Set Extern attribute			
| function_definition 
;

function_definition :  
type function_declarator decl_glb_fct compound_instruction // generate code function
  
;

decl_glb_fct :
// Get function name - Create a spot to store the function - set attributes
;

declaration :  
type declarator_list ';' {tmp_sym = $2;
			  while(tmp_sym != NULL){
				tmp_sym->type = $1;
				tmp_sym2 = tmp_sym->next;
				add_symbol(tmp_sym, local_table);
				tmp_sym = tmp_sym2;
				}
				$$ = $2;}
;

type :  
INT	{$$ = INTEGER;} 					// set INT
| STRING 	{$$ = STRING;}		// set String
;

declarator_list :  
declarator 	{$$ = $1}			// Propagate code
| declarator_list ',' declarator {tmp_sym = $1;
				while(tmp_sym->next != NULL)
					tmp_sym = tmp_sym->next;
				tmp_sym->next = $3;
				$$ = $1;}	
;

declaration_list :  
declaration 		{$$ = $1;}		// Set locals
| declaration_list declaration  {$$ = $2}	// Set locals
;

declarator :  
IDENT 			{$$ = malloc(sizeof(symbol));
			 $$->id = $1;
			$$->ret_type = VOID;}		// Create Variable
| function_declarator {$$ = $1;}		        // Create Function
;

function_declarator :  
IDENT '(' ')' 			{$$ = malloc(sizeof(symbol));
				$$->id = $1;
				$$->args = NULL;
				$$->type = FUNCTION;}	// Create function name
| IDENT '(' parameter_list ')'  {$$ = malloc(sizeof(symbol));
				$$->id = $1;
				$$->args = $3;
				$$->type = FUNCTION;}	// Create partial function 
;

parameter_list :  
parameter_declaration 	{$$ = $1;}		
| parameter_list ',' parameter_declaration  {tmp = $1;
						while(tmp->next != NULL)
							tmp = tmp->next;
						tmp->next= malloc(sizeof(arg));
						tmp->next->type = $3->type;
						tmp->next->next = NULL;
						$$ = $1;
						}// Insert parameters
;
parameter_declaration :  
type IDENT 			{$$ = malloc(sizeof(arg));
					$$->type = $1;
					$$->id = $2;
					$$->next = NULL;}
						// Type declaration
;

instruction :  
';'  
| compound_instruction {$$=$1;}
| expression_instruction  {$$=$1;}
| iteration_instruction  {$$=$1;}
| select_instruction  {$$=$1;}
| jump_instruction {$$=$1;}
;

expression_instruction :              
expression ';'   {$$ = $1;}
| assignment_expression ';' {$$ = $1;}
;

assignment_expression :  
IDENT assignment expression {printf("assign %s\n", $1); 
				tmp_sym = find_symbol($1, local_table);
				if(tmp_sym->type != $3->type)
					yyerror("conflicting types in assignment expression");
				else{
					tmp_sym->val = $3->val;
					$$ = $3;
				}} 
;

compound_instruction :  
block_start declaration_list instruction_list block_end {$$=$3;}
| block_start declaration_list block_end 
| block_start instruction_list block_end {$$=$2;}
| block_start block_end 
;


block_start :  
'{'  {local_table = create_table(local_table);}// Init your hash table - symbol table
;

block_end :  
'}' {if(local_table == global_table)
		yyerror("No block to close");
	 else local_table = destroy_table(local_table);
	}// Empty hash table
;

instruction_list :  
instruction  {$$=$1;}
| instruction_list instruction 
;

select_instruction :  
cond_instruction instruction 
| cond_instruction instruction ELSE instruction 
;

cond_instruction :  
IF '(' condition ')' {$$=$3;} 
;

iteration_instruction :  
WHILE '(' condition ')' instruction // Handle while loop
| DO instruction WHILE '(' condition ')' 
| FOR '(' assignment ';' condition ';' assignment ')' instruction 
;

jump_instruction:  
RETURN expression ';' 
;

condition :  
expression comparison_operator expression 
;

comparison_operator :  
EGAL  {$$.entier=EGAL;}
| DIFF {$$.entier=DIFF;} 
| INF  {$$.entier=INF;}
| SUP  {$$.entier=SUP;}
| INFEQUAL {$$.entier=INFEQUAL;}
| SUPEQUAL {$$.entier=SUPEQUAL;} 
;

expression :  
expression_additive {$$=$1;}
| expression SHIFTLEFT expression_additive {if($1->type != INTEGER || $3->type != INTEGER)
							 	yerror("left shift requires two integer values")
							else{
								$1->val.i = $1->val.i << $3->val.i;
								$$ = $1;
								free($3);
							}}//  Compute expression
| expression SHIFTRIGHT expression_additive {if($1->type != INTEGER || $3->type != INTEGER)
							 	yerror("right shift requires two integer values")
							else{
								$1->val.i = $1->val.i >> $3->val.i;
								$$ = $1;
								free($3);
							}}// Compute expression
;

expression_additive :  
expression_multiplicative {$$=$1;}
| expression_additive PLUS expression_multiplicative {if($1->type != INTEGER || $3->type != INTEGER)
							 	yerror("addition requires two integer values")
							else{
								$1->val.i = $1->val.i + $3->val.i;
								$$ = $1;
								free($3);
							}}// Compute expression
| expression_additive MINUS expression_multiplicative {if($1->type != INTEGER || $3->type != INTEGER)
							 	yerror("minus requires two integer values")
							else{
								$1->val.i = $1->val.i - $3->val.i;
								$$ = $1;
								free($3);
							}}// Compute expression
;

expression_multiplicative :  
unary_expression{$$=$1;}
| expression_multiplicative MULTI unary_expression {if($1->type != INTEGER || $3->type != INTEGER)
							 	yerror("mult requires two integer values")
							else{
								$1->val.i = $1->val.i * $3->val.i;
								$$ = $1;
								free($3);
							}}
| expression_multiplicative DIV unary_expression	{if($1->type != INTEGER || $3->type != INTEGER)
							 	yerror("div requires two integer values")
							else{
								$1->val.i = $1->val.i / $3->val.i;
								$$ = $1;
								free($3);
							}}
| expression_multiplicative MODULO unary_expression	{if($1->type != INTEGER || $3->type != INTEGER)
							 	yerror("modulo requires two integer values")
							else{
								$1->val.i = $1->val.i % $3->val.i;
								$$ = $1;
								free($3);
							}}
								
;

unary_expression:  
expression_postfixee {$$=$1;}
| MINUS unary_expression {$$=$2;
			$$->val.i = 0 - $$->val.i;}
;

expression_postfixee :  
primary_expression {$$=$1;}
| IDENT '(' argument_expression_list')' {$$ = $3}//insert "function call" function -> takes function symbol, list of args, returns pointer to arg list
| IDENT '(' ')' 			{$$ = NULL;}//same as above
;

argument_expression_list:  
expression {$$ = $1;}
| argument_expression_list ',' expression {tmp = $1;
			 while(tmp->next != NULL)
				tmp = tmp->next;
			tmp->next= $3;
				$$ = $1;}
;

primary_expression :  
IDENT  {tmp_sym = find_symbol($1, local_table);
	$$ = malloc(sizeof(arg));
	$$->type = tmp_sym->type;
	$$->val = tmp_sym->val;
	$$->next = NULL; }
| CONST_INT	{$$ = malloc(sizeof(arg));
		$$->type = INTEGER;
		$$->val.i  = $1;
		$$->next = NULL;}
| CONST_STRING {$$ = malloc(sizeof(arg));
		$$->type = STRING;
		$$->val.str = $1;
		$$->next = NULL}
| '(' expression ')'	{$$ = $2;}
;

%%

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

symbol *find_symbol(char *sym, sym_table *t){
	symbol *track;
	
	int i = hash_sym(symb);
	
	while(t != NULL){
		track = t->table[i];
		while(track != NULL){
			if(!strcmp(track->sym, symb))
				return track;
			else track = track->next;
		}
		t = t->prev;
	}
	return NULL;

}


void print_sym(char *symb, symbol **table){

	sym_def *track = table[hash_sym(symb)];
	arg *argument;

	while(track != NULL){
		if(!strcmp(track->sym, symb)){
			printf("Function: %s\nType: %s\n", track->sym, track->type);
			printf("Arguments: ");
			argument = track->alist;
			while(argument != NULL){
				printf("%s (%s) ",argument->id, argument->type);
				argument = argument->next; 
			}
			printf("\n");
			return;
		}
		else track = track->next;
	}
	return;


}



symbol *add_symbol(symbol *symb, symbol **table){

	int i = hash_sym(symb->id);
	symbol *track = table[i];

	arg *in_test = symb->alist; 
	arg *existing_test;

	if(track == NULL){
		table[i] = symb;
		table[i]->next = NULL;
		return table[i];

	}

	while(track->next != NULL){
		if(!strcmp(track->id, symb->id)){
			if(symb->type != track->type || symb->ret_type != track->ret_type){
				yyerror("Conflicting definitions");
				return NULL;
			}
			existing_test = track->alist;
			while(existing_test != NULL && in_test != NULL){
			 if(existing_test->type !=  in_test->type) || existing_test == NULL || in_test == NULL)
				yyerror("Conflicting function definitions");
				return NULL;
			}
			track->alist = symb->alist;
			free(symb);
			return track;
		}
		else track = track->next;
	}

	if(!strcmp(track->id, symb->id)){
			if(symb->type != track->type || symb->ret_type != track->ret_type){
				yyerror("Conflicting definitions");
				return NULL;
			}
			existing_test = track->alist;
			while(existing_test != NULL && in_test != NULL){
			 if(existing_test->type !=  in_test->type) || existing_test == NULL || in_test == NULL)
				yyerror("Conflicting function definitions");
				return NULL;
			}
			track->alist = symb->alist;
			free(symb);
			return track;
	}

	else{

		track->next = symb; 
		track->next->next = NULL;
		return track->next; 


	}
	return NULL;


}


sym_table *create_table(sym_table *loc){
	if(loc->next != NULL){
		yyerror("Creating table in middle of list");
		return NULL;
	}
	
	loc->next = malloc(sizeof(sym_table));
	loc->next->table = malloc(sizeof(sym_table *)*TABLESIZE);
	loc->next->prev = loc;
	loc->next->next = NULL;
	return loc->next;

}

sym_table *destroy_table(sym_table *loc){
	arg *a_track, *a_next;
	symbol *s_track, *s_next;
	
	sym_table *ret = loc->prev;
	
	int i;
	for(i = 0; i < TABLESIZE; ++i){
		s_track = loc->table[i];
		while(s_track != NULL){
			a_track = s_track->args;
			while(a_track != NULL){
				a_next = a_track->next;
				free(a_track);
				a_track = a_next;
			}
			s_next = s_track->next;
			free(s_track);
			s_track = s_next;
		}
	}
	
	free(loc->table);
	free(loc);
	return ret;
	
}



}

