#include <stdio.h>
#include <string.h>

/* prints the rightmost occurnce of a pttern, t, in a string, s.*/
int strindex(char s[], char t[]) {
    int i, j, k;
    for (i = strlen(s) - strlen(t); s[i] != '\0'; i--) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

int main() {
    char s[] = "hellol worldlolzxaq2";
    char t[] = "lol";

    printf("%d\n", strindex(s, t));
    return 0;
}
