//Escriba una aplicación C que lea de la línea de comandos un número 
//y lo imprima en todas las bases entre 2 y 16.
#include <stdio.h>
#include <string.h>

void reverse_print(char * buf){
	for(int i = strlen(buf)-1; i >= 0; i--){
		printf("%c", buf[i]);
	}
	printf("\n");
}


char get_digit(int d){
	if(d < 10){
		return d +'0';
	} else if( d == 10){
		return 'A';
	}else if( d == 11){
		return 'B';
	}else if( d == 12){
		return 'C';	
	}else if( d == 13){
		return 'D';
	}else if( d == 14){
		return 'E';
	}else if( d == 15){
		return 'F';
	}
}

void print(int num, int base){
	char buf[1000];
	memset(buf, 0,1000);
	int x = num;
	int r;
	int i =0;
	while(x > 0){
		r = x%base;
		buf[i++] = get_digit(r);
		x = x/base;
	}
	reverse_print(buf);
}

int main(int argc, char * argv[]){
	int n;
	printf("\ningrese un numero\n");
	scanf("%i", &n);

	printf("\nen base 2 "); print(n, 2);
	printf("\nen base 3 "); print(n,3);
	printf("\nen base 4 "); print(n,4);
	printf("\nen base 5 "); print(n,5);
	printf("\nen base 6 "); print(n,6);
	printf("\nen base 7 "); print(n,7);
	printf("\nen base 8 "); print(n,8);
	printf("\nen base 9 "); print(n,9);
	printf("\nen base 10 "); print(n,10);
	printf("\nen base 11 "); print(n,11);
	printf("\nen base 12 "); print(n,12);
	printf("\nen base 13 "); print(n,13);
	printf("\nen base 14 "); print(n,14);
	printf("\nen base 15 "); print(n,15);
	printf("\nen base 16 "); print(n,16);

}