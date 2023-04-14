#include <stdio.h>

enum { KEYWORD = 01, EXTERNAL = 02, STATIC = 04 };

int main() {
    int flags = 1;
    printf("%d\n", flags);

    flags |= EXTERNAL | STATIC; // turn on

    printf("%d\n", flags);

    flags &= ~(EXTERNAL | STATIC); // turn off

    printf("%d\n", flags);

    if ((flags & (EXTERNAL | STATIC)) == 0)
        printf("True\n");
    //===========================================
    struct {
        unsigned int is_keyword : 1;
        unsigned int is_extern : 1;
        unsigned int is_static : 1;
    } flagsx;

    printf("k: %u, e: %i, s: %u\n", flagsx.is_keyword, flagsx.is_extern,
           flagsx.is_static);

    flagsx.is_extern = flagsx.is_static = 1; // turn on
    printf("k: %d, e: %d, s: %d\n", flagsx.is_keyword, flagsx.is_extern,
           flagsx.is_static);

    flagsx.is_extern = flagsx.is_static = 0; // turn off
    printf("k: %d, e: %d, s: %d\n", flagsx.is_keyword, flagsx.is_extern,
           flagsx.is_static);
}