#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

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
	return max_len;
}

int main(){
    setlocale(LC_ALL, "Rus");
    /*char str[102] = "";
    printf("Введите строку: ");
    fgets(str, 102, stdin);
    printf("вы ввели: ");
    puts(str);*/	

    /*
    int c, i = 0;
    while( (c = fgetc(stdin)) != EOF ){
        i++;
    }
    printf("i ~ %d\n", i);*/

    int ch, i = 0;
    FILE *in = fopen("test.txt", "rt");
    /*while ( (ch = fgetc(in)) != EOF ){
        i++;
        printf("i ~ %d\n", i);
    }*/

    printf("max len ~ %d\n", maxsize(in));
    fclose( in );
    return 0;
}
