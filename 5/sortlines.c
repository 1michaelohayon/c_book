#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 // max lines to be sorted

char *lineptr[MAXLINES]; // pointers to textlines

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsortx(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmpx(char *, char *);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0;
    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsortx((void **)lineptr, 0, nlines - 1,
               (int (*)(void *, void *))(numeric ? numcmp : strcmpx));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000
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

char *alloc(int);

// readlines: read input lines
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char line[MAXLEN], *p;

    nlines = 0;
    while ((len = getlinex(line, maxlines)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0'; // delete newline
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void swap(void *v[], int i, int j) {
    char *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

/* qsort: sort v[left]... v[right] into increasing order */
void qsortx(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;

    if (left >= right) /* do nothig if array contains */
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsortx(v, left, last - 1, comp);
    qsortx(v, last + 1, right, comp);
}

double atof(char *s) {
    double val, power;
    int exp, i, sign;

    for (; isspace(*s); s++)
        ;

    sign = (*s == '-') ? -1 : 1;

    if (*s == '+' || *s == '-')
        s++;

    for (val = 0.0; isdigit(*s); s++)
        val = 10.0 * val + (*s - '0');

    if (*s == '.')
        s++;

    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }

    return sign * val / power;
}

int numcmp(char *s1, char *s2) {
    double v1 = atof(s1), v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int strcmpx(char *s, char *t) {
    int i;
    for (i = 0; s[i] == t[i]; i++)
        if (!s[i])
            return 0;
    return s[i] - t[i];
}