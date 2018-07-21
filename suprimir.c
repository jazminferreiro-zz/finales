//Defina la función SUPRIMIR sin utilizar funciones de bibliotecas. 
//La función debe suprimir del primer parámetro todas las ocurrencias del segundo.

#include <stdio.h>

int get_len(char * C){
	int i = 1;
	while(C[i]!= 0){
		i++;
	}
	return i;
}

int cmp(char * C1, char * C2, int n){
	int i = 0;
	while(i < get_len(C2) && i < get_len(C1) && i < n){
		if(C1[i] != C2[i]){
			return 1;
		}
		i++;
	}
	return 0;
}
char *suprimir(char * C1,char *C2) {
	int len = get_len(C2);
	int read_point = 0;
	int write_point = 0;
	while(read_point < get_len(C1)){
		if(cmp( &C1[read_point], C2, len) == 0){
			read_point += len;
		}else{
			
			C1[write_point++] =  C1[read_point++];
			
		}
		
	}
	C1[write_point] = 0;


}

int main(int argc, char* argv[]){
	char C1[] = "hola como estas como comes?";
	char C2[] = "com";
	suprimir(C1,C2);
	printf(" %s\n",C1 );
}