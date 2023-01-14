#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int plus1(int *a, int n)
{
	int j = 0, flag = 0;
	while( a[j] == 0 )
		j++; // j ~ index pervogo != 0 elementa massiva. eto chtobi neskolko raz mojno bilo primenyat' plus1

	if( a[j] >= 0 && a[n-1] != 9 ) // smotrite skhemu A
	{	
		flag = 1;
		a[n-1] += 1;
		printf("it's skhema A\n");
	}

	if( a[j] < 0 && a[n-1] != 0 && flag == 0 ) // smotrite skhemu B
	{
		flag = 1;
		printf("it's skhema B\n");
		if( j == n - 1 )
			a[n-1] += 1;
		else
			a[n-1] -= 1;
	}

	if( a[j] > 0 && a[n-1] == 9 && flag == 0 )
	{
		flag = 1;
		printf("it's skhema C\n");	// smotrite skhemu C
		for( int i = 0; i < n; i++)
			if( a[n-1-i] >= 9 )
			{
				a[n-1-i] = 0;
				a[n-1-i-1] += 1;

				if( a[n-1-i-1] <= 9 )
					break;
			}
	}

	if( a[j] < 0 && a[n-1] == 0 && flag == 0 )
	{
		flag = 1;
		printf("it's skhema D\n");	// smotrite skhemu D
		for( int i = 0; i < n; i++ )
		{
			if( a[n-1-i] > 0 )
			{
				a[n-1-i] -= 1;
				break;
			}

			if( a[n-1-i] < 0 )
			{
				a[n-1-i] += 1;
				if( a[n-1-i] == 0 )
					a[n-1-i+1] *= -1;
				break;
			}

			if( a[n-1-i] == 0 )
				a[n-1-i] = 9;
		}
	}

	return 0;
}

int minus1(int *a, int n) // chislo - 1 == - ( -chislo + 1 ). menyaem znak pervogo elementa dva raza
{
	int i = 0;

	while( a[i] == 0 )
		i++;
	// teper' i ~ index pervogo != 0 elementa massiva

	a[i] *= -1;
	plus1(a, n);
	i = 0;

	while( a[i] == 0 )
		i++;

	a[i] *= -1;

	return 0;
}

int main()
{
	int i, n;
	FILE *input, *output;
	int *a;
	input = fopen("input.txt", "rt");
	output = fopen("23newoutput.txt", "wt");
	if( input == NULL || output == NULL )
	{
		printf("error: files did not open\n");
		return -1;
	}

	if( fscanf(input, "%d", &n) != 1 || n <= 0 )
	{
		printf("error: wrong format of file (n ~ %d)\n", n);
		return -1;
	}

	n += 1;

	a = (int *)malloc( n * sizeof(int));

	if( a == NULL )
	{
		fclose( input );
		fclose( output );
		printf("error: array could not be created\n");
		return -1;
	}

	a[0] = 0;

	for (i = 1; i < n; i++)
	{
		if ( fscanf(input, "%d", &a[i]) != 1 || ( n > 1 && a[1] == 0 ) || ( a[i] < 0 && i > 1 ) || a[i]*a[i] > 81 )
		{
			printf("error: could not read the file or wrong format (a[%d] ~ %d)\n", i, a[i]);
			free( a );
			rewind( input );
			fclose( input );
			fclose( output );
			return -1;
		}
		printf( "a[%d] ~ %d\n", i, a[i] );
	}

	rewind( input );
	fclose( input );

	printf("+1 uspeh := 0? ~ %d\n", plus1(a, n) );
	//printf("-1 uspeh := 0? ~ %d\n", minus1(a, n) );

	i = 0;
	while( a[i] == 0 )
		i++;

	fprintf( output, "%d ", n - i);
	for( i = i; i < n; i++ )
	{
		printf( "new a[%d] ~ %d\n", i, a[i] );
		fprintf( output, "%d ", a[i] );
	}

	fclose( output );
	free( a );
	return 0;
}
