#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// а) 4 - вывести номера строк исходного файла и номер позиции 
// в строке, где встречается заданное слово

int compare(int n, char *a, char *b){
	for( int i = 0; i < n; i++ )
		if( a[i] != b[i] )
			return 0;
	return 1;
}

int len(char *a){
	int i = 0;
	while( a[i] != '\0' )
		i++;
	return i;
}

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
	char *word = (char*)malloc(maxs*sizeof(char));
	char *tmpw = (char*)malloc(maxs*sizeof(char));

	//  scanf("%s", word) != 1
	printf("enter the word you want to find:\n");
	if( fgets(word, maxs, stdin) == NULL || len(word)-1 > maxs || len(word)-1 == 0 ){
		printf("error: couldn't read your word or wrong format\n");
		fclose(in);
		free(word);
		free(tmpw);
		return -1;
	}
	
	int i = 1, j = 1, wrd_len, tmp_len, ch, check2;
	wrd_len = len(word) - 1;
	
	if( wrd_len == 1 ){
		printf("enter the same again:\n");
		check2 = fgetc(stdin);
		if( isspace(check2) ){
			printf("incorrect input\n");
			fclose(in);
			free(word);
			free(tmpw);
			return -1;
		}
	}

	printf("word len ~ %d\n", wrd_len);
	while( fscanf(in, "%s", tmpw) == 1 ){
		tmp_len = len(tmpw);
		if( (tmp_len >= wrd_len) && compare(wrd_len, word, tmpw) )
			printf("Row %d, column %d\n", i, j);
		ch = fgetc(in);
		j += tmp_len;
		//printf("j ~ %d ", j);
		while( isspace(ch) ){
			if( ch == '\n' ){
				i++;
				j = 1;
			}
			j++;
			ch = fgetc(in);
		}
		ungetc(ch, in);
	}

	fclose(in);
	free(word);
	free(tmpw);
	return 0;
}