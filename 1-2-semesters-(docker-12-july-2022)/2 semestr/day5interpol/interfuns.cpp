#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "interfuns.h"

double f1(double x){
	return 10*sin(x)*sin(x) + cos(x) + 2;
}

double f2(double x){
	return (1/pow(10, 7))*pow(x,6) + x - 10;
}

double f3(double x){
	return x*x + 55*x + 250;
}

double f4(double x){
	return cos(3*x*M_PI)/2 + cos(9*x*M_PI)/4 + cos(27*x*M_PI)/8 + cos(81*x*M_PI)/16;
}

double f5(double x){
	return 5;
}

double f6(double x){
	return 8*x;
}

void choose(double (**f)(double x), int m){
	if(m == 1)
		*f=f1;
	if(m == 2)
		*f=f2;
	if(m == 3)
		*f=f3;
	if(m == 4)
		*f=f4;
	if(m == 5)
		*f=f5;
	if(m == 6)
		*f=f6;
}

void getpoints(int m, double(*f)(double x), FILE *out, int n){
	srand(time(NULL));
	double xj = -50;
	//double xj = (double)rand()/RAND_MAX * 300 - 150;
	//double d = (double)rand()/RAND_MAX * 10;
	double d = 10;

	for( int j = 0; j < n; j++ ){
		fprintf(out, "%lf %lf ", xj, f(xj));
		xj += d;
	}
}

void load(point *p, FILE *in, int n){
	for( int k = 0; k < n; k++ )
		if( fscanf(in, "%lf %lf", &p[k].x, &p[k].y) != 2 )
			printf("error loading points\n");
}

double piecewiselinear(point *p, int n, double x){
	double x1 = p[0].x;
	double x2 = p[n-1].x;
	int i1 = 0, i2 = n-1;

	// need to find an interval first, then use interpolation formula
	for( int i = 1; i < n-1; i++ )
		 if( p[i].x <= x2 && p[i].x >= x1 ){
			 if( x == p[i].x )
				 return p[i].y;
			 if( p[i].x < x ){
				 x1 = p[i].x;
				 i1 = i;
			 }
			 if( p[i].x > x ){
				 x2 = p[i].x;
				 i2 = i;
			 }
		 }
	//printf("x1 ~ %lf, x2 ~ %lf, i1 ~ %d, i2 ~ %d, y1 ~ %lf, y2 ~ %lf\n", x1, x2, i1, i2, p[i1].y, p[i2].y);	
	return p[i1].y * (x - x2)/(x1 - x2) + p[i2].y * (x - x1)/(x2 - x1);
}
