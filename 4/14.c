#include <stdio.h>
#define swap(t, x, y)                                                          \
  {                                                                            \
    t _z;                                                                      \
    _z = y;                                                                    \
    y = x;                                                                     \
    x = _z;                                                                    \
  }

int main() {
  char arr[] = {'a', 'b'};
  swap(int, arr[0], arr[1]);
  printf("%c, %c\n", arr[0], arr[1]);
  return 0;
}