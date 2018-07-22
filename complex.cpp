//Declare una clase Complejo para encapsular un nro. complejo. 
//Incluya al menos: Constructor default, Constructor con valores de inicialización y Constructor de Copia;
// Operador <, ==, =, int (que devuelva la parte real del nro. encapsulado) y << (impresión). 
//Implemente el operator<<.

#include<stdbool.h>
#include<iostream>
#include<math.h>

using std::endl;
using std::cout;

class Complejo{
	private:
	float r;
	float i;

	public:
	Complejo(float r, float i): r(r), i(i){}

	Complejo(const Complejo & other){
		this->i = other.i;
		this->r = other.r;
	}

	//asignacion por copia
	Complejo operator =(const Complejo &other){
		if(this == &other){
			return *this;
		}
		this->i = other.i;
		this->r = other.r;

		return *this;
	}


	float get_r() const{
		return this->r;
	}

	float get_i() const{
		return this->i;
	}

	bool operator == (const Complejo & other) const{
		if(this->i != other.i || this->r != other.r){
			return false;
		}
		return true;
	}

	operator int(){
		return this->r;
	}

	int module() const {
		return sqrt(pow(this->r,2) + pow(this->i,2));
	}

	bool operator < (const Complejo & other) const{
		return this->module() < other.module();

	}
};

std::ostream & operator << (std::ostream & out, const Complejo c ){
	out << c.get_r() << " + " << c.get_i() << "i";
	return out;
}
int main(int argc, char * argv[]){
	Complejo c1(1,2);
	std::cout << "c1 = " << c1 << endl;

	Complejo c2(0,0);
	std::cout << "c2 = " << c2 << endl;

	if(c2 < c1){
		printf("c2 es menor a c1\n");
	}else{
		printf("c2 no es menor a c1\n");
	}

	c2 = c1;
	std::cout << "c2 = " << c2 << endl;

	if(c2 == c1){
		printf("c2 es igual a c1\n");
	}else{
		printf("c2 no es igual a c1\n");
	}




}