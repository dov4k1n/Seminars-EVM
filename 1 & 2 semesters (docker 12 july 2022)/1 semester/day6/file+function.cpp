#include <stdio.h>

int ev_incr_sum(FILE *in)
{
	int a, previous, sum;
	sum = 0;
	index = 1;
	b = 1;
	while ( fscanf( in, "%d", &a) == 1 )
	{
		if ( index == 1 )
			previous = a;

		if ( a >= previous )
		{
			if( b != 0 )
			{
				ind1 = index - 1;
			}
			if( a % 2 == 0 )
			{
				sum += a;
				totalsum += a;
			}
			b = 0;
		}
		else
		{
			ind2 = index - 1;
			b = 1;
			if( ind2 != ind1 )
				printf("uchastok %d-%d, sum = %d\n", ind1, ind2, sum);
			else
			{
				sum -= previous;
				totalsum -= previous;
			}
		}

		previous = a;
		index++;
	}
	
	return totalsum;
}

int main()
{

	return 0;
}
