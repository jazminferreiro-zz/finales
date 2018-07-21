//Escriba una aplicación C que modifique el archivo a.dat 
//eliminando los bytes mayores a 0xC3.

#include <stdio.h>
#include<string.h>
#include <unistd.h>


void reduce(char * filename){
	FILE * file = fopen(filename, "r+b");
	if(file == NULL){
		printf("error al abrir archivo\n");
		return;

	}

	int offset = 0;
	int c;
	while((c = getc(file)) != EOF){
		if(c > 0xC3){
			offset +=1;
		}else if(offset > 0){
		
			fseek(file, -offset -1, SEEK_CUR);
			fputc(c,file);
			fseek(file, +offset, SEEK_CUR);
		}

	}
	int size = ftell(file);
	ftruncate(fileno(file),size -offset);
	fclose(file);
	
}

int main(int argc, char * argv[]){
	char filename[] = "a.dat";
	reduce(filename);
	
}