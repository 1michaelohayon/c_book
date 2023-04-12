#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT 10
#define LINES 100
#define MAXLEN 100

void error(char *);
int getlinex(char *, int);

int main(int argc, char *argv[]) {
  char *p;
  char *buf;
  char *bufend;
  char line[MAXLEN];
  char *lineptr[LINES];
  int first, i, last, len, n, nlines;

  if (argc == 1)
    n = DEFAULT;
  else if (argc == 2 && (*++argv)[0] == '-')
    n = atoi(argv[1] + 1);
  else
    error("usage: tail [-n]");
  if (n < 1 || n > LINES)
    n = LINES;
  for (i = 0; i < LINES; i++)
    lineptr[i] = NULL;
  if ((p = buf = malloc(LINES * MAXLEN)) == NULL)
    error("tail: cannot allocate buf");
  bufend = buf + LINES * MAXLEN;
  last = 0;
  nlines = 0;

  while ((len = getlinex(line, MAXLEN)) > 0) {
    if (p + len + 1 >= bufend)
      p = buf;
    lineptr[last] = p;
    strcpy(lineptr[last], line);
    if (++last >= LINES)
      last = 0;
    p += len + 1;
    nlines++;
  }
  if (n > nlines)
    n = nlines;
  first = last - n;
  if (first < 0)
    first += LINES;
  for (i = first; n-- > 0; i = (i + 1) % LINES)
    printf("%s", lineptr[i]);
  return 0;
}


void error(char *s) {
  printf("%s\n", s);
  exit(1);
}

int getlinex(char *s, int lim) {
  int c;
  char *ps = s;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    *s++ = c;
  if (c == '\n')
    *s++ = c;
  *s = '\0';
  return s - ps;
}


