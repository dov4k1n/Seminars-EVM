#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// б) 5 - определить максимальную, минимальную и среднюю длину слов из данного файла
int maxsize(FILE *in){
	int ch, tmp_len = 0, max_len = 0;
	while ( (ch = fgetc(in)) != EOF ){
		while( !isspace(ch) ){
        	tmp_len++;
			ch = fgetc(in);
		}

		if( max_len < tmp_len )
        	max_len = tmp_len;
		tmp_len = 0;
	}
	rewind(in);
	return max_len;
}

int minsize(FILE *in){
	int min_len = maxsize(in);
	char tmp[min_len], min[min_len];

	while( fscanf(in, "%s", tmp) == 1 )
		if( strlen(tmp) < min_len ){
			min_len = strlen(tmp);
			strcpy(min, tmp);
		}
	rewind(in);
	return min_len;
}

void mm_Word(FILE *in, char *m_wrd, int m_len){
	int i;
	char tmp[maxsize(in)], m_w[m_len];

	while( fscanf(in, "%s", tmp) == 1 )
		if( strlen(tmp) == m_len )
			strcpy(m_w, tmp);

	for( i = 0; i < m_len; i++ )
		m_wrd[i] = m_w[i];

	rewind(in);
}

int countwords(FILE *in){
	int i = 0;
	char tmp[maxsize(in)];
	while( fscanf(in, "%s", tmp) == 1 )
		i++;
	rewind(in);
	return i;
}

int cmp( const void *a, const void *b )
{
	return *(int*)a - *(int*)b;
}

int findmedlen(FILE *in){
	int i, n = countwords(in), maxs = maxsize(in);
	char tmp[maxs];
	int *a = (int*)malloc(n*sizeof(int));
	if( a == NULL )
		return -1;
	
	for( i = 0; i < n; i++ ){
		if( fscanf(in, "%s", tmp) != 1 ){
			free(a);
			return -1;
		}
		a[i] = strlen(tmp);
	}

	qsort( a, n, sizeof(int), cmp );
	int ind;
	if( n % 2 == 1 )
		ind = a[(n-1)/2 + 1];
	else
		ind = a[n/2];
	free(a);
	rewind(in);
	return ind;
}

int main(int argc, const char **argv){
	if( argc != 2 ){
		printf("error: incorrect argc\n");
		return -1;
	}

	FILE *in = fopen(argv[1], "rt");
	
	if( in == NULL ){
		printf("error: can't open input file\n");
		return -1;
	}

	int maxs = maxsize(in);
	if( !maxs ){
		printf("error: incorrect file\n");
		fclose(in);
		return -1;
	}

	int min_l = minsize(in), max_l = maxsize(in);

	int medlen = findmedlen(in);
	if( medlen == -1 ){
		printf("error in medlen fun\n");
		fclose(in);
		return -1;
	}

	char *max_w = (char*)malloc(max_l*sizeof(char));
	char *min_w = (char*)malloc(min_l*sizeof(char));
	
	mm_Word(in, max_w, max_l);
	mm_Word(in, min_w, min_l);

	printf("min w ~ %s (%d)\n", min_w, min_l);
	printf("max w ~ %s (%d)\n", max_w, max_l);
	printf("median w length ~ %d\n", medlen);

	free(max_w);
	free(min_w);
	fclose(in);
	return 0;
}
