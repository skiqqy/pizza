/* @Author Stephen Cochrane
 * @License GPL
 * 
 * Scanner for the pizza project.
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "scanner.h"
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

static void
next_ch()
{
	ch = getc(source);
	if (ch != '\n') {
		printf("Current char = %c\n", ch);
	}

	if (ch == '\n') {
		clm = 0;
		row++;
	}

	clm++;
}

static void
process_number(Token *token)
{
	// TODO: Construct a number token.
}

static void
process_string(Token *token)
{
	// TODO: Construct a string literal token.
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
			// TODO: Parse word
			process_word(token);
		} else if (isdigit(ch)) {
			// TODO: Parse int/float
		} else {
			switch (ch) {
				case '#':
					// TODO: parse comment.
					break;
				case '"':
					// TODO: Parse a string.
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

	next_ch();
}
