typedef struct point
{
	double x, y;
} point;

int load( FILE *in, point *p, int n );
double magn( point p );
double dx( point p1, point p2 );
double dy( point p1, point p2 );
double dist( point p1, point p2 );
double dotprod( point p1, point p2 );
double det( point p1, point p2, point p0 );
double angle( point p1, point p2, point p0 );
int check( point *p, point p0, int n );
