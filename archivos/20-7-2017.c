/* Escribir un programa ISO C  que procese  un archivo  de texto sobre si mismo.
El proceso consiste en detectar la secuencia de caracteres 'ABAB'  y remplazarlas por 'C' */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <ctype.h>
#define ABAB "ABAB"
#define C "C"
int main(){
	FILE * file = fopen("file", "r+");
	if(file == NULL){
		printf("Error\n");
		return 1;
	}

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	char buffer[4];
	memset(buffer, 0, 4);
	printf("sizeof buffer %li\n", sizeof(buffer));

	char c;
	int read_pos = 0;
	int write_pos = 0;

	while( read_pos <file_size){
		fseek(file, read_pos, SEEK_SET);
		fread((void *) &buffer, 1, sizeof(buffer), file);
		
		printf(" se lee %s\n",buffer );

		fseek(file, write_pos, SEEK_SET);
		if(strncmp(buffer, ABAB, sizeof(ABAB)) == 0){
			fwrite((void *) &C, 1, sizeof(C),file);
			read_pos += sizeof(buffer);

		}else{
			fwrite((void *)&buffer[0], 1, sizeof(char), file);
			read_pos += 1;
		}
		write_pos = ftell(file);
	}
	ftruncate(fileno(file), write_pos);
	fclose(file);
	return 0;

}