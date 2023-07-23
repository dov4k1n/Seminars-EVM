#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, d;
	FILE *input;
	input = fopen("input.txt", "wt");

	if( input == NULL )
	{
		printf("couldn't open file\n");
		return -1;
	}

	printf("how long file doyou want?\n");
	scanf("%d", &n);

	for( int i = 0; i < n; i++ )
	{
		d = rand() % 1001;
		fprintf( input, "%d ", d );
	}

	fclose( input );
	return 0;
}
