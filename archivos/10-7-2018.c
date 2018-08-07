/*Escriba una rutina que procese un archivo binario indicado por parametro sobre 
si mismo sumarizando los listados de numeros que posee almacenado. 
La sumarizacion consiste en recorrer los valores enteros de 32 bits con signo
grabados en formato big-endian y acumular sus valores hasta encontrar el valor
0xffffffff que se considera un separador entre listados.

Todos los valores enteros detectados son reemplazados por su sumatoria (en el mismo formati)
manteniendo luego el elemento separador. Considere archivos bien formados. */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <ctype.h>
#define DELIMITER 0xffffffff

char * filename = "sumarize.bin";


int main(){
	FILE * file = fopen(filename, "r+b");
	if(file == NULL){
		printf("error al abri el archivo\n");
	}

	fseek(file,0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	int num = 0;
	int sum = 0;
	int read_pos = 0;
	int write_pos = 0;
	while(read_pos < file_size){
		fseek(file, read_pos,SEEK_SET );
		fread((void *) &num, 1, sizeof(int), file);
		read_pos  = ftell(file);
		if(num == DELIMITER){
			fseek(file, write_pos, SEEK_SET);
			fwrite((void *)&sum,1, sizeof(1), file);
			fwrite((void *)&num, 1, sizeof(1), file);
			write_pos = ftell(file);
		}else{
			sum += ntohl(num);
		}
	}
	ftruncate(fileno(file), write_pos);
	fclose(file);
	return 0;
}

