#include <stdio.h>

int ev_incr_sum( FILE *in )
{
	int a, b, index, previous, sum;
	index = 1;
	sum = 0;
	b = 28529436;

	while ( fscanf( in, "%d", &a) == 1 )
	{
		if( index == 1 )
			previous = a;
		if( index > 1 && previous % 2 == 0 && a > previous && b != previous )
			sum += previous; // eto chtobi posledovatelnosti tipa {2, 4}, {2, 2, 4} norm obrabotalis'
					 // "b != previous" - chtobi ne poschitat' dva raza v {2, 4, 6}
		if( a % 2 == 0 && a > previous )
		{
			sum += a;
			b = a;
		}
		previous = a;
		index++;
	}
	return sum;
}

int main()
{
	FILE *in = fopen("input.txt", "rt");
	if( in == NULL )
		return -1;
	printf("Sum of even increasing elements ~ %d\n", ev_incr_sum( in ) );
	fclose( in );

	return 0;

}
