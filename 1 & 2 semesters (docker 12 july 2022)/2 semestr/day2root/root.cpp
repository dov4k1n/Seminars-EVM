#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f( int n, double x )
{
	if( n == 1 )
		return x*x + 55*x + 250;
	if( n == 2 )
		return exp(x+5) - 1;
	if( n == 3 )
		return (1/pow(10,7))*(pow(x,6)) + x - 10;
	return 1;
}

double fd ( int n, double x )
{
	if( n == 1 )
		return 2*x + 55;
	if( n == 2 )
		return exp(x+5);
	if( n == 3 )
		return (6/pow(10,7))*(pow(x,5)) + 1;
	return 1;
}

double newton( int *time, int n, double (*f)( int n, double x ), double a, double b, double eps )
{
	double x1, x2, x3;

	if( f(n, a)*f(n, b) > 0 )
	{
		printf("wrong segment\n");
		return -1;
	}

	if( f(n, b)*fd(n, b) > 0 )
		x1 = b;
	else
		x1 = a;

	while (true)
	{
		(*time)++;
		x2 = x1 - f(n, x1) / fd(n, x1);
		x3 = x2 - f(n, x2) / fd(n, x2);

		if( fabs(x3 - x2) < eps ) // Cauchy's criterion
			break;

		x1 = x3;
	}
	//printf("time ~ %d\n", time);
	return x3;
}

int main()
{
	int n;
	int time = 0;
	double a, b, eps;

	printf("Finding root by Newton's method, choose function:\n");
	printf("1. x^2 + 55x + 250\n2. e^(x+5)-1\n3. (1/10^7)*x^6 + x - 10\n");
	
	if( scanf("%d", &n) != 1  || n < 1 || n > 3 )
	{
		printf("couldn't choose function\n");
		return -1;
	}

	printf("Choose segment [a, b]:\n");	
	if( scanf("%lf", &a) != 1 )
	{
		printf("error inputing segment A\n");
		return -1;
	}
	if( scanf("%lf", &b) != 1 || b <= a ) 
	{
		printf("error inputing segment B\n");
		return -1;
	}

	printf("enter epsilon:\n");
	if( scanf("%lf", &eps) != 1 || eps < 0 )
	{
		printf("error inputing epsilon\n");
		return -1;
	}

	printf("root ~ %lf\n", newton( &time, n, &f, a, b, eps ) );
	printf("time ~ %d\n", time );
	return 0;
}
