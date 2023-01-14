#include <stdio.h>
#include <stdlib.h>

int func1( int n )
{
	if( n < 0 )
	{
		printf("error #1\n");
		return -1;
	}
	return ( n + 5 );
}

int func2( int n )
{
	if( n < 0 )
	{
		printf("error #2\n");
		return -1;
	}
	return 10*func1( n );
}

int main()
{
	int n;
	scanf("%d", &n);
	printf("func1 uspeh ~ %d, func2 ~ %d\n", func1( n ), func2( n ));

	return 0;
}
