int yywrap();

void yyerror(const char *str);

enum type_ {
	INTEG,
	STRIN,
	FUNCTION,
	VOID
} ;

typedef struct arg_{
	char id[100];
	enum type_ type;
	union element{
		char *str;
		int i;
	} val;
	struct arg_ *next;
} arg;


typedef struct symbol_{
	char id[100];
	enum type_ type;
	enum type_ ret_type;
	arg* alist;
	union element val;
	struct symbol_ *next;
} symbol;

typedef struct sym_table_ {
	symbol **table;
	struct sym_table_ *prev;
	struct sym_table_ *next;
	symbol *func;
} sym_table;

int hash_sym(char *sym);
symbol *find_symbol(char *sym, sym_table *t);
void print_sym(char *sym, symbol **table);
symbol *add_symbol(symbol *symb, symbol **table);
char *print_type(enum type_ t);

void print_table(sym_table *t);

sym_table *create_table(sym_table *loc);
sym_table *destroy_table(sym_table *loc);
