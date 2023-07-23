#include <stdio.h>

int main()
{
	int n;
	printf("give your number\n");
	scanf("%d", &n);
	printf("you do task #%d\n", 1+((5*n+7)%30) );
	return 0;
}
