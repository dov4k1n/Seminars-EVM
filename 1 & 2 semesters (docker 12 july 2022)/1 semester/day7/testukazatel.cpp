#include <stdio.h>

int func1()
{
	int a = 0;
	return a + 100;
}

int func2()
{
	int *b;
	b =& a;
	b = 100;
	return func1;
}

int main()
{
	printf("%d %d\n", func1, func2);
	return 0;
}
