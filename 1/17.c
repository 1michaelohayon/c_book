#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000
#define MAXLINES 100
#define LONGLINE 80

char line[MAXLINE];
char lines[MAXLINES][MAXLINES];
int len = 0;
int i = 0;

int getlinex(char line[], int maxline);

int main() {
    while ((len = getlinex(line, MAXLINE)) > 0) {
        if (len > LONGLINE)
            printf("%s", line);
    }

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
