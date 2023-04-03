#include <stdio.h>

main()
{
	int c;

	while ((c = getchar()) != EOF) // while not in the of the line c = input
	{
		if (c == ' ') // if c is blank
		{
			putchar(c); // record input
			while ((c = getchar()) == ' ')
				; // enter infinite loop until the next input is not blank
		}
		putchar(c); // record input
	}
}