/* @Author Stephen Cochrane
 * @License GPL
 * 
 * Token type for the pizza project.
 */

#define ID_LEN_MAX 32

typedef enum {
	TOKEN_EOF,         /* EOF Token */
	TOKEN_ID,          /* Identifier Token */
	TOKEN_INT,         /* Int literal */
	TOKEN_FLOAT,       /* Float literal */
	TOKEN_STRING,      /* String Literal */
	TOKEN_LABEL,       /* Label Token */

	TOKEN_COPEN,       /* { */
	TOKEN_CCLOSE,      /* } */

	OPP_UPPER,
	/* opcodes start */
	TOKEN_CMP,
	TOKEN_JG,
	TOKEN_JL,
	TOKEN_JEQ,
	TOKEN_PUSH,
	TOKEN_POP,
	TOKEN_PUT,
	TOKEN_ADD,
	TOKEN_IMUL,
	TOKEN_IDIV,
	TOKEN_FMUL,
	/* opcodes end */
	OPP_LOWER,

	/* "sys" opcodes */
	TOKEN_FLUSH,
	TOKEN_MALLOC,
} TokenType;

typedef struct {
	TokenType type;
	union {
		int val_int;                  /* The value (if type int) */
		float val_float;              /* The value (if type float) */
		char lexeme[ID_LEN_MAX + 1];  /* The lexeme of the identifier */
		char *string;                 /* The string (for type string) */
	};
} Token;
