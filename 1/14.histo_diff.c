#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word*/

int main() {
    int c, i;
    int state = OUT;

    int letters[26];
    for (i = 0; i < 26; i++)
        letters[i] = 0;

    while ((c = getchar()) != EOF)
        if (c >= 'a' && c <= 'z')
            letters[c - 'a']++;

    for (i = 0; i < 26; i++) {
        if (letters[i] == 0)
            continue;

        printf("%c:%d\t", i + 'a', letters[i]);
        for (int j = 0; j < letters[i]; j++)
            printf("■");
        printf("\n");
    }
}
