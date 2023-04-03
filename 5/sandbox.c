#include "1.getint.c"
#include "getch.c"
#include <stdio.h>
#include <string.h>
#define SIZE 10


/* strmp: pointer version */
int strcmpp(char *s, char*t) {
  for(; *s == *t; s++, t++)
    if(!*s)
      return 0;
  return *s - *t;
}

/* strcmp: return <0  if s<t , 0 if s==t, >0 if s>t */ 
int strcmpx(char * s, char *t) {
  int i;
  for(i = 0; s[i] == t[i]; i++)
    if(!s[i])
      return 0;
  return s[i] - t[i];
}

/* strcpy: copy t to s; pointer version 1 */
void strcpyp(char *s, char *t) {
  while ((*s++ = *t++))
    ;
}

/* strcpy: copy t to s; array subscript version */
void strcpya(char *s, char *t) {
  int i = 0;

  while ((s[i] = t[i]) != '\0')
    i++;
}

void printarr(int *arr, int len) {
  printf("[");
  for (int i = 0; i < len - 1; i++)
    printf("%d,", arr[i]);

  printf("%d]\n", arr[len - 1]);
}
/* strlen: return length of string s */
int strlenxy(char *s) {
  int n;

  for (n = 0; *s != '\0'; s++)
    n++;
  return n;
}
/* strlen: return length of string s  version 2*/
size_t strlenx(char *s) {
  char *p = s;

  while (*p != '\0')
    p++;
  return p - s;
}

void swap(int *px, int *py) {
  int tmp = *px;
  *px = *py;
  *py = tmp;
}

int main() {
  int x = 1, y = 2, z[10];
  int *ip = &x;
  y = *ip;
  *ip = 0;

  ip = &z[0];
  *ip = 19;
  *ip += 4;

  y = *ip + 9;
  (*ip)++;
  ++*ip;
  int *iq = ip;
  *iq = 5;
  printf("x:%d, y:%d, z[0]:%d, *ip:%d, *iq:%d\n", x, y, z[0], *ip, *iq);

  printf("\n=====================================\n");

  int arr[] = {5, 10};
  swap(&arr[0], &arr[1]);
  printarr(arr, 2);

  printf("\n=====================================\n");
  //
  // int n, array[SIZE], getint(int *);
  // printarr(array, SIZE);
  //
  // for( n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
  //   ;
  // printarr(array, SIZE);
  //
  // printf("\n=====================================\n");

  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int *pa;

  pa = &a[2];
  int *paa = &*(a + 2); // points to 2 like the above statement
  int *pab = a;         // points to 0;
  printarr(a, 10);
  printf("*pa:%d, *paa:%d, *pab:%d\n", *pa, *paa, *pab);

  pa++;    // pa now points to a[3]
  pa += 4; // pa now points to a[7]
  printf("*pa:%d\n", *pa);
  printf("\n=====================================\n");

  char str[] = "hello";
  char *ps = str;
  printf("strlenx: %d\n", (int)strlen(ps));

  int abc = 324;

  char str2[10];
  strcpyp(str2, str);

  printf("%s : %s\n", str, str2);
  char str3[] ="hello";

  printf("%s : %s _ %d\n", str, str3, strcmpp(str, str3));

  return 0;
}


// *p++ = val push val onto stack
// val = *--p pop top of stack into val