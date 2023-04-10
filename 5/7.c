#include <stdio.h>
#include <string.h>
#define MAXLINES 5000 //max lines to be sorted
#define MAXLEN 1000 //max len of any input line

char *lineptr[MAXLINES]; // pointers to textlines

int readlines(char *lineptr[], char *linestor, int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main() {
  int nlines;  //number of input lines read 
  char linestor[MAXLEN];
  if ((nlines = readlines(lineptr,linestor, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr,nlines);
    return 0;
  } else {
    printf ("error: input too big to sort\n");
    return 1;
  }
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


/* without using alloc */
//readlines: read input lines
int readlines(char *lineptr[], char *linestor, int maxlines) {
  int len, nlines;
  char line[MAXLEN];
  char *p = linestor;
  char *linestop = linestor + MAXLEN;

  nlines = 0;
  while ((len = getlinex(line, maxlines)) > 0)
    if (nlines >= maxlines || p+len > linestop)
      return -1;
    else {
      line[len-1] = '\0'; // delete newline
      strcpy(p, line);
      lineptr[nlines++] = p;
      p += len; // p now points to the next location
    }
  return nlines;
}


void writelines(char *lineptr[], int nlines) {
  while(nlines-- > 0)
    printf("%s\n", *lineptr++);
}



void swap(char *v[], int i, int j) {
  char *tmp =v[i];
  v[i] = v[j];
  v[j] = tmp;
}

/* qsort: sort v[left]... v[right] into increasing order */
void qsort(char *v[], int left, int right) {
  int i, last;

  if (left >= right) /* do nothig if array contains */
    return;
  swap(v, left, (left + right) /2);
  last = left;
  for (i = left + 1; i < right; i++)
    if(strcmp(v[i], v[left]) < 0)
      swap (v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}