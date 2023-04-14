#include <stdio.h>

/*at most n */

void strcpyx(char *s, char *t, int n) {
    while (n-- && (*s++ = *t++))
        ;
}
void strcatx(char *s, char *t, int n) {
    while (*s)
        s++;
    strcpyx(s, t, n);
}

int strcmpx(char *s, char *t, int n) {
    for (; n-- && *s == *t; s++, t++)
        if (!*s || (!n && *s == *t))
            return 0;
    return *s - *t;
}

int main() {
    char s[15];
    char *t = "hello world";
    strcpyx(s, t, 7);

    printf("%s : %s\n", s, t);

    printf("strcmp: %d\n", strcmpx(s, t, 5));

    char *t2 = "orldasf43g3f";
    strcatx(s, t2, 4);
    printf("%s\n", s);
}