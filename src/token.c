/* @Author Stephen Cochrane
 * @License GPL
 * 
 * Token type for the pizza project.
 */

#include <stdlib.h>
#include <stdio.h>

#include "token.h"

/* @brief: Check if a token is an opcode
 * @param token: The token to check.
 * @return 1: the token is an opcode
 */
int
is_opcode(Token *token)
{
	if (token->type == TOKEN_ADD ||
		token->type == TOKEN_CMP ||
		token->type == TOKEN_FLUSH ||
		token->type == TOKEN_FMUL ||
		token->type == TOKEN_IDIV ||
		token->type == TOKEN_IMUL ||
		token->type == TOKEN_JEQ ||
		token->type == TOKEN_JG ||
		token->type == TOKEN_JL ||
		token->type == TOKEN_MALLOC ||
		token->type == TOKEN_POP ||
		token->type == TOKEN_PUSH ||
		token->type == TOKEN_PUT ) {
		return 1;
	}
	return 0;
}
