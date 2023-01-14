#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int oversize(FILE *in){
	int ch = fgetc(in), tmp_len = 0;
	while( isprint(ch) ){
		tmp_len++;
		ch = fgetc(in);
	}
	rewind(in);
	if( tmp_len == 0 )
		return -1;
	return tmp_len;
}

/*int somesize(in){
	int ch = fgetc(in), tmp_len = 0;
	
	while( (ch = fgetc(in)) != EOF ){
		while( !isspace(ch) ){
			tmp_len++;
			ch = fgetc(in);
		}
		if( tmp_len > 0 )
			break;
	}

	rewind(in);
	if( tmp_len == 0 )
		return -1;
	return tmp_len;
}*/

int minsize(FILE *in){
	int min_len = oversize(in);
	char tmp[min_len+1], min[min_len+1];

	while( fscanf(in, "%s", tmp) == 1 )
		if( strlen(tmp) < min_len ){
			min_len = strlen(tmp);
			strcpy(min, tmp);
		}
	rewind(in);
	printf("min ~ %s\n", min);
	return min_len;
}

int maxsize(FILE *in){
	int tmp_len = oversize(in), max_len = minsize(in);
	char tmp[tmp_len+1], max[tmp_len+1];

	while( fscanf(in, "%s", tmp) == 1 )
		if( strlen(tmp) > max_len ){
			max_len = strlen(tmp);
			strcpy(max, tmp);
		}
	rewind(in);
	printf("max ~ %s\n", max);
	return max_len;
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

	int over = oversize(in);
	if( over == -1 ){
		printf("error: incorrect file\n");
		fclose(in);
		return -1;
	}

	char *minw = (char*)malloc(over*sizeof(char));
	if( minw == NULL ){
		printf("error: couldn't create minw\n");
		fclose(in);
		return -1;
	}

	char *maxw = (char*)malloc(over*sizeof(char));
	if( maxw == NULL ){
		printf("error: couldn't create maxw\n");
		free(minw);
		fclose(in);
		return -1;
	}

	int min = minsize(in, minw), max = maxsize(in, maxw);
	
	printf("over ~ %d, min ~ %d, max ~ %d\n", over, min, max);
	fclose(in);
	return 0;
}


int mymin(int a, int b){
	if( a > b)
		return b;
	else
		return a;
}

int mystr_comp(const void *a,const void *b){
	char const *aa = *(char const **)a;	
	char const *bb = *(char const **)b;	
	return strncmp( aa, bb, mymin( strlen(aa), strlen(bb) ) );
}

int sortme(FILE *in, FILE *out){
	int i, j, n = countwords(in), maxs = maxsize(in);
	char **buf=(char **)malloc(n*sizeof(char *));
	if( buf == NULL )
		return 1;

	for( i = 0; i < n; i++ ){
		buf[i] = (char *)malloc(maxs*sizeof(char));
		if( buf[i] == NULL ){
			for( j = 0; j < i; j++ )
				free(buf[j]);
			free(buf)
			return 1;
		}

		if( fscanf(in, "%s", buf[i]) != 1 ){
			for( j = 0; j < i; j++ )
				free(buf[j]);
			free(buf);
			return 1;
		}
	}

	qsort(buf, n, sizeof(buf[0]), mystr_comp);
	
	for( i = 0 ; i < n; i++ )
		fprintf(out, "%s", buf[i]);

	for( i = 0; i < n; i++ )
		free(buf[i]);
	free(buf);
	return 0;
}