#include <stdio.h>
int F(const short *a); //declaracion de una funcion
int F(const short * a){
	return 0;

}

int main(int argc, char const *argv[]) {
	char u[3];
	u[0] = 'o';
	u[1] = 'u';
	u[2] = 'i';
	printf("%s\n",u );

  	char (*l)[3]; //puntero a vector de tres char

  	l = &u;

  	printf("%s\n", *l);


	float *C[3]; //vector de tres punteros afloat

	float float_num = 1.5;
	C[0] = &float_num;
	C[1] = &float_num;
	C[2] = &float_num;

  return 0;
}

