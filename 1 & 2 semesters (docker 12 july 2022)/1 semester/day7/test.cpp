#include <stdio.h>
#include <math.h>

int main()
{
	int n;
	scanf("%d", &n);
	for( int i = 0; i < 4; i++)
	{
		int power_i = pow(2, n-i);
		if( !( power_i*power_i < 512*512 ) )
			printf("power_%d = (2^n-%d) ~ %d\n", i, i, power_i);
		if( i == 2 )
			break;
		printf("%d\n", power_i);
	}
	return 0;
}
