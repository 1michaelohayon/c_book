#include <stdio.h>

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        int val = c - '0';
        if (c != '\n' && c >= '0' && c <= '9')
            printf("\t%d\n", val);
    }
}