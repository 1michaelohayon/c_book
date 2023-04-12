#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100

/* fgets: get at most n chars from iop */
char *fgets(char *s, int n, FILE *iop) {
  register int c;
  register char *cs;

  cs = s;
  while (--n > 0 && (c = getc(iop)) != EOF)
    if ((*cs++ = c) == '\n')
      break;
  *cs = '\0';
  return (c == EOF & cs == s) ? NULL : s;
}

/* fputs: put string s on file iop */
int fputsx(char *s, FILE *iop) {
  int c;

  while ((c = *s++))
    putc(c, iop);

  return ferror(iop) ? EOF : 0;
}

/* getlinex: read a line, return length */
int getlinex(char *line, int max) {
  if (fgets(line, max, stdin) == NULL)
    return 0;
  else
    return strlen(line);
}

int main() {
  // double sum, v;
  // sum = 0;
  //
  // while(scanf("%1lf", &v) == 1)
  //   printf("\t%.2f\n", sum+=v);

  // int day, month, year;
  // scanf("%d/%d/%d", &day, &month, &year);
  // printf("%d, %d, %d\n", day, month, year);
  //
  //  int a;
  //  int b;
  //  int c;
  //  printf("%d\n", scanf("%d %d", &a, &b));

  char line[1000];
  //  while (getlinex(line, 1000) > 0)
  //    fputsx(line, stdout);

  // char *sp;
  // while ((sp = fgets(line, sizeof(line), stdin))) {
  //   printf("\tsp: %s\n", sp);
  //   fputsx(line, stdout);
  // }

  
  //system("date");

  int arr[] = {1, 2, 3, 4};
  int size = 4;

  int nsize = 7;
  int *narr; // MALLOC uninitialized
  if ((narr = (int *)malloc(sizeof(int) * nsize)) == NULL)
    return -1;

  for (int i = 0; i < size; i++)
    narr[i] = arr[i];

  narr[5] = 9;


  free(narr);


  /* CALLOC all initialzied to 0*/
  if ((narr = (int *)calloc(nsize, sizeof(int))) == NULL)
    return -1;


  for (int i = 0; i < size; i++)
    narr[i] = arr[i];

  for (int i = 0; i < nsize; i++)
    printf ("%d ", narr[i]);
  return 0;
}
