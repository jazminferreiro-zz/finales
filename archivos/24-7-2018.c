//Escriba un programa C que reciba por argumento el nombre de un archivo de numeros binarios de 16 bits y lo procese sobre si mismo.
//El procesamiento consiste en repetir los numeros que sean "multiplos de 5 + 1" (6, 11, 16...) (El archivo se agranda)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <errno.h>
#include <unistd.h>

bool is_mult(short n){
	return ((n-1) % 5 == 0);

}

int get_offset(FILE * file, int size){
	short num = 0; //un short ocupa 2 bytes = 16 bits;
	int offset = 0;
	int pos = 0;

	while(pos < size){
		fread((void *) &num, 1, sizeof(short), file);	
		pos += sizeof(short);
		if(is_mult(num)){
			offset += sizeof(short);
		}
	}
	return offset;
}

void write_back(FILE* file, int * write_pos, short num){
	(*write_pos) -= sizeof(short);
	fseek(file, *write_pos, SEEK_SET);
	fwrite((void *) &num, 1, sizeof(short), file);
	

}

short read_back(FILE* file, int * read_pos){
	short num = 0;
	(*read_pos) -= sizeof(short);
	fseek(file, *read_pos, SEEK_SET);
	fread((void *) &num, 1, sizeof(short), file);
	return num;
}



int main(int argc, char * argv[]){
	if(argc < 2){
		printf("Error, falta argumento del archivo\n");
		return 1;
	}

	FILE * file = fopen(argv[1],"r+b");

	if(file == NULL){
		printf("error al abrir archivo\n");
		return 1;
	}

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	rewind(file);

	size_t offset = get_offset(file,size);

	ftruncate(fileno(file), size + offset);

	int read_pos = size;
	int write_pos = size + offset;

	short num = 0;
	while(read_pos > 0){

		num = read_back(file, &read_pos);
		printf("se lee %d\n", num );
		write_back(file, &write_pos ,num);

		if(is_mult(num)){
			printf("es multiplo se vuelve a escribir %d\n", num );
			write_back(file, &write_pos ,num);
		}
		
	}


	return 0;

}

