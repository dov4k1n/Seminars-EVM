#include <stdio.h>
#include <stdlib.h>

/*
int random_file( int n )
{
	int d;
	FILE *input;
	input = fopen( "input.txt", "wt" );

	if( input == NULL )
		return -1;

	for( int i = 0; i < n; i++ )
	{
		d = rand() % 1001;
		fprintf( input, "%d ", d ); 
	}

	fclose( input );
	return 0;
}
*/

int read_file( FILE *input, int* a, int n )
{
	for( int i = 0; i < n; i++ )
		fscanf( input, "%d", &a[i] );

	rewind( input );
	return 0;
}

void print_file( FILE *output, int *a, int n )
{
	for( int i = 0; i < n; i++ )
		fprintf( output, "%d ", a[i] );
}

int cmp( const void *a, const void *b )
{
	return *(int*)a - *(int*)b;
}

int check_eq( int *a, int *b, int n )
{
	for( int i = 0; i < n; i++ )
		if( a[i] != b[i] )
			return -1;

	return 0;
}

int insert_sort( int *a, int n )
{
	int clock = 0;

	for( int i = 1; i < n; i++ )
	{
		int j = i;

		while( j > 0 && a[j-1] > a[j] )
		{
			int tmp = a[j-1];
			a[j-1] = a[j];
			a[j] = tmp;
			j -= 1;
			clock++;
		}
	}

	return clock;
}

int quick_sort( int *c, int first, int last, int *clock ) // v nachale first == 0, last == n-1
{
	if( first < last )
	{
		(*clock)++;
		int left = first;
		int right = last;
		int middle = c[ (left + right) / 2 ];

		while( left <= right )
		{
			while( c[left] < middle )
			{
				(*clock)++;
				left++;
			}
			while( c[right] > middle )
			{
				(*clock)++;
				right--;
			}

			if( left <= right )
			{
				(*clock)++;
				int tmp = c[left];
				c[left] = c[right];
				c[right] = tmp;
				left++;
				right--;
			}
		}
		quick_sort( c, first, right, clock );
	       	quick_sort( c, left, last, clock );
	}

	return 0;
}

int main()
{
	int i, n = 0, d = 0, clock = 0;
	FILE *input, *output, *output2;
	int *a, *b, *c;

	// scanf( "%d", &n );
	// if( n <= 0 )
	//	printf("error\n");
	
	input = fopen( "input.txt", "rt" );
	output = fopen( "outputslow.txt", "wt" );
	output2 = fopen( "outputfast.txt", "wt" );

	if( input == NULL || output == NULL || output2 == NULL )
	{
		printf( "couldn't open file\n" );
		return -1;
	}

	while( fscanf( input, "%d", &d ) == 1 )
		n++;

	rewind( input );

	a = ( int* )malloc( n * sizeof( int ) );

	if( a == NULL )
	{
		printf("couldn't create array A\n");
		fclose( input );
		fclose( output );
		fclose( output2 );
		return -1;
	}

	b = ( int* )malloc( n * sizeof( int ) );

	if( b == NULL )
	{
		printf("couldn't create array B\n");
		fclose( input );
		fclose( output );
		fclose( output2 );
		free( a );
		return -1;
	}

	c = ( int* )malloc( n * sizeof( int ) );

	if( c == NULL )
	{
		printf("couldn't create array C\n");
		fclose( input );
		fclose( output );
		fclose( output2 );
		free( a );
		free( b );
		return -1;
	}

	read_file( input, a, n );
	read_file( input, b, n );
	read_file( input, c, n );

	qsort( b, n, sizeof( int ), cmp );
	printf( "slow time is ~ %d\n", insert_sort( a, n ) );
	quick_sort( c, 0, n-1, &clock );
	printf( "fast time is ~ %d\n", clock );
	printf( "slow sort uspeh ~ 0: %d\n", check_eq( a, b, n ) );
	printf( "fast sort uspeh ~ 0: %d\n", check_eq( c, b, n ) );
	print_file( output, a, n );
	print_file( output2, c, n );

	//for( i = 0; i < n; i++ )
	//	printf("b[%d] ~ %d\n", i, b[i] );

	free( a );
	free( b );
	fclose( input );
	fclose( output );
	fclose( output2 );

	return 0;
}
