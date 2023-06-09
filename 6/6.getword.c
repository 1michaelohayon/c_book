#include <ctype.h>
#include <stdio.h>
#include <string.h>

int getch(void);
void ungetch(int);

/* get next word  or character from input  */
int getword(char *word, int lim) {
    int c, d, comment(void), getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        if (c == '\n') {
            word[0] = '\n';
            word[1] = '\0';
            return c;
        }
    if (c != EOF)
        *w++ = c;

    if (isalpha(c) || c == '_' || c == '#') {

        for (; --lim; w++)
            if (!isalnum(*w = getch()) && *w != '_') {
                ungetch(*w);
                break;
            }

    } else if (c == '\'' || c == '"') {
        for (; lim; w++) {
            if ((*w = getch()) == '\\')
                *++w = getch();
            else if (*w == c) {
                w++;
                break;
            } else if (*w == EOF)
                break;
        }
    } else if (c == '/') {
        if ((d = getch()) == '*') {
            c = comment();
        } else
            ungetch(d);
    } else if (isdigit(c)) {
        for (; --lim; w++)
            if (!isdigit(*w = getch()) && *w != '_') {
                ungetch(*w);
                break;
            }
    }

    *w = '\0';
    return c;
}

int comment(void) {
    int c;
    while ((c = getch()) != EOF)
        if (c == '*') {

            if ((c = getch()) == '/')
                break;
            else
                ungetch(c);
        }
    return c;
}