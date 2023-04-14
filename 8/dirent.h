#define NAME_MAX 14 /* longest filename component;*/
/* system-dependent */


typedef struct {           /* portable directory entry */
  long ino;                /* file descriptor for directory */
  char name[NAME_MAX + 1]; /* name + '\0' terminator */
} Direntx;

typedef struct { /* minimal DIRx: no bufffering, etc */
  int fd;        /* file descriptor for directory */
  Direntx d;      /*the directory entry */
} DIRx;
