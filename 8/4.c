#include "syscalls.h"
#include <unistd.h>

int fseek(FILE *fp, long offset, int origin) {
    unsigned nc;
    long rc = 0;

    if (fp->flag & _READ) {
        if (origin == 1)
            offset -= fp->cnt;
        rc = lseek(fp->fd, offset, origin);
        fp->cnt = 0;
    } else if (fp->flag & _WRITE) {
        if ((nc = fp->ptr - fp->base) > 0)
            if (write(fp->fd, fp->base, nc) != nc)
                rc = -1;
        if (rc != -1)
            rc = lseek(fp->fd, offset, origin);
    }

    return (rc == -1) ? -1 : 0;
}
