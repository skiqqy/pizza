/* @Author Stephen Cochrane
 * @License GPL
 * 
 * Scanner for the pizza project.
 */
#include <stdlib.h>
#include <stdio.h>

#include "scanner.h"

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
	// TODO: Get the next char, and inc line and colm nr where needed.
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
proess_word(Token *token)
{
	// TODO: Process a word, and construct the token.
}

void
get_token(Token *token)
{
	// TODO: Construct the token, by reading source and retrieving the next token.
}
