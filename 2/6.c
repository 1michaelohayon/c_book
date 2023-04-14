#include <stdio.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
    ((byte)&0x80 ? '1' : '0'), ((byte)&0x40 ? '1' : '0'),                      \
        ((byte)&0x20 ? '1' : '0'), ((byte)&0x10 ? '1' : '0'),                  \
        ((byte)&0x08 ? '1' : '0'), ((byte)&0x04 ? '1' : '0'),                  \
        ((byte)&0x02 ? '1' : '0'), ((byte)&0x01 ? '1' : '0')

int setbits(int x, int p, int n, int y) {
    return x & ((0 << n) << (p + 1 - n)) | (y & (0 << n)) << (p + 1 - n);
}

int main() {

    int x = 5;
    int y = setbits(x, 7, 7, 12);
    printf("x: %d, y: %d\n", x, y);
    printf("x, m: " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN "\n",
           BYTE_TO_BINARY(x), BYTE_TO_BINARY(6));
}