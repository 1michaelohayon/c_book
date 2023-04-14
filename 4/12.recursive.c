#include <stdio.h>
#include <string.h>
#define abs(x) ((x) < 0 ? -(x) : (x))

void itoa(int n, char s[]) {
    static int i;
    if (n / 10)
        itoa(n / 10, s);
    else {
        i = 0;
        if (n < 0)
            s[i++] = '-';
    }
    s[i++] = abs(n) % 10 + '0';
    s[i] = '\0';
}

int main() {
    char arr[20];
    itoa(425, arr);
    printf("%s", arr);
}
/*
425 / 10 == 42
  42/10 == 4
    4/10 == 0 integer division *trigger else*
    i = 0, is a static variable so it's the same memory
    if n < 0  add -

    convert last didigt of n to char and add it
    null terminate the string
    <- go back to prev scope if there is one
  convert last didigt of n to char and add it
  null terminate the string
  <- go back to prev scope if there is one
convert last didigt of n to char and add it
null terminate the string
<- go back to prev scope if there is one

 */