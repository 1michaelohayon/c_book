#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

typedef struct _iobuf {
  int cnt;    /* characters left */
  char *ptr;  /* next character position */
  char *base; /* location of buffer */
  struct flag {
    unsigned read : 1;
    unsigned write : 1;
    unsigned unbuf : 1;
    unsigned buf : 1;
    unsigned eof : 1;
    unsigned err : 1;
  } flag; /* mode of file access */
  int fd; /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])


int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag.eof) != 0)
#define ferror(p) (((p)->flag.err) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) ((--(p)->cnt >= 0) ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) ((--(p)->cnt >= 0) ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getch(stdin)
#define putchar(x) putc((x), stdout)

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
    if (fp->flag.read == 0 && fp->flag.write == 0)
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
  fp->flag.unbuf = 0;
  fp->flag.buf = 1;
  fp->flag.eof = 0;
  fp->flag.err = 0;
  if (*mode == 'r') {
    fp->flag.read = 1;
    fp->flag.write = 0;
  } else {
    fp->flag.read = 0;
    fp->flag.write = 1;
  }
  return fp;
}

#include <stdlib.h>

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp) {
  int bufsize;

  if (!fp->flag.read || fp->flag.eof || fp->flag.err)
    return EOF;

  bufsize = (fp->flag.unbuf) ? 1 : BUFSIZ;

  if (fp->base == NULL)
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
      return EOF;

  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);

  if (--fp->cnt < 0) {
    if (fp->cnt == -1)
      fp->flag.eof = 1;
    else
      fp->flag.err = 1;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}

FILE _iob[OPEN_MAX] = {
    {0, (char *)0, (char *)0, {1,0,0,1,0,0}, 0},
    {0, (char *)0, (char *)0, {0,1,0,1,0,0}, 1},
    {0, (char *)0, (char *)0, {0,1,1,1,0,0}, 2}
};
