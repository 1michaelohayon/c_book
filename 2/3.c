#include <ctype.h>
#include <stdio.h>
#define YES 1
#define NO 0

int c = 0x1f; // hexdc 31
int d = 0X1F; // hexdc 31

int htoi(char s[]) {
    int hexdigit;

    int i = 0;
    if (s[i] == '0') {
        i++;
        if (s[i] == 'x' || s[i] == 'X')
            i++;
    }

    int n = 0;
    int inhex = YES;
    for (; inhex == YES; i++) {

        if (s[i] >= '0' && s[i] <= '9')
            hexdigit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            hexdigit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            hexdigit = s[i] - 'A' + 10;
        else
            inhex = NO;

        if (inhex == YES)
            n = 16 * n + hexdigit;
    }
    return n;
}

int main() {

    char strx[] = "0x1f";

    int n = htoi(strx);

    printf("%d\n", n);

    return 0;
}
