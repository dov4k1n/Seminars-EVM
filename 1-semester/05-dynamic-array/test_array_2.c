#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a[4]={-1, 2, -3, 4};
	for( int i = 0; i < 4; i++)
		if( a[i > 0] > 0 )
			printf("a[%d] ~ %d - prosto\n", i, a[i]);
	return 0;
}
