#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

int gen(FILE *in, int n, int ch){
	int i;
	double tmp;
	if( ch ){
		for( i = 0; i < n*n; i++ ){
			if( scanf("%lf", &tmp) != 1 )
				return 1;
			fprintf(in, "%.2lf ", tmp);
		}
		return 0;
	}

	else{
		srand(time(NULL));
		for( i = 0; i < n*n; i++ ){
			tmp = (double)rand()/RAND_MAX * 300 - 150;
			fprintf(in, "%.2lf ", tmp);
		}
		return 0;
	}

	return 1;
}

int load(double *A, int n, FILE *in){
	for( int i = 0; i < n*n; i++ )
		if( fscanf(in, "%lf", &A[i]) != 1 )
			return 1;
	return 0;
}

int find_max(double *A, int n, double *max){
	int i, maxi = 0;
	(*max) = A[0];
	for( i = 1; i < n*n; i++ )
		if( A[i] > (*max) ){
			(*max) = A[i];
			maxi = i;
		}
	return maxi;
}

/*int find_col(int n, int maxi){
	9 x 9 matrix
	maxi ~ 33
	which column?
	i.e. when his column starts, and when ends
	maxi % 9 == 6
	0 ... 8 first row
	9 ... 17 second row
	0 1 2 3 4 5 6 7 8
	9 10 11 12 13 14 15 16 17
	18 19 20 21 22 23 24 25 26
	27 28 29 30 31 32 33 34 35
	so column's number is (maxi % 9), numerating from 0
}*/

void imagemax(double *A, int n){
	double max = 0, image = 0;;
	int maxi, i, j;
	maxi = find_max(A, n, &max) % n;
	printf("\nmax is ~ %.2lf, column ~ %d\n", max, maxi+1);
	printf("\nmax's column is:\n");
	for( i = 0; i < n; i++ )
		printf("%.2lf ", A[maxi + i*n]);
	printf("\n");

	printf("\nmatrix's image on max column is:\n");
	for( i = 0; i < n; i++ ){
		for( j = 0; j < n; j++ )
			image += A[i*n + j] * A[j*n + maxi];
		printf("%.2lf ", image);
		image = 0;
	}
	printf("\n\n");
}

int main(){
	int ch = 0, i, j;
	printf("enter order N of square matrix:\n");
	int m, n;
	if( scanf("%d", &n) != 1 || n <= 0 ){
		printf("error: couldn't read N or wrong format\n");
		return -1;
	}

	double *A = (double*)malloc(n*n*sizeof(double));
	if( A == NULL ){
		printf("error: couldn't create A\n");
		return -1;
	}

	printf("type 1 to enter manual matrix, or 0 for random:\n");
	if( scanf("%d", &ch) != 1 || ch > 1 || ch < 0){
		printf("couldn't read choice or wrong format\n");
		free( A );
		return -1;
	}
	if( ch )
		printf("enter %d elements of your matrix:\n", n*n);

	FILE *in = fopen("input.txt", "wt");
	if( in == NULL ){
		printf("error: couldn't create input.txt\n");
		free( A );
		return -1;
	}

	if( gen(in, n, ch) ){
		printf("error: problem with typing elements\n");
		free( A );
		fclose( in );
		return -1;
	}

	fclose( in );
	in = fopen("input.txt", "rt");
	if( in == NULL ){
		printf("error: couldn't open file#2\n");
		free( A );
		return -1;
	}

	if( load(A, n, in) ){
		printf("error: couldn't read file\n");
		fclose( in );
		free( A );
		return -1;
	}
	fclose( in );

	printf("\ninputed matrix:\n");
	for( i = 0; i < n; i++ ){
		for( j = 0; j < n; j ++)
			printf("%.2lf\t", A[i*n + j]);
		printf("\n");
	}

	imagemax(A, n);

	free( A );
	return 0;
}