/* @Author Stephen Cochrane
 * @License GPL
 * 
 * Scanner for the pizza project.
 */
#include <stdlib.h>
#include <stdio.h>

#include "scanner.h"

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
