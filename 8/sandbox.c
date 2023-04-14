#include <fcntl.h>
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

#include "malloc.c"
/* getchar:e buffered version */
int getchar(void) {
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) { // buffer is empty
        n = read(0, buf, sizeof(buf));
        bufp = buf;
    }
    return (--n >= 0) ? (unsigned char)*bufp++ : EOF;
}

/* read n bytes from position pos */
int get(int fd, long pos, char *buf, int n) {
    if (lseek(fd, pos, 0) >= 0)
        return read(fd, buf, n);
    else
        return -1;
}
int main() {
    // char buf[BUFSIZ];
    // int n;

    // while ((n = read(0, buf, BUFSIZ)))
    //   write (1, buf, n);

    // char c;
    // while ((c = getchar()))
    //   printf("%c", c);

    int arr[] = {4, 2, 7, 3};

    int nsize = 8;
    int *narr = (int *)memalloc(sizeof(int) * nsize);

    for (int i = 0; i < 4; i++) {
        narr[i] = arr[i];
    }

    narr[4] = 9;
    narr[5] = narr[6] = 423532;
    narr[7] = 7;
    for (int i = 0; i < nsize; i++) {
        printf("%d\n", narr[i]);
    }

    return 0;
}

// int getchar(void)  {
//   char c;
//   return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
// }
