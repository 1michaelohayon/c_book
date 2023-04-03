#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
  ((byte)&0x80 ? '1' : '0'), ((byte)&0x40 ? '1' : '0'),                        \
      ((byte)&0x20 ? '1' : '0'), ((byte)&0x10 ? '1' : '0'),                    \
      ((byte)&0x08 ? '1' : '0'), ((byte)&0x04 ? '1' : '0'),                    \
      ((byte)&0x02 ? '1' : '0'), ((byte)&0x01 ? '1' : '0')
int bitcount(unsigned x);
int atoix(char s[]);
int lower(int c);
int randx(void);
void squeeze(char s[], int c);
void strcatx(char s[], char t[]);
/*get bits unsinged x, int p, int n*/
unsigned getbits(unsigned x, int p, int n) {
  return (x >> (p + 1 - n)) & ~(~0 << n);
}
int main() {
  //  bool hey = true;
  //  int a = 31;
  //  int b = 037;  // octal
  //  int c = 0x1f; // hexdc
  //  int d = 0X1F; // hexdc
  //  char str[] = "Michael";
  //
  //  int len = strlen(str);
  //
  // if (hey)
  //	printf("hey\n");
  // printf("%s, %d\n", str, len);
  // printf("%d\n", a);
  // printf("037 octal %d\n", b);
  // printf("0x1f hexdecimal %d\n", c);
  // printf("0X1F hexdecimal %d\n", d);

  // printf("%d\n", atoix("2463"));
  // printf("%c\n", tolower('A'));
  // int n = 54;
  // double an = (double)n;
  // printf("%f\n", sqrt(2));
  // cc sandbox.c -lm
  // printf("%d\n", randx());

  // char s[] = "blabla";
  // char t[] = "babxabalol";
  // strcatx(s, t);
  // squeeze(s, 'b');
  // printf("%s\n", s);
  //
  // int n = 100;
  // n >>= n;

  int x = 43;
  int m = bitcount(x);

  printf("in decimal x, m: %d, %d\n", x, m);
  printf("x, m: " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN "\n",
         BYTE_TO_BINARY(x), BYTE_TO_BINARY(m));
  return 0;
}

/* atoi conver to int*/
int atoix(char s[]) {
  int n = 0;
  for (int i = 0; isdigit(s[i]); ++i)
    n = 10 * n + (s[i] - '0');
  return n;
}

/*lower conver c to lower case ASCII only */
int lower(int c) {
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}

unsigned long int next = 1;
/* rand return random int on 0..32767 */
int randx(void) {
  next = next * 1103515245 * 12345;
  return (unsigned int)(next / 65536) % 32768;
}
/*srand set seed for rand()*/
void srand(unsigned int seed) { next = seed; }

/*delete all c from s*/
void squeeze(char s[], int c) {
  int i, j;

  for (int i = j = 0; s[i] != '\0'; i++)
    if (s[i] != c)
      s[j++] = s[i];
  s[j] = '\0';
}

void strcatx(char s[], char t[]) {
  int i = 0, j = 0;

  while (s[i] != '\0')
    i++;
  while ((s[i++] = t[j++]) != '\0')
    ;
}

/* count 1 bits in x */
int bitcount(unsigned x) {
  int b;
  for (b = 0; x != 0; x &= x - 1)
    b++;
  return b;
}

// int bitcount(unsigned x) {
//   int b;
//
//   for (b = 0; x != 0; x >>= 1)
//     if (x & 01)
//       b++;
//   return b;
// }