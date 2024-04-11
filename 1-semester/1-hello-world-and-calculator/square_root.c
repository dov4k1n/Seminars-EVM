#include <stdio.h>
#include <math.h>

int main()
{
	printf("Pi equals ~ %lf\n", M_PI );
	printf("Hello! Enter some real number, I will give you it's square root\n");
	float a;
	scanf("%f", &a);
	printf("value ~ %f\n", sqrt(a) );
	return 0;
}
