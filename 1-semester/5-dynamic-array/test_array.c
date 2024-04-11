#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	scanf("%d", &n);
	int *a;
	a = (int *)malloc( n * sizeof(int) );

	for( int i = 0; i < n; i++ )
		scanf("%d", &a[i]);
	printf("a ~ %p\n", a);
	printf("a ~ %p\n", a);
	for( int i=0; i < n-1; i++ )
		printf("%d\n", a[i+1]);

	free(a);
	return 0;
}
