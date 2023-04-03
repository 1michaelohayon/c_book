#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define YES 1
#define NO 0

/* shellsort sort v[0]*/
void shellsort(int v[], int n) {
  for (int gap = n / 2; gap > 0; gap /= 2)
    for (int i = gap; i < n; i++)
      for (int j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
        int tmp = v[j];
        v[j] = v[j + gap];
        v[j + gap] = tmp;
      }
}

/* binsearch: find x in v[0] <= [v1] <=  ... <= v[n-1]*/
int binsearch(int x, int v[], int n) {
  int low = 0, high = n - 1;

  while (low <= high) {
    int mid = (low + high) / 2;
    if (x < v[mid])
      high = mid;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

void reverse(char s[]) {
  for (int i = 0, j = strlen(s) - 1; i < j; j--, i++) {
    int c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

/* convert to int v2 */
int atoi(char s[]) {
  int i, n, sign;
  for (i = 0; isspace(s[i]); i++) // skip white space
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;

  for (n = 0; isdigit(s[i]); i++)
    n = 10 * n + (s[i] - '0');
  return sign * n;
}
/*itoa convert n to s*/
void itoa(int n, char s[]) {
  int sign, max = NO;
  if ((sign = n) < 0) {
    if (n == -2147483648)
      max = YES;
    n = (max) ? 2147483647 : -n;
  }
  int i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
  if (max)
    s[10] = '8';
}

void count_white_space() {
  int c, i, nwhite, nother, ndigit[10];
  nwhite = nother = 0;

  nwhite = nother = 0;

  for (i = 0; i < 10; i++)
    ndigit[i] = 0;

  while ((c = getchar()) != EOF)
    switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      ndigit[c - '0']++;
      break;
    case ' ':
    case '\t':
    case '\b':
      nwhite++;
      break;
    default:
      nother++;
      break;
    }

  printf("digits =");
  for (i = 0; i < 10; i++)
    printf("% d", ndigit[i]);
  printf(", white space = %d, other = %d\n", nwhite, nother);
}

int trim(char s[]) {
  int n;
  for (n = strlen(s) - 1; n >= 0; n--)
    if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
      break;
  s[n + 1] = '\0';
  return n;
}
void goto_test() {

  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      if (j == i + 3)
        goto found;

  return;
found:
  printf("got it");
}

int main() {
  int arr[] = {7, 3, 4, 1, 5};
  int len = 5;
  //
  // int x = 7;
  // int ans = binsearch(x, arr, 5);
  //
  // printf("index of %d is %d\n", x, ans);
  // count_white_space();

  // char s[] = " -674";
  //
  // printf("%d\n", (s));
  //
  //  char hello[] = "hello world";
  //  reverse(hello);
  //  printf("%s\n", hello);
  //
  //  int i = 0;
  //  shellsort(arr, len);
  //
  //  do
  //    printf(" %d", arr[i]);
  //  while (++i < 5);
  //  putchar('\n');

  // char str[15];
  //
  // itoa(-2147483648, str);
  //
  // printf("%s\n", str);

  // char s[] = " ";
  // trim(s);
  // printf("%s%s%d\n", s, "hey", (int)strlen(s));
  goto_test();
}