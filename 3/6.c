#include <stdio.h>
#include <string.h>
#define abs(x) ((x) < 0 ? -(x) : (x))
void reverse(char s[]) {
  for (int i = 0, j = strlen(s) - 1; i < j; j--, i++) {
    int c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

/*itoav2 convert n to s. minimum field, mf, will pad to the left if the output
 * is smaller*/
void itoa(int n, char s[], int mf) {
  int i, sign;
  sign = n;
  i = 0;
  do {
    s[i++] = abs(n % 10) + '0';
  } while ((n /= 10) != 0);
  if (sign < 0)
    s[i++] = '-';
  while (i < mf)
    s[i++] = ' ';
  s[i] = '\0';
  reverse(s);
}

int main() {
  char s[100];
  int mf = 9;

  itoa(123456789, s, mf);
  printf("%s\n", s);
}
