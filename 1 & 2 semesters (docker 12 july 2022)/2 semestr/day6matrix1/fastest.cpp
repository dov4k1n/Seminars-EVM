#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *a = fopen("test.txt", "wt");
	fprintf(a, "%d", 5);
	fprintf(a, "\n");
	fprintf(a, "%d", 6);
	fclose( a );
	return 0;
}
