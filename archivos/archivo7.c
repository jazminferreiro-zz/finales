//Escribir un programa C que, sin crear archivos intermedios, procese el archivo “enteros.dat”.
//El procesamiento consiste en leer grupos de 2 enteros sin signo de 32 bits desde el archivo 
//y escribir, en su lugar, la resta del grupo (es decir que el archivo se acortará).

#include <stdio.h>
#include <unistd.h>

void reduce(char * filename){
	FILE * file = fopen(filename, "r+b");
	if(file == NULL){
		printf("error al abrir archivo\n");
		return;

	}
	fseek(file, 0, SEEK_END);
	int file_size = ftell(file);
	rewind(file);
	unsigned int entero_a = 0;
	unsigned int entero_b = 0;
	int write_point = 0;
	int read_point = 0;
	while(read_point < file_size){
		fread((void*) &entero_a, 4, 1, file);
		printf("se lee %u = %x \n", entero_a, entero_a);
		if(ftell(file) < file_size){
			fread((void*) &entero_b, 4, 1, file);
			printf("se lee %u = %u \n", entero_b, entero_b);
		}
		read_point = ftell(file);
		printf(" read_point %i \n", read_point );
		entero_a -= entero_b;
		printf("resta %u = %x \n", entero_a, entero_a);
		fseek(file, write_point, SEEK_SET);
		printf(" write_point antes %i \n", write_point );
		fwrite((void *) &entero_a, 4, 1 ,file);
		
		write_point = ftell(file);
		printf(" write_point despues %i \n", write_point );
		fseek(file, read_point, SEEK_SET);
		entero_a = 0;
	    entero_b = 0;
	}
	ftruncate(fileno(file), write_point);
	fclose(file);
}

int main(int argc, char * argv[]){
	char filename[] = "a.dat";
	reduce(filename);
	
}
