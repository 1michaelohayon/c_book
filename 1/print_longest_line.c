#include <stdio.h>
#define MAXLINE 26 /* maximum input line size */

int getlinex(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main() {
    int max;               /* maximum line length */
    int len;               /* current line length */
    char line[MAXLINE];    /* current input line */
    char longest[MAXLINE]; /* longest line */

    max = 0;
    while ((len = getlinex(line, MAXLINE)) > 0) {

        if (line[len - 1] != '\n') {
            int c;
            while ((c = getchar()) != EOF && c != '\n')
                len++;
        }
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    if (max > 0) /* there was a line */
        printf("\n%d\t%s\n", max - 1, longest);

    return 0;
}

/* getline: read a line into s, return length */
int getlinex(char s[], int lim) {
    int i, c;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[]) {
    int i = 0;

    while ((to[i] = from[i]) != '\0')
        i++;
}
