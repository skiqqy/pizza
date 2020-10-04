/* @Author Stephen Cochrane
 * @License GPL
 * 
 * Token type for the pizza project.
 */

#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "err.h"

static char *tok_names[] = {
	"end-of-file",
	"identifier",
	"const-integer",
	"const-float",
	"const-string",
	"label",
	"token: {",
	"tolen: }",
	"DEBUG: OPP_UPPER",
	"cmp",
	"jg",
	"jl",
	"jeq",
	"push",
	"pop",
	"put",
	"add",
	"imul",
	"idiv",
	"fmul",
	"DEBUG: OPP_LOWER",
	"flush",
	"malloc",
};


const char *
tok_string(Token *token)
{
	int type = token->type;

	if ((type < 0) || type >= sizeof(tok_names)/sizeof(char *)) {
		pcerror("Unknown token type. tok_string(...)");
	}

	return tok_names[type];
}

/* @brief: Check if a token is an opcode
 * @param token: The token to check.
 * @return 1: the token is an opcode
 * @return 0: the token is not an opcode
 */
int
is_opcode(Token *token)
{
	if (token->type > OPP_UPPER && token->type < OPP_LOWER) {
		return 1;
	}
	return 0;
}
