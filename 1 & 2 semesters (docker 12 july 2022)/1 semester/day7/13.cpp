#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int polusumma( double *a, int n )
{
	double first = a[0], last = a[n-1];

	FILE *output;
	output = fopen("output13.txt", "wt");
	if( output == NULL )
	{
		printf("error code #3\n");
		return -1;
	}

	fprintf( output, "%lf ", a[0] );
	for( int i = 1; i < n-1; i++ )
			fprintf( output, "%lf ", ( a[i-1] + a[i+1] ) / 2 );
	fprintf( output, "%lf ~ from initial numbers: ", a[n-1] );

	for( int i = 0; i < n; i++ )
		fprintf( output, "%lf ", a[i] );
	
	fclose( output );
	return 0;
}

int main()
{
	int n;
	double temp, *a;
	n = 0;

	FILE *input;
	input = fopen("input13.txt", "rt");
	if( input == NULL )
	{
		printf("error code #1\n");
		return -1;
	}

	while( fscanf(input, "%lf", &temp) == 1 )
		n++;
	rewind( input );
	a = (double *)malloc( n * sizeof(double) );

	for( int i = 0; i < n; i++ )
		if( fscanf( input, "%lf", &a[i] ) != 1 )
		{
			printf("error code #2 (i ~ %d)\n", i);
			free( a );
			rewind( input );
			fclose( input );
			return -1;
		}

	rewind( input );
	fclose( input );

	polusumma( a, n);

	free( a );
	return 0;
}
