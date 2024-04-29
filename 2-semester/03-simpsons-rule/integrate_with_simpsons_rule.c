#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f( int m, double x )
{
	if( m == 1 )
		return 5;
	if( m == 2 )
		return x+5;
	if( m == 3 )
		return x*x + 5;
	if( m == 4 )
		return 5*sin(x);
	if( m == 5 )
		return sin(x)*sin(x) + cos(x) + 2;
	return 1;
}

double F( int m, double x)
{
	if( m == 1 )
		return 5*x;
	if( m == 2 )
		return x*x/2 + 5*x;
	if( m == 3 )
		return x*x*x/3 + 5*x;
	if( m == 4 )
		return (-5)*cos(x);
	if( m == 5 )
		return 5*x/2 + sin(x) -sin(2*x)/4;
	return 1;
}

long double simpson( int m, double (*f)(int m, double x), double a, double b, double n )
{
	double d = (b - a) / n;
	long double sum = 0;
	double c = a;
	
	for( int i = 0; i < n; i++ )
	{
		sum += f( m, c ) + 4*f( m, c + d/2 ) + f( m, c + d ) ;
		c += d;
	}
	
	sum *= d / 6;
	return sum;
}

int main()
{
	double a, b;
	int m;

	printf("\nchoose function:\n\n");
	printf("1. 5\n2. x+5\n3. x^2 + 5\n4. 5sinx\n5. (sinx)^2 + cosx + 2\n\n");

	if( scanf("%d", &m) != 1 || m < 1 || m > 5 )
	{
		printf("error: wrong format\n");
		return -1;
	}

	printf("enter segment [a, b]:\n");
	if( scanf("%lf %lf", &a, &b) != 2 || b <= a )
	{
		printf("error: couldn't read A or B, or wrong format\n");
		return -1;
	}
	
	int n = 2;
	long double tmp, tmpI, dif, tmp2n, dif2n;
	// double oldif = 0, oldif2n = 0, acc, acc2n;
	for( int j = 0; j < 16; j++ )
	{
		if( j == 0 )
			tmp = simpson( m, &f, a, b, n );
		else
			tmp = tmp2n;

		tmp2n = simpson( m, &f, a, b, 2*n );
		tmpI = F(m, b) - F(m, a) ;
		dif = fabs( tmp - tmpI );
		dif2n = fabs( tmp - tmp2n );

		//acc = oldif / dif;
		//acc2n = oldif2n / dif2n;
		
		printf("sum ~ %Lf, realsum ~ %Lf, dif of I ~ %Le, dif of I_2n ~ %Le, n ~ %d\n", tmp, tmpI, dif, dif2n, n );
		//printf("acc ~ %lf, acc2n ~ %lf, n ~ %d\n", acc, acc2n, n);
	
		// oldif = dif;
		// oldif2n = dif2n;

		n *= 2;
	}

	return 0;
}
