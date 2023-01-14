#include <stdio.h>

int main()
{
	FILE *in = fopen("./input.txt", "rt");
	if( in == NULL )
	{
		printf("error opening file\n");
		return -1;
	}
	
	int a, max, index, indexmax;
	index = 1;
	while( fscanf( in, "%d", &a) == 1 )
	{
		if ( index == 1 )
			max = a;

		if( a > max )
		{
			max = a;
			indexmax = index; 
		}

		index++;
	}
	fclose( in );

	FILE *ou = fopen("./output.txt", "wt");
	if(ou == NULL)
	{
		printf("can't create\n");
		return -1;
	}
	
	fprintf( ou, "index of maximum ~ %d\n", indexmax);
	fclose( ou );
	return 0;
}
