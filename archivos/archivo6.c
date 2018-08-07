//Escriba un programa ISO C que procese el archivo de números datos.txt sobre sí mismo. 
//El procesamiento consite en convertir los números encontrados (de 1 o más cifras decimales) a octal.
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 64
#define FILENAME "data.txt"

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

int write_octal(FILE * file, int write_point, char * buf, int * c){
	if(strlen(buf) > 0){
		reverse(buf);
		long num = atol(buf);
		char * oct = to_octal(num);
		int oct_len = strlen(oct);
		write_point = write_point - oct_len;
		fwrite((void *) oct, oct_len,1, file);

	}
	
	if(c !=NULL){
		write_point--;
		fseek(file, write_point, SEEK_SET);
		fputc(*c, file);

	}

	return write_point;
}


int get_offset(FILE *file, int *file_size){
	int offset = 0;
	int i = 0;
	char buffer[SIZE];
	memset(buffer, 0,SIZE);
	int c = 0;
	while((c =fgetc(file)) != EOF){
		printf("se lee %c\n",c );
		if(isdigit(c)){
			printf("es un numero \n");
			buffer[i++] = c;
		} else if(i > 0){
			long num = atol(buffer);
			printf("el numero es %li\n", num);

			char * oct = to_octal(num);
			printf("en octal = %s\n",oct );

			offset += strlen(oct) -i;
			i = 0;
			memset(buffer, 0, SIZE);
		}
	}
	*file_size = ftell(file);
	return offset;
}

void process(){
	FILE * file = fopen(FILENAME, "r+b");
	if(file == NULL){
		printf("no se pudo abrir\n");
		return;
	}

	int file_size;
	int offset = get_offset(file, &file_size);
	ftruncate(fileno(file), file_size + offset);
	printf("%i ofsset, file_size %i \n", offset, file_size);
	int i = 0;
	char buffer[SIZE];
	memset(buffer, 0,SIZE);
	int write_point = file_size +offset;
	int read_point = file_size -1;
	int c = 0;
	while(read_point >= 0){
		fseek(file, read_point, SEEK_SET);
		c = fgetc(file);
		printf("se lee %c\n",c );
		read_point --;
		if(isdigit(c)){
			buffer[i++] = c;
		}else{
			buffer[i++] = 0;
			write_point = write_octal(file, write_point, buffer, &c);
			printf("write_point despues de scribir %i\n",write_point );
			i = 0;
			memset(buffer, 0, SIZE);
		}
	}
	write_octal(file, write_point, buffer, NULL);
	fclose(file);
}

int main(){
	char pal[] = "hola como";
	reverse(pal);
	printf("%s\n", pal);
	long num = 8;
	char * base = to_octal(num);
	printf("%s\n", base);
	process();
}