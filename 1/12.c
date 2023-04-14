#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word*/

int main() {
    int state = OUT;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n')
            putchar('\n');
        else
            putchar(c);
    }
}