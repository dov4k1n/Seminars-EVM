#include <stdio.h>
#include <stdlib.h>

int main(){
	int a, *b;
	a = 5;
	b = &a;

	(*b) = 3;
	printf("a ~ %d\n", a);
	return 0;
}
