#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word*/

/* count lines, words, and chars in input */

int main() {
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
            if (c == '\n')
                nl++;
        } else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("\vl w c\n");
    printf("%d %d %d\n", nl, nw, nc);
}

// how would u test: