%{
	#include<stdio.h>
	#include<string.h>
	#include "symbol.h"
	#define TABLESIZE 100



int yywrap(){
	return 1;
}

void yyerror(const char *str){
	fprintf(stderr, "error: %s\n",str);

}

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
	INFE,
	EGA,
	SU,
	INFEQUA,
	SUPEQUA,
	DIF
 } entier;
 struct symbol_ *s;
}
%token <t> INT
%token <t> STRING
%token <fn> CONST_INT
%token <a> CONST_STRING IDENT 


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

%type <g> primary_expression expression expression_additive unary_expression expression_postfixee expression_multiplicative argument_expression_list assignment_expression parameter_declaration parameter_list
%type <t> type
%type <s> function_declarator declarator declarator_list declaration declaration_list
%type <a> function_definition instruction  compound_instruction expression_instruction iteration_instruction select_instruction jump_instruction condition instruction_list cond_instruction
%type <entier> comparison_operator
%%

program :  
external_declaration 
| program external_declaration 
;

external_declaration :  
declaration 	// Declaration Global			
| EXTERN declaration {printf(" as extern\n");}// Set Extern attribute			
| function_definition 
;

function_definition :  
type function_declarator compound_instruction {$$ = $3; local_table->func = NULL;
						$2->ret_type = $1;
						add_symbol($2, local_table->table);	
						}// generate code function
  
;


declaration :  
type declarator_list ';' {tmp_sym = $2;
			  while(tmp_sym != NULL){
				if(tmp_sym->type == FUNCTION){
				 tmp_sym->ret_type = $1;
				 local_table->func = NULL;
				}
				else{
					if(tmp_sym->type != VOID && tmp_sym->type != $1){
						yyerror("conflicting type for declaration and assignment");
						return -1;
					}
					printf("declare symbol %s of type %s\n", tmp_sym->id, print_type($1));
					tmp_sym->type = $1;
				}
				tmp_sym2 = tmp_sym->next;
				if(add_symbol(tmp_sym, local_table->table) == NULL)
					return -1;
				tmp_sym = tmp_sym2;
				}
				$$ = $2;}
;

type :  
INT	{$$ = INTEG;} 					// set INT
| STRING 	{$$ = STRIN;}		// set String
;

declarator_list :  
declarator 	{$$ = $1;}			// Propagate code
| declarator_list ',' declarator {tmp_sym = $1;
				while(tmp_sym->next != NULL)
					tmp_sym = tmp_sym->next;
				tmp_sym->next = $3;
				$$ = $1;}	
;

declaration_list :  
declaration 		{$$ = $1;}		// Set locals
| declaration_list declaration  {$$ = $2;}	// Set locals
;

declarator :  
IDENT 			{$$ = malloc(sizeof(symbol));
			 strcpy($$->id, $1);
			$$->type = VOID;}		// Create Variable
| IDENT assignment expression {$$ = malloc(sizeof(symbol));
			 strcpy($$->id, $1);
			$$->type = $3->type;
			$$->val = $3->val;}	
| function_declarator {$$ = $1;}		        // Create Function
;

function_declarator :  
IDENT '(' ')' 			{printf("function declaration: %s\n", $1);
				$$ = malloc(sizeof(symbol));
				strcpy($$->id, $1);
				$$->alist = NULL;
				$$->type = FUNCTION;
				local_table->func = $$;}	// Create function name
| IDENT '(' parameter_list ')'  {printf("function declaration: %s\n", $1);
				$$ = malloc(sizeof(symbol));
				strcpy($$->id, $1);
				$$->alist = $3;
				$$->type = FUNCTION;
				local_table->func = $$;}	// Create partial function 
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
					strcpy($$->id, $2);
					$$->next = NULL;}
						// Type declaration
;

instruction :  
';' {$$ = "";} 
| compound_instruction {$$=$1;}
| expression_instruction  {$$=$1;}
| iteration_instruction  {$$=$1;}
| select_instruction  {$$=$1;}
| jump_instruction {$$=$1;}
;

expression_instruction :              
expression ';'   {$$ = $1->val.str;printf("%s\n", $1->id);}
| assignment_expression ';' {$$ = $1->val.str;
				printf("%s\n", $1->id);}
;

assignment_expression :  
IDENT assignment expression { 
				tmp_sym = find_symbol($1, local_table);
				if(tmp_sym == NULL){
					yyerror("symbol not found");
					return -1;
				}
				if(tmp_sym->type != $3->type){
					yyerror("conflicting types in assignment expression");
					return -1;
				}
				else{
					char *s = strdup($3->id);
					snprintf($3->id, 100, "assign to %s %s", tmp_sym->id, s);
					$$ = $3;
				}} 
;

compound_instruction :  
block_start declaration_list instruction_list block_end {$$=$3;}
| block_start declaration_list block_end {$$ = $2->id;} 
| block_start instruction_list block_end {$$=$2;}
| block_start block_end {$$ = "";} 
;


block_start :  
'{'  {local_table = create_table(local_table);}// Init your hash table - symbol table
;

block_end :  
'}' {if(local_table == global_table){
		yyerror("No block to close");
		return -1;
	}
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
WHILE '(' condition ')' instruction {printf("while loop\n");}// Handle while loop
| DO instruction WHILE '(' condition ')'  {printf("do/while loop\n");}
| FOR '(' assignment_expression ';' condition ';' assignment_expression ')' instruction  {printf("for loop with %s as iterator\n", $3->id);} 
;

jump_instruction:  
RETURN expression ';' {printf("return %s\n", $2->id);}
;

condition :  
expression comparison_operator expression {$$ = $1->id;}
;

comparison_operator :  
EGAL  {$$=EGA;}
| DIFF {$$=DIF;} 
| INF  {$$=INFE;}
| SUP  {$$=SU;}
| INFEQUAL {$$=INFEQUA;}
| SUPEQUAL {$$=SUPEQUA;} 
;

expression :  
expression_additive {$$=$1;}
| expression SHIFTLEFT expression_additive {if($1->type != INTEG || $3->type != INTEG){
							 	yyerror("left shift requires two integer values");
								return -1;
							}
							else{
								strcat($1->id, " shift left  by ");
								strcat($1->id, $3->id);
								$$ = $1;
								free($3);
							}}//  Compute expression
| expression SHIFTRIGHT expression_additive {if($1->type != INTEG || $3->type != INTEG){
							 	yyerror("right shift requires two integer values");
								return -1;
							}
							else{
								strcat($1->id, " shift right by ");
								strcat($1->id, $3->id);
								$$ = $1;
								free($3);
							}}// Compute expression
;

expression_additive :  
expression_multiplicative {$$=$1;}
| expression_additive PLUS expression_multiplicative {if($1->type != INTEG || $3->type != INTEG){
							 	yyerror("addition requires two integer values");
								return -1;
							}
							else{
								strcat($1->id, " plus ");
								strcat($1->id, $3->id);
								$$ = $1;
								free($3);
							}}// Compute expression
| expression_additive MINUS expression_multiplicative {if($1->type != INTEG || $3->type != INTEG){
							 	yyerror("minus requires two integer values");
								return -1;
							}
							else{
								strcat($1->id, " minus ");
								strcat($1->id, $3->id);

								$$ = $1;
								free($3);
							}}// Compute expression
;

expression_multiplicative :  
unary_expression{$$=$1;}
| expression_multiplicative MULTI unary_expression {if($1->type != INTEG || $3->type != INTEG){
							 	yyerror("mult requires two integer values");
								return -1;
							}
							else{
								strcat($1->id, " mult ");
								strcat($1->id, $3->id);
								$$ = $1;
								free($3);
							}}
| expression_multiplicative DIV unary_expression	{if($1->type != INTEG || $3->type != INTEG){
							 	yyerror("div requires two integer values");
								return -1;
							}
							else{
								strcat($1->id, " div ");
								strcat($1->id, $3->id);
								$$ = $1;
								free($3);
							}}
| expression_multiplicative MODULO unary_expression	{if($1->type != INTEG || $3->type != INTEG){
							 	yyerror("modulo requires two integer values");
								return -1;
							}
							else{
								strcat($1->id, " modulo ");
								strcat($1->id, $3->id);
								$$ = $1;
								free($3);
							}}
								
;

unary_expression:  
expression_postfixee {$$=$1;}
| MINUS unary_expression {$$=$2;char *s = strdup($$->id);
			snprintf($$->id, 100, "negative %s", s);}
;

expression_postfixee :  
primary_expression {$$=$1;}
| IDENT '(' argument_expression_list')' {
					arg *existing_test, *in_test;
					 tmp_sym = find_symbol($1, local_table);
					if(tmp_sym == NULL){
					 yyerror("function not declared");
					 return -1;
					}
					existing_test = tmp_sym->alist;
					in_test = $3;
					while(existing_test != NULL || in_test != NULL){
			 			if(existing_test == NULL || in_test == NULL || existing_test->type !=  in_test->type ){
							yyerror("function parameters do not match declaration");
							return -1;
						}
						existing_test = existing_test->next; in_test = in_test->next;
					}
					 tmp_sym->alist = $3;
					$$ = malloc(sizeof(arg));
					snprintf($$->id, 100, "function %s with args", $1);
					tmp = $3;
					while(tmp != NULL){
						strcat($$->id, " ");
						strcat($$->id, tmp->id);
						tmp = tmp->next;
					}}//insert "function call" function -> takes function symbol, list of args, returns pointer to arg list
| IDENT '(' ')' 			{tmp_sym = malloc(sizeof(symbol));
					 tmp_sym = add_symbol(tmp_sym, local_table->table);
					$$ = malloc(sizeof(arg));
					snprintf($$->id, 100, "function %s", $1);}//same as above
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
IDENT  {
	tmp_sym = find_symbol($1, local_table);
	if(tmp_sym == NULL){
		yyerror("symbol not found");
		return -1;
	}
	$$ = malloc(sizeof(arg));
	$$->type = tmp_sym->type;
	strcpy($$->id, tmp_sym->id);
	$$->next = NULL; }
| CONST_INT	{
		$$ = malloc(sizeof(arg));
		$$->type = INTEG;
		strcpy($$->id, "const");
		$$->next = NULL;}
| CONST_STRING {$$ = malloc(sizeof(arg));
		$$->type = STRIN;
		strcpy($$->id, "const");
		$$->next = NULL;}
| '(' expression ')'	{$$ = $2;}
;

%%

int main(void) {

	global_table = malloc(sizeof(sym_table));
	global_table->table = malloc(sizeof(symbol *)*TABLESIZE);
	global_table->prev = NULL;
	global_table->next = NULL;
	global_table->func = NULL;

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
	sym_table *ti = t;
	
	int i = hash_sym(sym);
	
	while(ti != NULL){
		track = ti->table[i];
		while(track != NULL){
			if(!strcmp(track->id, sym))
				return track;
			else track = track->next;
		}
		ti = ti->prev;
	}
	return NULL;

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
			while(existing_test != NULL || in_test != NULL){
			 if(existing_test == NULL || in_test == NULL || existing_test->type !=  in_test->type ){
				yyerror("Conflicting function definitions");
				return NULL;
			 }
			 existing_test = existing_test->next; in_test = in_test->next;
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
			while(existing_test != NULL || in_test != NULL){
			 if(existing_test == NULL || in_test == NULL || existing_test->type !=  in_test->type ){
				yyerror("Conflicting function definitions");
				return NULL;
			 }
			 existing_test = existing_test->next; in_test = in_test->next;
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
	
	arg* a;
	symbol *s;
	if(loc->next != NULL){
		yyerror("Creating table in middle of list");
		return NULL;
	}
	
	loc->next = malloc(sizeof(sym_table));
	loc->next->table = malloc(sizeof(sym_table *)*TABLESIZE);
	loc->next->prev = loc;
	loc->next->next = NULL;
	if(loc->func != NULL){
		a = loc->func->alist;
		while(a != NULL){
		  s = malloc(sizeof(symbol));
		  s->type = a->type;
		  strcpy(s->id, a->id);
		  s = add_symbol(s, loc->next->table);
		  a = a->next;
		}

	}
	loc->next->func = loc->func;
	return loc->next;

}

sym_table *destroy_table(sym_table *loc){
	
	printf("destroying table: \n");
	print_table(loc);
	arg *a_track, *a_next;
	symbol *s_track, *s_next;
	
	sym_table *ret = loc->prev;
	
	int i;
	for(i = 0; i < TABLESIZE; ++i){
		s_track = loc->table[i];
		while(s_track != NULL){
			a_track = s_track->alist;
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
