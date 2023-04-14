#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* cat: concatenate files */
void cat8(int, char *[]);
void cat7(int, char *[]);
int main(int argc, char *argv[]) {
    clock_t start, end;
    double cpu_time;
    start = clock();
    // cat7(argc, argv); /* Times: 0.000346, 0.000378, 0.000269, 0.000293 */
    //  cat8(argc, argv); /* Times:	0.000056, 0.000184, 0.000062, 0.000070
    //  */
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time:\t%f\n", cpu_time);
    return 0;
}

void cat7(int argc, char *argv[]) {
    FILE *fp;

    void filecopy(FILE *, FILE *);
    char *prog = argv[0]; /* program name for errors */

    if (argc == 1) /* no args, copy standard output */
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("cat : can't open %s\n", *argv);
                return;
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        return;
    }
    return;
}

/* copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp) {
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

void error(char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    return;
}

void cat8(int argc, char *argv[]) {
    int fd;
    void filecopy2(int ifd, int ofd);

    if (argc == 1)
        filecopy2(0, 1);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY)) == -1)
                error("cat: error: can't open %s", argv);
            else {
                filecopy2(fd, 1);
                close(fd);
            }
    return;
}
void filecopy2(int ifd, int ofd) {
    int n;
    char buf[BUFSIZ];
    while ((n = read(ifd, buf, BUFSIZ)) > 0)
        if (write(ofd, buf, n) != n)
            error("cat: error can't write");
}