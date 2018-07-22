//Escriba un programa ISO C que procese el archivo de números datos.txt sobre sí mismo. 
//El procesamiento consite en convertir los números encontrados (de 1 o más cifras decimales) a octal.
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 64
#define FILE_NAME data.txt

void reverse(char * pal){
	int len = strlen(pal);
	char tmp[len];
	strncpy(tmp, pal, len);
	int j = len-1;
	for(int i = 0; i < len ; i++){
		pal[i] = tmp[j];
		j--;
	}
}

char * to_octal(long num){
	char * octal = (char *) malloc(sizeof(char)*SIZE);
	int i = 0;
	long x = num;
	while(x > 0){
		octal[i++] =  (x % 8) +'0';
		x = x/8;
	}
	octal[i++] = 0;
	reverse(octal);
	return octal;
}

int get_offset(FILE *file, int *file_size){
	int i = 0;
	char buffer[SIZE];
	memset(buffer, 0,SIZE);
	int c = 0;
	while((c =fgetc(file)) != EOF){
		if(isdigit(c)){
			buffer[i++] = c;
		} else if(i > 0){
			long num = atol(buffer);

			char * oct = to_octal(num);

			offset += strlen(oct) -i;
			i = 0;
			memset(buffer, 0 SIZE);
		}
	}
	*file_size = ftell();
}

void process(){
	FILE * file = fopen(FILENAME, "r+b");
	if(file == NULL){
		return;
	}

	int file_size;
	int offset = get_offset(file, &file_size);
	ftruncate(fileno(file), file_size + offset);
	int i = 0;
	char buffer[SIZE];
	memset(buffer, 0,SIZE);
	int write_point = file_size +offset -1;
	int read_point = file_size -1;
	int c = 0;
	while(read_point > = 0){
		fseek(file, read_point, SEEK_SET);
		c = fget(file);
		read_point --;
		if(isdigit(c)){
			buffer[i++] = c;
		}else{
			write_point = write_octal(file, write_point, buffer, &c);
			i = 0;
			memset(bufferm 0, SIZE);
		}
	}
	write_octal(file, write_point, buffer, NULL);
	fclose(file);
	return 0;
}

int main(){
}