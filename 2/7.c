#include <stdio.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)

int invert(int x, int p, int n) { return x | ((0 << n)) << (p + 1 - n); }

int main() {
    printf("%d, %d\n", 5, invert(5, 3, 6));

    return 0;
}