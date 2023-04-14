#include <stdio.h>
/* counts lines in input */
int main() {

    int c, n = 0, t = 0, b = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n')
            n++;
        else if (c == '\t')
            t++;
        else if (c == ' ')
            b++;

        printf("' ' %d, \\t %d, \\n %d\n", b, t, n);
    }
}
