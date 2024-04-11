#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x){
	return log( sqrt( 1 + x*x ) );
}

double indef_Taylor(double x){
	return 1/2*( log( x*x + 1 ) - 2 ) + atan(x);
}

double intsimpson(double a, double b, double (*f)(double), int n){
	double d = (b - a) / n;
	double sum = 0;
	double c = a;
	
	for( int i = 0; i < n; i++ ){
		sum += f( c ) + 4*f( c + d/2 ) + f( c + d ) ;
		c += d;
	}
	
	sum *= d / 6;
	return sum;
}

double Int2x_part(double a, double b, double(*f)(double), int n, double delta){
	double I_n = intsimpson(a, b, f, n);
	double I_2n = intsimpson(a, b, f, 2*n);

	while( fabs(I_n - I_2n) > delta ){
		n *= 2;
		I_n = I_2n;
		I_2n = intsimpson(a, b, f, 2*n);
	}

	return I_2n;
}
//searching root in this segment
double find_segment(double alpha, double(*f)(double), double delta, double *a, double *b, int n){
	double S = 0, S_prev = 0;
	*b = 4*delta,
	*a = epsilon;
	S = Int2x_part(*a, *b, f, n, delta);

	do{
		*a = *b;
		*b *= 2;
		S_prev = S;
		S += Int2x_part(*a, *b, f, n, delta);
	}
	while( S < alpha );

	return S_prev;
}

double rootnewt(double a, double b, double alpha, double (*f)(double), double S, double delta, int n){
	double middle_point, a_left = a;
	double I_a, I_m;

	double left_integral = indef_Taylor(epsilon); //integral f(x) from 0 to epsilon

	S -= (alpha - left_integral);

	while(b - a > delta){
		I_a = S + Int2x_part(a_left, a, f, n, delta);

		middle_point = (a+b)/2;
		I_m = S + Int2x_part(a_left, middle_point, f, n, delta);

		if(I_a*I_m <= 0)
			b=middle_point;
		else
			a=middle_point;
	}
	return fabs(a+b)/2;
}

int main(){
	double delta, alpha, a_x, b_x, S, x;
	int n = 32;
	printf("enter alpha:\n");
	if( scanf("%lf", &alpha) != 1 ){
		printf("Incorrect input data\n");
		return -1;
	}

	printf("enter delta:\n");
	if( scanf("%lf", &delta) != 1 ){
		printf("Incorrect input data\n");
		return -1;
	}

	S = segment_finder(alpha, f, delta*0.01, &a_x, &b_x, n);
	x = root_finder(a_x, b_x, alpha, f, S, delta, n);
	printf("Answer of integral equation: %lf\n", x);

	return 0;
}


// printf("root - I_2n ~ %e\n", x0 - getclose(0, x0, f));