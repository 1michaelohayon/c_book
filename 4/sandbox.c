#include <bits/types/FILE.h>
#include <ctype.h>
#include <stdio.h>
#define MAXLINE 1000
#define forever for (;;)
/* bug: using max(i++, --b) etc will cause it to tirgger more tan once */
#define max(A, B) ((A) > (B) ? (A) : (B))
#define dprint(expr) printf(#expr " = %g\n", expr)
#define paste(front, back) front##back

#if !defined(hdr)
#define HDR2
/*cotents  goes ehre for the preprocessor-if */
#endif

#ifndef HDR5
#define HDR5
#endif

#ifdef HDR4
#undef HDR4
#endif

#if SYSTEM == SYSV
#define HDR "sysv.h"
#elif SYSTEM == BSD
#define HDR "bsd.h"
elif SYSTEM == MSDOS
#define HDR "msdos.h"
else
#define HDR "default.h"
#endif
// #include HDR

/* printd: print n in decimal */
void printd(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}

/* atof: convert string s to double */
double atof(char s[]) {
    double val, power;
    int exp, i, sign;

    for (i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    return sign * val / power;
}

int getlinex(char s[], int lim) {
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
// swap interchange v[i] and v[j]
void swap(int v[], int i, int j) {
    int tmp;
    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

// qsort: sort v[left]...v[right] int increasing order
void qsort(int v[], int left, int right) {
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right) //  do nothing if array contains fewer than two elemts
        return;
    swap(v, left, (left + right) / 2); // move partion elem
    last = left;
    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last); // restore partion elem
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

int main() {

    //  int arr[] = {5, 3, 2, 6, 7, 9, 1};
    //  qsort(arr, 0, 7);
    //  for (int i = 0; i < 7; i++)
    //    putchar(arr[i] + '0');
    //
    double a = 3.0;
    double c = 5.0;
    double b = 10.0;
    dprint(max(a, c) * b);
    char name1[] = "michael";

    printf("%s\n", paste(name, 1));
    //  printd(1);

    // char s[] = "42.141";
    //
    // double sum, atof(char[]);
    // char line[MAXLINE];
    //
    // while (getlinex(line, MAXLINE) > 0)
    //  printf("\t%g\n", sum += atof(line));
}
