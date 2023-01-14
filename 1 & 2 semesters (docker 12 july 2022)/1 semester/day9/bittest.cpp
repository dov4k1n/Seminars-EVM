#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main()
{
	/*int a = 0b1111011;
	int b = 0x7b;
	printf("%d, %d\n", a, a + 0b101 );
	printf("%d, %d\n", b, b + 0x11 );
	printf("sixteen ~ %xh, %Xh\n", a, b + 0x11 );
	int d;
	// scanf("%x", &d);
	// printf("%d\n", d);
	scanf("%d", &d);
	printf("decimal ~ %d\n", d);
	printf("binary ~ somedaymaybe\n");
	printf("sixteen ~ %x\n", d);
	printf("eight ~ %o\n", d);
	*/
	
	int32_t x;
	char z;

	x = 7;
	printf("%" PRIi32 " \n", x );
	z = x >> 2;
	printf("%hhd\n", z );
	z = z << 2;
	printf("%hhd\n", z );
	
	return 0;
}
