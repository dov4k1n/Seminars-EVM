#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps 0.00001

double f(double x){
	return log( sqrt( 1 + x*x ) );
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

double getclose(double a, double b, double (*f)(double x)){
    double epsilon = eps;
    double I_n = 2 * epsilon, I_2n = 0;
    int n = 1, it = 0;

    while ( fabs(I_n - I_2n) > epsilon ){
            I_n = intsimpson(a, b, f, n);
            n *= 2;
            I_2n = intsimpson(a, b, f, n);
            it += 1;
    }
    return I_2n;
}

double add_integral(double alpha, double(*f)(double x), double delta, double &a, double &b){
    double S = 0, sum_prev = 0, a_i , b_i;
    b = 2 * delta;
    a = 0;
	b_i = 2 * delta;
    a_i = 0; 
	
    sum_prev = getclose(a_i, b_i, f);

    while ( sum_prev < alpha ){
		a_i = b;
        b_i *= 2;
        sum_prev += getclose(a_i, b_i, f);
        if ( sum_prev < alpha ){
            S = sum_prev;
            a = a_i;
            b = b_i;
        }
        a = b;
        b = b_i;
    }
	printf("S ~ %lf\n", S);
    return S;
}

double int_div(double a, double b, double alpha, double (*f)(double), double S, double delta)
{
    double c, a_l = a;
    double x1, x2, x3;
    S -= alpha;
    while (b - a > eps){
        x1 = S + getclose(a_l, a, f);
        x2 = S + getclose(a_l, b, f);
        c = (a + b) / 2;
        x3 = S + getclose(a_l, c, f);

        if (x3 == 0)
            return c;

    	if (x1 * x3 < 0)
            b = c;
        else
        	a = c;
    }
    return (a + b) / 2;
}

int main(){
    double delta, alpha, a, b, S, x0;

    printf("enter alpha:\n");
    if ( scanf("%lf", &alpha) != 1 ){
        printf("error: incorrect alpha\n");
        return -1;
    }
    printf("enter acurracy:\n");
    if ( scanf("%lf", &delta) != 1 ){
        printf("error: incorrect delta\n");
        return -1;
    }

    S = add_integral(alpha, f, delta, a, b);
    x0 = int_div(a, b, alpha, f, S, delta);
    printf("root of integral equation: %lf\n", x0);
    return 0;
}