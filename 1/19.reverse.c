

#include <stdio.h>
#define MAXLINE 1000

int getlinex(char line[], int maxline);
void reverse(char line[], int length);

int main() {
    char line[MAXLINE];
    int len = 0;

    while ((len = getlinex(line, MAXLINE)) > 0) {
        while (line[len - 2] == ' ' || line[len - 2] == '\t') {
            line[len - 2] = '\0';
            len--;
        }
        reverse(line, len - 1);
        if (len > 1)
            printf("%d: %s\n", len - 1, line);
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

/* reverse input string*/
void reverse(char str[], int len) {
    for (int i = 0, j = len; i < j; i++, j--) {
        int tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}