//Escriba una funcion de C llamada strncat_new que reciba tres parametros: 
//dos punteros a caracter constante (S1 y S2) y un entero sin signo (L).

//La funcion debe concatenar S1 con S2 y retornar una nueva cadena de caracteres 
//considerando L como tamaño maximo para cualquiera de los elementos (S1, S2 y la nueva cadena).

//La funcion debe detectar condiciones de error respecto de la longitud y retornar NULL en cualquier caso.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char * strncat_new(const char * S1, const char * S2, unsigned int max){
	char * nueva = (char *)malloc(sizeof(char)*max);
	int i = 0;
	for(i = 0; i < strlen(S1); i++){
		if(i > max){
			break;
		}
		nueva[i] = S1[i];
	}
	for(int j = 0; j < strlen(S2); j++){
		if(i > max){
			break;
		}
		nueva[i++] = S2[j];
	}
	return nueva;

}

int main(int argc, char * argv[]){
	char S1[] = "hola";
	char S2[] = "chau";
	char * cat = strncat_new(S1,S2,8);
	printf("%s\n",cat );
	cat =  strncat_new(S1,S2,3);
	printf("%s\n",cat );
}