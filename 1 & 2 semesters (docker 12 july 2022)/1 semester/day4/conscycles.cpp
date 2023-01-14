#include <stdio.h>
#include <math.h>

int main()
{
	int n, i, j;
	printf("Salut! Let's come to an agreement: you give me a natural number N, I return to you it's divisors\n");

	if ( scanf("%d", &n) != 1 )
	{
		printf("error\n");
		return -1;
	}

	else
		j = 0;
		for ( i = 1; i <= n; i++ )
		{
			if( !(n%i == 0) )
				continue;
			j++;
			printf("divisor number #%d ~ %d\n", j, i );
		}

	if ( j == 2 )
		printf("You've found a prime number!\n");

	printf("that's all\n");
	return 0;
}
