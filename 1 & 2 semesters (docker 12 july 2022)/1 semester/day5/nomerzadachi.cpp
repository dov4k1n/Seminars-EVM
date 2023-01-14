#include <stdio.h>

int main()
{
	int nomer, n;
	if( scanf("%d", &n) == 0 )
	{
		printf("error\n");
		return -1;
	}
	nomer = 1 + ((7*n + 3)%30);
	printf("nomer zadachi ~ %d\n", nomer);
	return 0;
}
