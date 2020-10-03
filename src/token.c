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
