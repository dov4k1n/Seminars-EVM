#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int destroy( int32_t d ) 
{
	FILE *output;
	output =  fopen( "output.txt", "wt" );
	if( output == NULL )
	{
		printf("can't create file\n");
		return -1;
	}

	int x = 0b11111111;
	char *z;
	z = (char*)malloc( 4 * sizeof(char) );
	if( z = NULL )
	{
		printf("can't destroy array\n");
		return -1;
	}

	for( int i = 0; i < 4; i++ )
	{
		char w = x & d;
		z[i] = w;
		d = d >> 8;
		printf("d ravno %d\n", d );
		fprintf( output, "%hhd ", z[i] );
	}

	printf("%hhd %hhd %hhd %hhd \n", z[0], z[1], z[2], z[3] );

	free( z );
	fclose( output );
	return 0; // poprobyi zapisat' v file, a zatem v build schitat iz faila
}

int32_t build( void )
{
	FILE *input;
	input = fopen( "output.txt", "rt" );
	if( input == NULL )
	{
		printf("can't open file\n");
		return -1;
	}

	char *z;
	z = (char*)malloc( 4 * sizeof(char) );
	if( z == NULL )
	{
		printf("can't build array\n");
		return -1;
	}

	for( int i = 0; i < 4; i++ )
	{
		fscanf( input, "%hhd", &z[i] );
	}
	return (int32_t)z[0] + (int32_t)( z[1] << 8 ) + (int32_t)( z[2] << 16 ) + (int32_t)( z[3] << 24 );
}

int main()
{
	int32_t z;
	printf( "give me a number\n" );
	scanf( "%" SCNi32 "\n", &z );
	
	destroy( z );
	printf( "%" PRIi32 "\n", build() );

	return 0;
}
