#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>

int change( int32_t z, int index, int32_t newb ) // z = 0b index1 index2 index3 index4
{
	newb = newb << (4-index)*8;

	if( index == 1 )
	{
		z = z << 8;
		z = z >> 8;
		z = z | newb;
		return 0;		
	}

	if( index == 2 )
	{
		int32_t tmp = z >> 24;
		tmp = tmp << 24;
		z = z << 16;
		z = z >> 16;
		z = z | newb;
		z = z | tmp;
		return 0;
	}

	if( index == 3 )
	{
		int32_t tmp = z << 24;
		tmp = tmp >> 24;
		z = z >> 16;
		z = z << 16;
		z = z | newb;
		z = z | tmp;
		return 0;
	}

	if( index == 4 )
	{
		z = z >> 8;
		z = z << 8;
		z = z | newb;
		return 0;
	}

	else 
		return -1;
}

int main()
{
	int32_t z, newb;
	int index;

	printf( "give me a number and which byte of it you want to change in this format: number index newbyte\n" );
	scanf(" %" SCNi32" %d %" SCNi32" \n", &z, &index, &newb );
	printf("uspeh ~ 0: %d\n", change( z, index, newb ) );

	return 0;
}
