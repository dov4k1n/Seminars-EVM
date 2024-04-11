#include <stdio.h>
#include <stdlib.h>

int main(){
	int *a, *b, c, d;
	c = 1;
	d = 3;

	a = &c;
	(*a) = 5 + 5;
	b = &d;

	printf("%ld, a ~ %p, b ~ %p\n", a-b, a, b);

	return 0;
}
