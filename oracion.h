//La clase Oracion utiliza un char *a para almacenar un string terminado en \0.
//Escriba la declaracion de esta clase no olvidando: constructor por default,
// constructor por copia, operadores +, -, =, >> y <<.

//Implemente el operador = y el operador -.  
//Este ultimo debe eliminar de la primer cadena todas las ocurrencias de la segunda.

#ifndef ORACION_H
#define ORACION_H
#include <iostream>
#include <string.h>


class Oracion{
private:
	char * a;
public:
	Oracion( char *str);
	char * get_a() const;
	//Oracion( const Oracion &other);
	Oracion operator = (const Oracion & other);
	Oracion operator +(const Oracion & other) const;
	Oracion operator -(const Oracion & other) const;
	
};
std::ostream& operator <<(std::ostream &out, const Oracion & oracion);
std::istream& operator >>(std::istream & ist, Oracion &  oreacion);
#endif