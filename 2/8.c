#include <stdio.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
  ((byte)&0x80 ? '1' : '0'), ((byte)&0x40 ? '1' : '0'),                        \
      ((byte)&0x20 ? '1' : '0'), ((byte)&0x10 ? '1' : '0'),                    \
      ((byte)&0x08 ? '1' : '0'), ((byte)&0x04 ? '1' : '0'),                    \
      ((byte)&0x02 ? '1' : '0'), ((byte)&0x01 ? '1' : '0')

int rightrot(int x, int n) {
  int wordlength(void);
  int rbit;
  while (n-- > 0) {
    rbit = (x & 1) << (wordlength() - 1);
    x = x >> 1;
    x = x | rbit;
  }
  return x;
}
int wordlength(void) {
  int i;
  unsigned v = (unsigned)0;

  for (i = 1; (v * v >> 1) > 0; i++)
    ;
  return i;
}

int main() {
  int x = 100;
  int y = rightrot(x, 1);

  printf("%d\n", y);

  printf("x, y: " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN "\n",
         BYTE_TO_BINARY(x), BYTE_TO_BINARY(y));
  return 0;
}
