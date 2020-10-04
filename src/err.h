/* @Author Stephen Cochrane
 * @License GPL
 * 
 * error handling the pizza project.
 */

typedef struct {
	int r; /* Row */
	int c; /* Column */
} Pos;

void pfcerror(const char *fmt, ...);
void pcerror(const char *fmt, ...);
void pfwerror(const char *fmt, ...);
