#include <stdlib.h>
#include <stdio.h>

#include "scanner.h"

void
usage()
{
	printf("./testscanner /path/to/file\n");
	exit(1);
}

void
p_token(Token *token)
{
	switch (token->type) {
		case TOKEN_ID:
			printf("Identifier: %s\n", token->lexeme);
			break;
		case TOKEN_INT:
			printf("Int: %d\n", token->val_int);
			break;
		case TOKEN_FLOAT:
			printf("Float: %f\n", token->val_float);
			break;
		case TOKEN_STRING:
			printf("String: \"%s\"\n", token->string);
			break;
		case TOKEN_LABEL:
			printf("Label: %s\n", token->lexeme);
			break;
		default:
			if (is_opcode(token)) {
				printf("Opcode: %s\n", token->lexeme);
			} else {
				printf("Unknown token type.\n");
			}
			break;
	}
}

int
main(int argc, char *argv[])
{
	/* TODO: Write test code for the scanner. */
	Token token;
	FILE *file;

	if (argc < 2) {
		usage();
	}

	file = fopen(argv[1], "r");

	init_scanner(file);
	fetch_token(&token);

	while (token.type != TOKEN_EOF) {
		p_token(&token);
		fetch_token(&token);
	}
	
	return EXIT_SUCCESS;
}
