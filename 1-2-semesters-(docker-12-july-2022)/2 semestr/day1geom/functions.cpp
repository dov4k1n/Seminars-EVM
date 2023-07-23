#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

int load( FILE *in, point *p, int n )
{
	for( int j = 0; j < n; j++ )
		if( fscanf( in, "%lf %lf", &p[j].x, &p[j].y ) != 2 )
		{
			printf("error reading file\n");
			return -1;
		}
	return 0;
}

double magn( point p )
{
	return sqrt( p.x*p.x + p.y*p.y  );
}

double dx( point p1, point p2 )
{
	return p1.x - p2.x;
}

double dy( point p1, point p2 )
{
	return p1.y - p2.y;
}

double dist( point p1, point p2 )
{
	point dd = { dx(p1, p2), dy(p1, p2) };
	return magn( dd );
}

double dotprod( point p1, point p2 )
{
	return p1.x*p2.x + p1.y*p2.y;
}

double det( point p1, point p2, point p0 )
{
	return ( dx(p1, p0) * dy(p2, p0) - dy(p1, p0) * dx(p2, p0)  );
}

double angle( point p1, point p2, point p0 )
{
	point dd1 = { dx(p1, p0), dy(p1, p0) };
	point dd2 = { dx(p2, p0), dy(p2, p0) };

	double cos = dotprod(dd1, dd2) / ( magn(dd1) * magn(dd2) );
	double sin = det(p1, p2, p0) / ( dist(p1, p0) * dist(p2, p0) );
	// printf("%lf\n", sin );

	if( sin < 0 )
		return (-1) * acos( cos );
	else
		return acos( cos );
}

int check( point *p, point p0, int n )
{
	double ANGLE = 0;
	for( int i = 0; i < n; i++ )
	{
		if( i != n-1 )
			ANGLE += angle( p[i], p[i+1], p0 );
		else
			ANGLE += angle( p[i], p[0], p0 );

		printf("angle ~ %lf, i ~ %d\n", ANGLE, i );
	}

	if( fabs( fabs(ANGLE) - 2*M_PI ) < 0.01 )
	       return 1;
	if( fabs( ANGLE ) < 0.01 )
		return 2;
	else
		return -1;
}
