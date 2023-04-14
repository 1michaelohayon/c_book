#include <unistd.h> /* sbrk */

#ifdef NULL
#undef NULL
#endif
#define NULL 0
#define NALLOC 1024

typedef long Align;
union header {
    struct {
        union header *next;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

static Header *morecore(unsigned);
void freem(void *);

void *memalloc(unsigned nbytes) {
    Header *cp;
    Header *prevp;
    unsigned nunits;

    nunits = ((nbytes + sizeof(Header) - 1) / sizeof(Header)) + 1;

    if (freep == NULL) {

        base.s.next = &base;
        base.s.size = 0;

        freep = &base;
    }

    prevp = freep;

    for (cp = prevp->s.next;; prevp = cp, cp = cp->s.next) {
        if (cp->s.size >= nunits) {
            if (cp->s.size == nunits) {
                prevp->s.next = cp->s.next;
            } else {
                cp->s.size -= nunits;
                cp += cp->s.size;
                cp->s.size = nunits;
            }
            freep = prevp;
            return (void *)(cp + 1);
        }

        if (cp == freep)
            if ((cp = morecore(nunits)) == NULL)
                return NULL;
    }
}

static Header *morecore(unsigned nunits) {
    void *freemem;
    Header *insertp;

    if (nunits < NALLOC)
        nunits = NALLOC;

    freemem = sbrk(nunits * sizeof(Header));
    if (freemem == (void *)-1)
        return NULL;

    insertp = (Header *)freemem;
    insertp->s.size = nunits;

    freem((void *)(insertp + 1));

    return freep;
}

void freem(void *ptr) {
    Header *insertp, *cp;

    insertp = ((Header *)ptr) - 1;

    for (cp = freep; !((cp < insertp) && insertp < cp->s.next); cp = cp->s.next)
        if ((cp >= cp->s.next) && ((cp < insertp) || insertp < cp->s.next))
            break;

    if ((insertp + insertp->s.size) == cp->s.next) {
        insertp->s.next += cp->s.next->s.size;
        insertp->s.next = cp->s.next->s.next;
    } else
        insertp->s.next = cp->s.next;

    if ((cp + cp->s.size) == insertp) {
        cp->s.size += insertp->s.size;
        cp->s.next = insertp->s.next;
    } else
        cp->s.next = insertp;

    freep = cp;
}