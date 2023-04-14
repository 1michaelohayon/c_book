#include <stdio.h>
#include <string.h>
#define YES 1
#define NO 0
#define abs(x) ((x) < 0 ? -(x) : (x))

void reverse(char s[]) {
    for (int i = 0, j = strlen(s) - 1; i < j; j--, i++) {
        int c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
/*itoav2 convert n to s*/
void itoa(int n, char s[]) {
    int i, sign;
    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main() {
    char s[100];
    itoa(-2147483648, s);
    printf("%s\n", s);
    return 0;
}

/*itoa convert n to s first attempt but also works*/
void itoa_old(int n, char s[]) {
    int sign, max = NO;
    if ((sign = n) < 0) {
        if (n == -2147483648)
            max = YES;
        n = (max) ? 2147483647 : -n;
    }
    int i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    if (max)
        s[10] = '8';
}