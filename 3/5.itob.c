#include <stdio.h>
#include <string.h>
void reverse(char s[]) {
  for (int i = 0, j = strlen(s) - 1; i < j; j--, i++) {
    int c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
int pwr(int n, int p) {
  while (--p > 0)
    n *= n;
  return n;
}
void itob(int n, char s[], int b) {
  int i, j, sign;
  if ((sign = n) < 0)
    n = -n;
  i = 0;
  do {
    j = n % b;
    s[i++] = (j <= 9) ? j + '0' : j + 'a' - 10;
  } while ((n /= b) > 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

int main() {

  char str[1500];
  itob(4252, str, 2);
  printf("%s\n", str);
  return 0;
}