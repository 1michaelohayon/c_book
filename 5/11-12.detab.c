#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000
#define SPACES 4

int getlinex(char line[], int maxline);
void foldline(char line[], int len);
void set_tabstops(int argc, char *argv[], char *line);

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int len;
    while ((len = getlinex(line, MAXLINE)) > -1) {
        if (argc > 1)
            set_tabstops(argc, argv, line);
        foldline(line, len);
    }
}
void set_tabstops(int argc, char *argv[], char *line) {
    // if -m -n, starting at m, sets tabstop every n col
    if (argc == 3 && argv[1][0] == '-' && argv[2][0] == '+') {
        int m = argv[1][1] - '0';
        int n = argv[2][1] - '0';
        printf("m: %d, n: %d\n", m, n);
        while (m < MAXLINE)
            line[m += (n > 0) ? n : 1] = '\t';
    } else
        while (--argc) {
            int i = atoi(*++argv);
            if (i >= 0 && i < MAXLINE)
                line[i] = '\t';
        }
}
void foldline(char line[], int len) {
    for (int i = 0; i < len; i++)
        if (line[i] == '\t') {
            for (int x = 0; x < SPACES; x++)
                putchar(' ');
        } else {
            putchar(line[i]);
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
