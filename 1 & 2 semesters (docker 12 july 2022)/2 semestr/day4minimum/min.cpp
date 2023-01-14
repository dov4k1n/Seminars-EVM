#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double my2min( double x, double y )
{
	if( x < y )
		return x;
	else
		return y;
}

/*double my3min( double x, double y, double z )
{
	if( x < my2min( y, z) )
		return x;
	else
		return my2min( y, z );
}*/

double f( int m, double x )
{
	if( m == 1 )
		return 10*sin(x)*sin(x) + cos(x) + 2;
	if( m == 2 )
		return (1/pow(10,7))*pow(x,6) + x - 10;
	if( m == 4 )
		return cos(3*x*M_PI)/2 + cos(9*x*M_PI)/4 + cos(27*x*M_PI)/8 + cos(81*x*M_PI)/16;
	if( m == 3 )
		return x*x + 55*x + 250;
	else
		return 1;
}

double minevnly( int m, double (*f)(int m, double x), double a, double b, int n, int it, int *count )
{
	double h;
	double ym, xm, xi; // starting with a+h, because otherwise method's not working
	
	for( int j = 0; j < it; j++ )
	{
		h = (b - a) / n;
		if( j == 0 )
		{
			ym = f( m, a+h );
			xm = a+h;
		}

		for( int i = 2; i < n; i++ )
		{
			(*count)++;
			xi = a + i*h;
			if( f( m, xi ) < ym )
			{
				ym = f( m, xi ); 
				xm = xi;
			}
		}
		
		//if( f(m,a) < ym || f(m,b) < ym ) 
		//	return my2min( f(m,a), f(m,b) );

		a = xm - h;
		b = xm + h;
	}

	double xl = xm - h, xr = xm + h;
	double yl = f( m, xl ), yr = f( m, xr );

	double ap = (yr - ( xr*(ym - yl) + xm*yl - xl*ym )/(xm - xl)) / (xr*(xr - xl - xm) + xl*xm );
	double bp = ((ym - yl)/(xm - xl)) - ap*(xl + xm);
	double cp = (xm*yl - xl*ym)/(xm - xl) + ap*xl*xm;
	double z = (-1)*bp/(2*ap);

	//return ap*z*z + bp*z + cp;
	return (a+b)/2;
}

int main()
{
	double a, b;
	int m, n, it, count = 0;

	printf("choose function:\n");
	printf("1. 10(sinx)^2 + cosx + 2\n2. (x^6)/10^7 + x - 10\n3. x^2 + 55x + 250\n");
	printf("4. cos(3pix)/2 + cos(9pix)/4 + cos(27pix)/8 + cos(81pix)/16\n");
	if( scanf("%d", &m ) != 1 || m < 1 || m > 4 )
	{
		printf("error bro\n");
		return -1;
	}

	printf("enter segment [a, b]:\n");
	if( scanf("%lf %lf", &a, &b) != 2 || b <= a )
	{
		printf("error bro\n");
		return -1;
	}
	printf("enter number of iterations:\n");
	if( scanf("%d", &it) != 1 )
	{
		printf("error bro\n");
		return -1;
	}

	n = 2; 
	double z;
	double xmin = 0;
	if( scanf("%lf", &xmin) != 1 ){
		printf("error reading xmin\n");
		return -1;
	}

	for( int i = 0; i < 16; i++ )
	{
		z = minevnly( m, &f, a, b, n, it, &count);
		printf("x minimum ~ %lf, dif ~ %e, count ~ %d, n ~ %d\n", z, fabs( z - xmin ), count, n );
		n *= 2;
	}

	return 0;
}
