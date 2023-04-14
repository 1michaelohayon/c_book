#define isupper(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0

#include <stdio.h>

int isupperx(char c) { return (c >= 'A' && c <= 'Z') ? 1 : 0; }

int main() {
    char c = 'A';
    printf("%d\n", isupper(c)); // prints 1
    printf("c: %c\n", c);
    printf("%d\n", isupper(c++)); /*prints 1, expends to ((c++) >= 'A' && (c++)
    <= 'Z') ? 1 : 0 which results in 'A' to increment twice to 'C'
  */

    char k = 'A';
    printf("%d\n", isupperx(k)); // prints 1
    printf("k: %c\n", k);

    printf("%d\n", isupperx(k++)); /*prints 1, increment only once to B because
    of automatic variables the function only gets 'A' and then it's incremented
    after the function call to 'B'

  */
    printf("c: %c\n", c);
    printf("k: %c\n", k);

    return 0;
}