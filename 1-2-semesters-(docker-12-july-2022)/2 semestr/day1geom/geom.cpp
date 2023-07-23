#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

void check2( int c )
{
	if( c == 1 )
		printf("inside\n");
	if( c == 2 )
		printf("outside\n");
	if( c == -1 )
		printf("on the boundary\n");
}

int main()
{
	int n;
	point *p, p0;

	printf("enter number of vertices:\n");
	if( scanf("%d", &n) != 1 || n <= 0 )
	{
		printf("error: couldn't read n or wrong format\n");
		return -1;
	}

	FILE *in = fopen("input.txt", "rt");
	if( in == NULL )
	{
		printf("error: couldn't open file input.txt\n");
		return -1;
	}

	p = (point*)malloc( n * sizeof(point) );
	if( p == NULL )
	{
		printf("error: couldn't create p malloc\n");
		fclose ( in );
		return -1;
	}

	load( in, p, n );
	
	int j = 1;
	int c;
	while ( j == 1 )
	{
		printf("enter coordinates of a point that you want to check:\n");
		if( scanf("%lf %lf", &p0.x, &p0.y) != 2 )
		{
			printf("error: couldn't read x or y\n");
			free( p );
			fclose( in );		
			return -1;
		}

		c = check( p, p0, n );
		
		check2( c );

		printf("\ntype 1 if you want to continue checking points\n");

		if( scanf("%d", &j) != 1 )
		{
			printf("error: couldn't read j\n");
			free( p );
			fclose( in );
			return -1;
		}

		if( j != 1 )
			break;
	}

	free( p );
	fclose( in );
	return 0;
}
