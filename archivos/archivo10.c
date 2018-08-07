//Escribir un programa ANSI C que, sin crear archivos intermedios, 
//procese el archivo “valores.bin”. 
//El procesamiento consiste en leer 2 enteros sin signo de 32 bits desde el archivo y escribir, en su lugar,
//el máximo y el mínimo del grupo y el resultado de la operacion or entre los dos (es decir que el archivo se agrandara).

#include <stdio.h>
#include <string.h>
#include<unistd.h>



void proces_file(char * file_name){
	FILE * file = fopen(file_name, "r+b");
	if(file == NULL){
		printf("Error al leer el archivo\n");
		return;
	}
	fseek(file, 0, SEEK_END);
	int file_size = ftell(file);
	rewind(file);
	ftruncate(fileno(file), file_size*3/2);

	int write_pos = 0;
	int read_pos = 0;
	int a = 0;
	int b = 0;
	int  c = 0;
	while(read_pos < file_size){
		fseek(file, read_pos, SEEK_SET);
		fread((void *) &a, 4, 1, file);
		printf("se lee a\n");
		if(ftell(file) < file_size){
			fread((void *) &b, 4, 1, file);
			printf("se lee b\n");
			read_pos = ftell(file);

			fseek(file, write_pos, SEEK_SET);
			if(b > a){
				fwrite((void *) &b, 4, 1, file);
				fwrite((void *) &a, 4, 1, file);
			} else{
				fseek(file, 8, SEEK_CUR);
			}
			c = a | b;
			fwrite((void *) &c, 4, 1, file);
			write_pos = ftell(file);
		} else{
			fseek(file, write_pos, SEEK_SET);
			fwrite((void *) &a, 4, 1, file);
			break;
		}
	}
	fclose(file);
}



int main(int argc, char * argv[]){
	proces_file(argv[1]);
}