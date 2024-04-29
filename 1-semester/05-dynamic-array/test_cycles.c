#include <stdio.h>

int main()
{
	for( int i = 0; i < 5; i++ )
	{
		if( i == 0 )
			printf("first i ~ %d\n", i);
		else
			printf("i ~ %d\n", i);
		printf("bla bla\n");
	}
	return 0;
}
