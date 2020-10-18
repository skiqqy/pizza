/* @Author Stephen Cochrane
 * @License GPL
 * 
 * Scanner for the pizza project.
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "lexer.h"
#include "err.h"

typedef struct {
	char *word;
	TokenType type;
} ResWord;

static ResWord reserved[] = {
	/* Word must be in alpha order, so we can do a binary search */
	{"add", TOKEN_ADD},
	{"cmp", TOKEN_CMP},
	{"flush", TOKEN_FLUSH},
	{"fmul", TOKEN_FMUL},
	{"idiv", TOKEN_IDIV},
	{"imul", TOKEN_IMUL},
	{"jeq", TOKEN_JEQ},
	{"jg", TOKEN_JG},
	{"jl", TOKEN_JL},
	{"malloc", TOKEN_MALLOC},
	{"pop", TOKEN_POP},
	{"push", TOKEN_PUSH},
	{"put", TOKEN_PUT},
};

#define NUM_RESV sizeof(reserved)/sizeof(ResWord)

static FILE *source;
static int ch;  /* current char */
static int clm; /* column number */
static int row; /* row number */

/* @brief: set ch to the next char in source
 * @return: void
 */
static void next_ch();

/* @brief: process a number, and set the token appropriatly
 * @return: void
 * @param token: The token to update
 */
static void process_number(Token *token);

/* @brief: process a string, and set the token appropriatly 
 * @return: void
 * @param token: The token to update
 */
static void process_string(Token *token);

/* @brief: process a word, if it is unique we then specify the token type, else
 * it is an identifier
 * @return: void
 * @param token: The token to update
 */
static void process_word(Token *token);

static void process_comment();

static double get_rem();

static void
next_ch()
{
	ch = getc(source);

	if (ch == '\n') {
		clm = 0;
		row++;
	}

	clm++;
}

static double
get_rem() {
	double rem = 0;
	int i = 1;
	double index = 0.1;

	while (isdigit(ch)) {
		// TODO: Make sure no undeflow occurs
		rem += (ch - '0')*pow(index, i++);
		next_ch();
	}

	return rem;
}

static void
process_number(Token *token)
{
	// Construct a number token.
	int val = ch - '0'; // COnv to int
	double rem = 0;
	
	next_ch();
	while (isdigit(ch) || ch == '.') {
		if (ch == '.') {
			if (rem != 0) {
				// The next token is a label.
				return;
			}

			next_ch();
			rem = get_rem();
			break;
		} else {
			// TODO: Ensure that this doesnt overflow.
			val = val*10 + (ch - '0');
		}
		next_ch();
	}

	if (rem == 0) {
		token->type =  TOKEN_INT;
		token->val_int = val;
	} else {
		token->type = TOKEN_DOUBLE;
		token->val_double = val + rem;
	}
}

static void
process_string(Token *token)
{
	// Construct a string literal token.
	char *buff;
	int size = 1024, i = 0;
	buff = malloc(sizeof(char)*size);
	next_ch();

	while (ch != '"') {
		if (i >= size) {
			/* We must recize the buffer */
			size *= 2;
			buff = realloc(buff, sizeof(char)*size);
		}

		switch (ch) {
			case EOF:
				pcerror("Unclosed string literal");
				break;
			case '\\':
				next_ch();
				switch (ch) {
					case '\\':
						buff[i] = '\\';
						break;
					case 't':
						buff[i] = '\t';
						break;
					case 'n':
						buff[i] = '\n';
						break;
					case '"':
						buff[i] = '"';
						break;
					default:
						pcerror("Invalid escape sequence");
						break;
				}
				break;
			default:
				if (isprint(ch)) {
					buff[i] = ch;
				} else {
					pcerror("Non-printable char in string literal");
				}
				break;
		}
		next_ch();
		i++;
	}
	next_ch();

	buff[i] = 0;
	token->type = TOKEN_STRING;
	token->string = buff;
}

static void
process_word(Token *token)
{
	/* Process a word, and construct the token. */
	int i = 0, low, high, cmp, mid;
	char lex[ID_LEN_MAX + 1];

	while ( (i <= ID_LEN_MAX) && (isalpha(ch) || isdigit(ch)) ) {
		lex[i++] = ch;
		next_ch();
	}
	lex[i] = 0;

	if ( i >= ID_LEN_MAX + 1) {
		pcerror("Identifier too long.");
	}

	high = NUM_RESV;
	low = 0;
	do {
		mid = (high + low)/2;
		cmp = strcmp(lex, reserved[mid].word);
		if (cmp < 0) {
			high = mid - 1;
		} else if (cmp > 0) {
			low = mid + 1;
		} else {
			i = mid;
			break;
		}
	} while (low <= high);

	/* Check to see if it is an opcode */
	if (!cmp) {
		token->type = reserved[i].type;
		strcpy(token->lexeme, lex);
		return;
	}

	token->type = TOKEN_ID;
	strcpy(token->lexeme, lex);
}

void
process_comment()
{
	while (ch != '\n') next_ch();
}

void
init_scanner(FILE *file)
{
	// TODO: Finish init func.
	clm = 0;
	row = 1;
	source = file;
	next_ch();
}

void
fetch_token(Token *token)
{
	// TODO: Construct the token, by reading source and retrieving the next token.
	while (isspace(ch)) next_ch();

	if (ch != EOF) {
		if (isalpha(ch)) {
			// Parse word
			process_word(token);
		} else if (isdigit(ch)) {
			// Parse int/float
			process_number(token);
		} else {
			switch (ch) {
				case '#':
					/* parse comment. */
					process_comment();
					next_ch();
					fetch_token(token);
					break;
				case '"':
					process_string(token);
					break;
				case '.':
					// TODO: Parse a label.
					break;
				case '{':
					token->type = TOKEN_COPEN;
					next_ch();
					break;
				case '}':
					token->type = TOKEN_CCLOSE;
					next_ch();
					break;
			}
		}
	} else {
		token->type = TOKEN_EOF;
	}
}
