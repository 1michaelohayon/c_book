#include <stdio.h>

int strend(char *s, char *t) {
    char *bs = s;
    char *bt = t;

    while (*s)
        s++;
    while (*t)
        t++;
    for (; *s == *t; s--, t--)
        if (t == bt || s == bs)
            break;

    return (*s == *t && t == bt && *s != '\0');
}

// return 1 if string t occurs at end of string s
// int strend(char *s, char *t) {
//	int i = 1;
//	while(*t) {
//		t++;
//		i++;
//	}
//  while(*s)
//    s++;
//	while (--i)
//		if (*s-- != *t--)
//			return 0;
//	return i == 0 && *s == *t;
//}

int main() {
    char s[] = "hello world";
    char t[] = "world";

    printf("%d\n", strend(s, t));
}
