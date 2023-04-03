#include <stdio.h>

int main()
{
	int c, i = 0, lim = 1000;
	char str[1000];
	
	enum loop { NO, YES};
	enum loop okloop = YES;
	
	while (okloop == YES)
		if (i >= lim-1)
			okloop = NO;
		else if ((c =getchar()) == '\n')
			okloop = NO;
		else if (c == EOF)
			okloop = NO;
		else {
			str[i] = c;
			++i;
		}	
			

	str[i] = '\0';

	printf("%s\n", str);
}
