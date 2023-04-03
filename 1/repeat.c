#include <stdio.h>
/* copy input to output; 1*/
int main()
{
	int c;
	c = getchar();
	while ((c = getchar()) != EOF)
	{
		putchar(c);
	}
}

// EOF is - 1,
// ((c = getchar()) != EOF) is 1