#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word*/

int main() {
    int c;
    int state = OUT;
    int wordLen = 0;
    int string[1000];

    while ((c = getchar()) != EOF)
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
            printf(" %d\t", wordLen);
            for (int i = 0; i < wordLen; i++)
                printf("%c", string[i]);
            printf("\t\t");
            while (wordLen-- > 0)
                printf("■");
            wordLen = 0;
            printf("\n");
        } else {
            state = IN;
            string[wordLen] = c;
            wordLen++;
        }
}
