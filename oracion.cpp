//La clase Oracion utiliza un char *a para almacenar un string terminado en \0.
//Escriba la declaracion de esta clase no olvidando: constructor por default,
// constructor por copia, operadores +, -, =, >> y <<.

//Implemente el operador = y el operador -.  
//Este ultimo debe eliminar de la primer cadena todas las ocurrencias de la segunda.

#include "oracion.h"

Oracion::Oracion(char * str){

	this->a = str;
}

char * Oracion::get_a() const{
	return this->a;
}

Oracion Oracion::operator = ( const Oracion &other){
	if(this == &other){
		return (*this);
	}
	this->a = other.get_a();
	return (*this);
}
Oracion Oracion::operator -(const Oracion & other) const{
	char* nueva = (char *)malloc(sizeof(char)*strlen(this->a));
	int write_point = 0;
	int read_point = 0;
	while(read_point < strlen(this->a)){
		printf("%s == %s ?\n",&this->a[read_point], other.get_a()  );
		if(strncmp(&this->a[read_point], other.get_a(), strlen(other.get_a()) ) == 0){
			printf("iguales\n");
			read_point += strlen(other.get_a() ) ;

		}
		else{
			nueva[write_point++] = this->a[read_point++];
		}
	}
	nueva[write_point++] = 0;
	Oracion resta(nueva);
	return resta;
}

std::ostream & operator <<(std::ostream & out, const  Oracion &ora){
	out << ora.get_a() << "\n";
	return out;
}

int main(){
	char c1[] = "hola como estas como comes";
	char c2[] = "com";

	Oracion o(c1);
	Oracion b(c2);

	std::cout << o;
	Oracion c = o-b;
	std::cout << c;




}