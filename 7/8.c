#include <stdio.h>
#define MAXFILES 300
#define MAXLINE 1000

void printfile(FILE *out, FILE *in) {
    char line[MAXLINE];
    fprintf(out, "\n");
    while (fgets(line, MAXLINE, in) != NULL) {
        fprintf(out, "  %s", line);
    }
    fprintf(out, "\n");
}

int main(int argc, char *argv[]) {
    char *prog = argv[0];
    if (argc <= 1) {
        printf("%s: no files\n", prog);
        return 1;
    }

    FILE *files[MAXFILES];
    char *filenames[MAXFILES];
    int i = 0, page_number = 0;

    while (argc > 1)
        if ((files[i++] = fopen(argv[--argc], "r")) == NULL) {
            printf("%s: can't open %s\n", prog, argv[argc]);
            return 1;
        } else
            filenames[i - 1] = argv[argc];

    while (i--) {
        fprintf(stdout, "\n\nTitle: %s\tPage: %d\n", filenames[i],
                ++page_number);
        printfile(stdout, files[i]);
    }
    return 0;
}
