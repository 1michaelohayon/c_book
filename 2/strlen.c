#include <stdio.h>

int strlenx(const char s[]) {
    int i = 0;
    while (s[i] != '\0')
        ++i;
    return i;
}

int main() {
    char str[] = "michael";

    int len = strlenx(str);

    printf("%d\n", len);
}