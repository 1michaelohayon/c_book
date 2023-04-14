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
    char newline = '\n';

    while (isspace(c = getch()))
        if (c == '\n') {
            word[0] = '\n';
            word[1] = '\0';
            return c;
        }

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = c = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}
