#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "interfuns.h"

int main(){
	point *p;
	int m, n;
	double (*f)(double x);

	printf("choose fun:\n");
	printf("1. 10(sinx)^2 + cosx + 2\n2. (x^6)/10^7 + x - 10\n3. x^2 + 55x + 250\n");
	printf("4. cos(3pix)/2 + cos(9pix)/4 + cos(27pix)/8 + cos(81pix)/16\n5. 5\n6. 10x\n");
	
	if( scanf("%d", &m ) != 1 || m < 1 || m > 6 ){
		printf("error choosing fun\n");
		return -1;
	}

	choose(&f, m);
	
	printf("enter number of points:\n");
	if( scanf("%d", &n) != 1 ){
		printf("error reading n\n");
		return -1;
	}
	
	p = (point*)malloc(n*sizeof(point));
	if( p == NULL ){
		printf("error creating p\n");
		return -1;
	}

	FILE *in = fopen("input.txt", "wt");
	if( in == NULL ){
		printf("error opening file\n");
		free( p );
		return -1;
	}

	getpoints(m, f, in, n);
	rewind( in );
	fclose( in );

	in = fopen("input.txt", "rt");
	if( in == NULL ){
		printf("error opening file#2\n");
		return -1;
	}

	load(p, in, n);
	fclose( in );
	
	double xl, iv, rv, yl;
	for( int l = 0; l < n-1; l++ ){
		xl = ( p[l].x + p[l+1].x ) / 2 ;
		iv = piecewiselinear(p, n, xl);
		rv = f(xl);
		yl = (p[l].y + p[l+1].y )/2;
		printf("interpol value ~ %lf, real value ~ %lf, ", iv, rv);
		printf("difference ~ %e, point#%d ~ %lf\n", fabs( rv - yl ), l, xl);
	}
	
	free( p );
	return 0;
}
