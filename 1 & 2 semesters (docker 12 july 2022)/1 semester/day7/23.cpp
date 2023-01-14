#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int plus1(int *a, int n)
{
	FILE *outputplus;
	int number, i, temp, first, tenpower_n, new_n;
	number = 0;

	outputplus = fopen("outputplus.txt", "wt");
	if( outputplus == NULL )
	{
		printf("error code #1\n");
		return -1;
	}
	
	new_n = n;
	first = a[0];
	if( a[0] < 0 )
		first *= -1;

	for ( i = 0; i < n; i++)
	{
		if( i == 0 )
			number += first*pow(10, n-1);
		else
		{
			int tenpower_nminus;
			tenpower_nminus = pow(10, n-1-i);
			number += a[i]*tenpower_nminus;
		}
	}						// naprimer, dlina 9999 eto 4,
							// 9999 == 9*10^3 + 9*10^2 + 9*10^1 + 9*10^0
	if( a[0] >= 0 )
	{
		number += 1;
		tenpower_n = pow(10, n);
		if( number % tenpower_n != number )	// 9999 % 10,000 == 9999; but (9999+1) % 10,000 == 0;
			new_n += 1;				// (9999+1) % 100,000 == (9999+1) vse ok, TEST na
	}						// uvelichenie dliny, dlina uvelichilas -> nujno uvelichit' n
	if( a[0] < 0 )
	{
		number -= 1; 				// ( -1234 ) + 1 ==  (-1)*( 1234 - 1 )

		tenpower_n = pow(10, n);
		int tenpower_nminus1 = pow(10, n-1);

		if( ( number != 0) && ( number % tenpower_n == number ) && ( number % tenpower_nminus1 == number ) )  
			new_n -= 1;								
	}						// (1000-1) % 10,000 == 999
							// (1000-1) % 1000 == 999
							// but (1234-1) % 10,000 == 1233
							// (1234-1) % 1000 === 233. 
							// dlina ne izmenilas, znachit nado ne menyat' n. 
							// etot TEST kak raz opredelyaet nujno menyat' n ili net	

	for ( i = 0; i < new_n; i++ )
	{
		if( i == 0)
			fprintf( outputplus, "%d ", new_n); // dlina chisla == perviy element massiva po usl
		// eto v tetradke lutshhe ponyatno:
	
		int tenpower_nminusi, tenpower_nminusiminus1;
		tenpower_nminusi = pow(10, new_n-i);
		tenpower_nminusiminus1 = pow(10, new_n-i-1);

		temp = ( ( ( number % tenpower_nminusi ) - ( number % tenpower_nminusiminus1 ) ) / tenpower_nminusiminus1 );

		if( a[0] < 0 && i == 0 )
			fprintf( outputplus, "%d ", -temp);
		else
			fprintf( outputplus, "%d ", temp );
	}
	
	for ( i = 0; i < n; i++ )
	{
		if( i == 0 )
			fprintf( outputplus, "\n~ from initial numbers: %d ", n);
		fprintf( outputplus, "%d ", a[i]);
	}

	fclose( outputplus );
	return 0;
}

int minus1(int *a, int n)
{
	// -1234 - 1 = (-1) * plus1(1234)
	// 1234 - 1 = (-1) * plus1(-1234)
	FILE *outputminus;
	int number, i, temp, first, tenpower_n, new_n, first2;
	number = 0;

	outputminus = fopen("outputminus.txt", "wt");
	if( outputminus == NULL )
	{
		printf("error code #\n");
		return -1;
	}

	new_n = n;
	first2 = (-1) * a[0];	//izmenenie #1
	first = first2;		//izmenenie #2
	if( first2 < 0 )	//izmenenie #3
		first *= -1;
	
	for( i = 0; i < n; i++)
	{
		if( i == 0 )
			number += first*pow(10, n-1);
		else
		{
			int tenpower_nminus;
			tenpower_nminus = pow(10, n-1-i);
			number += a[i]*tenpower_nminus;
		}
	}
	
	if( first2 >= 0 )	//izmenenie #4
	{
		number += 1;
		tenpower_n = pow(10, n);

		if( number % tenpower_n != number )
			new_n += 1;
	}

	if( first2 < 0 )	//izmenenie #5
	{
		number -= 1;
		tenpower_n = pow(10, n);
		int tenpower_nminus1 = pow(10, n-1);

		if( ( number != 0 ) && ( number % tenpower_n == number ) && ( number % tenpower_nminus1 == number ) )
			new_n -= 1;
	}

	for( i = 0; i < new_n; i++ )
	{
		if( i == 0 )
			fprintf( outputminus, "%d ", new_n );

		int tenpower_nminusi, tenpower_nminusiminus1;
		tenpower_nminusi = pow(10, new_n-i);
		tenpower_nminusiminus1 = pow(10, new_n-i-1);

		temp = ( ( ( number % tenpower_nminusi ) - ( number % tenpower_nminusiminus1 ) ) / tenpower_nminusiminus1 );

		if( first2 >= 0 && i == 0 )				//izmenenie #6 i #7
			fprintf( outputminus, "%d ", -temp);
		else
			fprintf( outputminus, "%d ", temp );
	}

	for( i = 0; i < n; i++ )
	{
		if( i == 0 )
			fprintf( outputminus, "\n~from initial numbers: %d ", n);
		fprintf( outputminus, "%d ", a[i]);
	}

	fclose( outputminus );
	return 0;
}

int main()
{
	int i, n;
	FILE *input;
	int *a;
	input = fopen("input.txt", "rt");
	if( input == NULL )
	{
		printf("error code #2\n");
		return -1;
	}

	if( fscanf(input, "%d", &n) != 1 || n <= 0 )
	{
		printf("error code #3 (n ~ %d)\n", n);
		return -1;
	}
	a = (int *)malloc( n * sizeof(int));

	for (i = 0; i < n; i++)
		if ( fscanf(input, "%d", &a[i]) != 1 || ( n > 1 && a[0] == 0 ) || a[i > 0] < 0 )
		{
			printf("error code #4 (a[%d] ~ %d)\n", i, a[i]);
			free( a );
			rewind( input );
			fclose( input );
			return -1;
		}
	rewind( input );
	fclose( input );

	printf("+1 uspeh := 0? ~ %d\n", plus1(a, n));
	printf("-1 uspeh := 0? ~ %d\n", minus1(a, n));

	free( a );
	return 0;
}
