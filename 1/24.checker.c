#include <stdio.h>
#define STACKSIZE 1000

char pop();
void push(char c);

int main()
{
	int result = 0;
	int c;
	while ((c = getchar()) != EOF)
	{

		if (c == '"')
			while ((c = getchar()) != EOF && c != '"')
				;
		else if (c == '\'')
			while ((c = getchar()) != EOF && c != '\'')
				;

		switch (c)
		{
		case '{':
			push('}');
			break;
		case '[':
			push(']');
			break;
		case '(':
			push(')');
			break;
		}

		if (c == '}' || c == ')' || c == ']')
		{
			char popped = pop();
			if (c == popped)
				continue;
			else
			{
				printf("error: expected %c but got %c\n", popped, c);
				result = -1;
				break;
			}
		}
	}
	char last = pop();
	if (last)
	{
		printf("\nerror: expecting %c\n", last);
	}
	else if (result != -1)
		printf("\nlooks good\n");
}

char stack[STACKSIZE];
int len = 100;

void push(char c)
{
	stack[len] = c;
	len++;
}

char pop()
{
	if (len < 1)
	{
		return '\0';
	}
	char val = stack[len - 1];
	len--;
	return val;
}