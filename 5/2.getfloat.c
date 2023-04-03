#include <ctype.h>
#include <stdio.h>
#define SIZE 10
#include "getch.c"


void printarr(float *arr, int len) {
  printf("[");
  for (int i = 0; i < len - 1; i++)
    printf("%0.2f,", arr[i]);

  printf("%0.2f]\n", arr[len - 1]);

}


/* getfloat: get next float from input into *pn */
int getfloat(float *pn) {
  int c, sign, getch(void);
  void ungetch(int);
  float pow;

  while (isspace(c = getch()))
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    int d = c;
    if (!isdigit(c = getch())) {
      if (c != EOF)
        ungetch(c);
      ungetch(d);
      return d;
    }
  }
  for (*pn = 0.0; isdigit(c); c = getch())
    *pn = 10.0 * *pn + (c - '0');
 
  if (c == '.') 
    c = getch();
 
  for (pow = 1.0; isdigit(c); c = getch()) {
    *pn = 10.0 * *pn + (c - '0'); // fractional
    pow *= 10.0;
  }
  
  *pn *= sign / pow;
  if (c != EOF)
    ungetch(c);
  return c;
}






int main() {
  float array[SIZE];
  int n;
  printarr(array, SIZE);
  for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
    ;
  printarr(array, SIZE);

  return 0;
}




/* works but WRONG, should've returned int */
/* getfloat: get next float from input into *pn */
//float getfloatw(float *pn) {
//  int c, sign, getch(void);
//  void ungetch(int);
//
//  while (isspace(c = getch()))
//    ;
//  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
//    ungetch(c);
//    return 0.0;
//  }
//
//  sign = (c == '-') ? -1 : 1;
//  if (c == '+' || c == '-')
//    /* respects the first - or + */
//    while (isspace(c = getch()) || c == '+' || c == '-')
//      ;
//
//  for (*pn = 0; isdigit(c); c = getch()) 
//    *pn = 10 * *pn + (c - '0');
//  
//
//  if (c == '.') {
//    c = getch();
//    for (float i = 0.1; isdigit(c); c = getch(), i /= 10)
//       *pn += i * (c - '0');
//  }
//  *pn *= sign;
//  if (c != EOF)
//    ungetch(c);
//  return c;
//}