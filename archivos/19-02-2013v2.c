	//Escribir un programa C que procese el archivo texto.txt sobre sí mismo. 
	//El proceso consiste en triplicar las palabras que tengan todas las vocales.

/*como no aclara nada, voy asuponer que el formato del texto son palabras sin signo de puntuacion, separadas por espacio. 
El archivo empieza y termina en espacio*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

char * triplicar(char * palabra){
	char * nueva = (char *)malloc(sizeof(char)*strlen(palabra)*3 +1);
	int i = 0;
	int j = 0;
	for(int k = 0; k < 3 ;k++){
		while(i < strlen(palabra)){
			nueva[j++] = palabra[i++];
		}
		i = 0;
	}
	nueva[j++] = 0;
	return nueva;
	
}

bool all_vowel(char * palabra){
	bool a = false;
	bool e = false;
	bool i = false;
	bool o = false;
	bool u = false;
	for(int j = 0; j < strlen(palabra); j++){
		if(palabra[j] == 'a' ){
			a = true;
		}else if(palabra[j] == 'e' ){
			e = true;
		}else if(palabra[j] == 'i' ){
			i = true;
		}else if(palabra[j] == 'o' ){
			o = true;
		}else if(palabra[j] == 'u' ){
			u = true;
		}
	}
	return (a && e && i && o && u);

}


int get_offset(FILE * file, int * file_size){
	int c;
	char palabra[100];
	memset(palabra, 0, 100);
	int i = 0;
	int offset = 0;
	while( (c = fgetc(file)) != EOF){
		printf("se lee %c\n",c);
		palabra[i++] = c;
		if(c == ' '){
			printf("se termino la palabra %s\n", palabra);
			if(all_vowel(palabra)){
				offset += 2*i;
			}
			memset(palabra, 0, 100);
			i = 0;
		}
	}
	*file_size = ftell(file);
	return offset;
}

void process(char * file_name){
	FILE * file = fopen(file_name, "r+b");
	if(file == NULL){
		printf("no se puede abrir el archivo %s\n", file_name);
		return;
	}
	int file_size = 0;
	int offset = get_offset(file, &file_size);
	ftruncate(fileno(file),file_size + offset);
	printf("tamaño anterior %i\n",file_size);
	printf("nuevo tamaño %i\n", file_size + offset);

	int read_point = file_size;
	int write_point = file_size + offset;
	
	int c;
	int i = 0;
	char palabra[100];
	char * nueva;
	while(read_point > 0){
		read_point --;
		fseek(file,read_point,SEEK_SET);
		c = fgetc(file);
		
		palabra[i++] = c;
		
		
		printf("se lee -> %c\n",c);
		if(c == ' '){
			nueva = palabra;
			if(all_vowel(palabra)){
				nueva = triplicar(palabra);
			}
			write_point = write_point - strlen(nueva);
			fseek(file, write_point , SEEK_SET);
			for(int j = strlen(nueva); j >=0 ; j--){
				fputc(nueva[j], file);
			}
			memset(palabra, 0, 100);
			i = 0;
		}
	}
	fclose(file);
	}

int main(int argc, char * argv[]){
	char file_name[] = "texto.txt";
	
	char palabra[100] = "hola";
	char palabra2[100] = "equipado";

	if(all_vowel(palabra)){
		printf("tiene todas las vocales %s\n",palabra );
	}else{
		printf("no tiene todas las vocales %s\n",palabra );
	}

	if(all_vowel(palabra2)){
		printf("tiene todas las vocales %s\n",palabra2 );
	}else{
		printf("no tiene todas las vocales %s\n",palabra2 );
	}

	char * triple = triplicar(palabra2);
	printf("%s\n",triple );


	process(file_name);
}	