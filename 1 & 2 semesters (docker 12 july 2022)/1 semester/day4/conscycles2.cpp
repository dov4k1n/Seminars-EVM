#include <stdio.h>
#include <math.h>

int main()
{
	printf("Salut! Let's have a look at how close is the sum of first N terms of series 1/n^2 to it's limit PI^2/6. Give me a natural number N\n");
	double sum, i, dif;
	int n;

	while ( scanf("%d", &n) == 1 )
	{
		sum = 0;

		if( n < 0 )
		{
			printf("error\n");
			return -1;
		}

		if( n == 0 )
				break;

		for ( i = 1; i <= n; i++ )
		{
			sum += 1/(i*i);
		}

		dif = sum - pow(M_PI, 2)/6;
		printf ("Sum is ~ %lf. Difference is ~ %lf%%\n", sum,  fabs(dif)*100);

		printf("if you want to finish, enter 0\n");
	}

	return 0;
}
