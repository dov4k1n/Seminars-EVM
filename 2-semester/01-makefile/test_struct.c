#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point2d
{
	double x, y;
};

typedef struct point2d point;

double magn( point p )
{
	return sqrt( p.x*p.x + p.y*p.y  );
}

double dx( point p1, point p2 )
{
	return (p1.x - p2.x);
}

double dist( point p1, point p2 )
{
	point dd = { dx(p1, p2), p1.y - p2.y };
	return magn(dd);
}

int main()
{
	point p1={1, 2}, p2={3, 4};
	
	printf("p1 ~ %f %f, p2 ~ %f %f\n", p1.x, p1.y, p2.x, p2.y );
	printf("dist ~ %lf\n", dist(p1, p2) );

	return 0;
}
