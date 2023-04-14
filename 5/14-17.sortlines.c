#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINES 5000 // max lines to be sorted
#define NO 0
#define YES 1

char *lineptr[MAXLINES]; // pointers to textlines

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);
void qsortx(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmpx(char *, char *), strcmp_cins(char *s, char *t);

int numeric = NO; // numeric sorting instad of lexcographic
int reverse = NO;
int foldcase = NO; // case insenstive
int dirorder =
    NO; // directory order, only compare letters, nmumbers, and blanks

int start = 0; // starting col
int end = NO;  //  end col

/* sort input lines */
int main(int argc, char *argv[]) {
    while (argc-- > 1)
        if (strcmp(argv[argc], "-n") == 0)
            numeric = YES;
        else if (strcmp(argv[argc], "-r") == 0)
            reverse = YES;
        else if (strcmp(argv[argc], "-f") == 0)
            foldcase = YES;
        else if (strcmp(argv[argc], "-d") == 0)
            dirorder = YES;
        else if (strcmp(argv[argc], "-s") == 0) {
            for (char *ps = argv[argc + 1]; *ps; ps++)
                if (!isdigit(*ps)) {
                    printf("sortlines error: -s n: invalid number\n");
                    return 1;
                }
            start = atoi(argv[argc + 1]);

        } else if (strcmp(argv[argc], "-e") == 0) {
            for (char *ps = argv[argc + 1]; *ps; ps++)
                if (!isdigit(*ps)) {
                    printf("sortlines error: -e n: invalid number\n");
                    return 1;
                }
            end = atoi(argv[argc + 1]);
        }

    if (end && start >= end) {
        printf("sortlines error:invalid args: start >= end\n");
        return 1;
    }

    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsortx((void **)lineptr, 0, nlines - 1,
               (int (*)(void *, void *))(numeric ? numcmp : strcmpx));
        writelines(lineptr, nlines, reverse);
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

void writelines(char *lineptr[], int nlines, int reverse) {
    if (reverse)
        while (nlines)
            printf("%s\n", lineptr[--nlines]);
    else
        while (nlines-- > 0)
            printf("%s\n", *lineptr++);
}

void swap(void *v[], int i, int j) {
    char *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}
int alnum_or_space(char *s, char *x) {
    return ((isalnum(*s) || isspace(*s)) && (isalnum(*x) || isspace(*x)));
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

int numcmp(char *s1, char *s2) {
    double v1 = atof(s1), v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* case insensetive strcmp */
int strcmp_cins(char *s, char *t) {
    for (int j = 0; tolower(*s) == tolower(*t); s++, t++, j++) {
        if (*s == '\0')
            return 0;
        if (end && j == end - start)
            break;
    }
    return tolower(*s) - tolower(*t);
}

int strcmpx(char *s, char *t) {
    for (int i = 0; i < start; i++) {
        s++;
        t++;
        printf("%d g\n", i);
    }

    if (dirorder) {
        while (!isalnum(*s) && !isspace(*s) && *s != '\0')
            s++;
        while (!isalnum(*t) && !isspace(*t) && *t != '\0')
            t++;
    }

    if (foldcase)
        return strcmp_cins(s, t);

    for (int j = 0; *s == *t; s++, t++, j++) {
        if (*s == '\0')
            return 0;
        if (end && j == end - start) {
            printf("BROKE\n");
            break;
        }
    }
    return *s - *t;
}
