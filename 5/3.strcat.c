#include <stdio.h>
#include <string.h>

void strcatx(char *s, char *t) {
	while(*s)
    s++;
  while((*s++ = *t++))
    ;
}


int main(){
	char s[20] = "hello ";
	char s2[] = "world";


	printf("%s, %s\n", s, s2);
	strcatx(s, s2);
	printf("%s, %s\n", s, s2);
	return 0;
}
