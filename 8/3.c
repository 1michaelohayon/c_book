#include "syscalls.h"
#include <fcntl.h>
#include <unistd.h>

#define PERMS 0666
/* fopen: open filem return file ptr */
FILE *fopenx(char *name, char *mode) {
  int fd;
  FILE *fp;

  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;

  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if ((fp->flag & (_READ | _WRITE)) == 0)
      break;
 
  if (fp >= _iob + OPEN_MAX) /* no free slots */
    return NULL;

  if (*mode == 'w')
    fd = creat(name, PERMS);
  else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0L, 2);
  } else
    fd = open(name, O_RDONLY, 0);

  if (fd == -1)
    return NULL;

  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}

#include <stdlib.h>

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp) {
  int bufsize;

  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
    return EOF;

  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

  if (fp->base == NULL)
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
      return EOF;

  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);

  if (--fp->cnt < 0) {
    if (fp->cnt == -1)
      fp->flag |= _EOF;
    else
      fp->flag |= _ERR;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}

FILE _iob[OPEN_MAX] = {{0, (char *)0, (char *)0, _READ, 0},
                       {0, (char *)0, (char *)0, _WRITE, 1},
                       {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}

};

int _flushbuf(int x, FILE *fp) {
  unsigned nc;
  int bufsize;

  if (fp < _iob || fp >= _iob + OPEN_MAX)
    return EOF;

  if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
    return EOF;

  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if (fp->base == NULL) {
    if ((fp->base = (char *)malloc(bufsize)) == NULL) {
      fp->flag |= _ERR;
      return EOF;
    }
  } else {
    nc = fp->ptr - fp->base;
    if (write(fp->fd, fp->base, nc) != nc) {
      fp->flag |= _ERR;
      return EOF;
    }
  }
  fp->ptr = fp->base;
  *fp->ptr++ = (char)x;
  fp->cnt = bufsize - 1;
  return x;
}

int fflush(FILE *fp) {
  int rc = 0;
  if (fp < _iob || fp >= _iob + OPEN_MAX)
    return EOF;
  if (fp->flag & _WRITE)
    rc = _flushbuf(0, fp);
  fp->ptr = fp->base;
  fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  return rc;
}

int fclose(FILE *fp) {
  int rc;

  if ((rc = fflush(fp)) != EOF) {
    free(fp->base);
    fp->ptr = NULL;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag &= (_READ | _WRITE);
  }
  return rc;
}