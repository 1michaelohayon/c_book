#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000
#define MAXFILES 10

/* prints lines that match pattern from 1st arg */
int grep(char *, char **, FILE *, bool, bool);
int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int c, found = 0;
    char *prog = argv[0];
    bool except = false, number = false;
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c) {
            case 'x':
                except = true;
                break;
            case 'n':
                number = true;
                break;
            default:
                printf("illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }

    /* first arguement is the pattern, anymore arguements will be attempted to
     * be opened as files */
    FILE *files[MAXFILES];
    char *filenames[MAXFILES];
    int i = 0;

    while (argc > 1)
        if ((files[i++] = fopen(argv[--argc], "r")) == NULL) {
            printf("%s: can't open %s\n", prog, argv[argc]);
            return 1;
        } else
            filenames[i - 1] = argv[argc];

    if (argc != 1)
        printf("usage: find -x -n pattern\n");
    else if (i == 0)
        found = grep(line, argv, stdin, number, except);
    else
        while (i--) {
            printf("file: %s \n----------------\n", filenames[i]);
            found += grep(line, argv, files[i], number, except);
            printf("========end of file========\n");
            fclose(files[i]);
        }
    if (found)
        printf("\nfound: %d\n", found);
    return found;
}

int grep(char *line, char **argv, FILE *f, bool number, bool except) {
    int found = 0;
    long lineno = 0;
    while (fgets(line, MAXLINE, f) != NULL) {
        lineno++;
        if ((strstr(line, *argv) != NULL) != except) {
            if (number)
                printf("%ld:", lineno);
            printf("%s", line);
            found++;
        }
    }
    return found;
}
