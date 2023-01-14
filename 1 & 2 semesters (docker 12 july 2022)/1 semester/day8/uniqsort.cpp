#include <stdio.h>
#include <stdlib.h>

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

/*int cmp( const void *a, const void *b )
{
	return *(int*)a - *(int*)b;
}*/

int check_eq( int *a, int n )
{
	for( int j = 0; j < n; j++ )
		for( int i = 1; i < n; i++ )
			if( a[j] % 2 == 0 && a[i] % 2 == 0 && a[j] > a[i] && j <= i )
				return -1;

	return 0;
}

/*int uniqsort( int *a, int n, int firstev, int lastev, int *clock )
{
	if( firstev == lastev odin chetniy element*/ /*|| (firstev == 0 && a[firstev] % 2 != 0) chetnikh net*/ /*
		return 0;

	if( firstev < lastev )
	{
		(*clock)++;
		int left = firstev;
		int right = lastev;
		int mid = (left + right) / 2;
		int middle = a[mid];
		for( int i = 1; i < n/2; i++ )
		{
			if( i == 1 && a[mid] % 2 == 0 )
			{
				(*clock)++;
				break;
			}

			else
			{
				(*clock)++;
				if( a[mid + i] % 2 == 0 )
				{
					middle = a[mid + i];
					break;
				}
				(*clock)++;
				if( a[mid - i] % 2 == 0 )
				{
					middle = a[mid - i];
					break;
				}
			}
		}
		
		while( left <= right )
		{
			while( a[left] < middle )
			{
				(*clock)++;
				left++;
			}
			while( a[right] > middle )
			{
				(*clock)++;
				right--;
			}

			if( left <= right && a[left] % 2 == 0 && a[right] % 2 == 0)
			{
				(*clock)++;
				int tmp = a[left];
				a[left] = a[right];
				a[right] = tmp;
				left++;
				right--;
			}

			else
			{
				left++;
				right--;
			}
		}
		uniqsort( a, n, firstev, right, clock );
		uniqsort( a, n, left, lastev, clock );
	}

	return 0;
}*/

int long_uniqsort( int *a, int n, int *clock )
{
	for( int j = 0; j < n; j++ )
		for( int i = 1; i < n; i++ )
		{
			if( a[j] % 2 == 0 && a[i] % 2 == 0 && j <= i && a[j] >= a[i] )
			{
				(*clock)++;
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}

	return 0;
}

int main()
{
	int i, n = 0, d = 0, clock = 0;
	FILE *input, *output;
	int *a; 

	input = fopen( "input.txt", "rt" );
	output = fopen( "outputuniq.txt", "wt" );

	if( input == NULL || output == NULL )
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
		return -1;
	}

	/*b = ( int* )malloc( n * sizeof( int ) );

	if( b == NULL )
	{
		printf("couldn't create array B\n");
		fclose( input );
		fclose( output );
		free( a );
		return -1;
	}*/

	read_file( input, a, n );
	/*read_file( input, b, n );*/

	/*int firstev = 0;
	int lastev = n - 1;

	for( i = 0; i < n; i++ )
		if( a[i] % 2 == 0 )
		{
			firstev = i;
			break;
		}

	for( i = 0; i < n; i++ )
		if( a[n-1-i] % 2 == 0 )
		{
			lastev = i;
			break;
		}*/

	// qsort( b, n, sizeof( int ), cmp );
	// uniqsort( a, n, firstev, lastev, &clock );

	long_uniqsort( a, n, &clock );

	printf( "sort uspeh ~ 0: %d\n", check_eq( a, n) );
	printf( "time is ~ %d\n", clock );
	print_file( output, a, n );

	//for( i = 0; i < n; i++ )
	//	printf("b[%d] ~ %d\n", i, b[i] );

	free( a );
	// free( b );
	fclose( input );
	fclose( output );

	return 0;
}
