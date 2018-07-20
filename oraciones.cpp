//Declare la clase Oraciones que almacena una acumulacion de lineas de texto (strings)
// en cierto orden e incluye las operaciones de agregacion y eliminacion de lineas.
//La clase debe poseer los operadores usuales de copia, asignacion, salida a flujo (<<) 
//comparacion (==), agregacion (+), substraccion (-).
//Los 2 ultimos operadores deben admitir argumentos del tipo string en formato C (char*) y C++ (std::string).

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class Oraciones{
	std::vector<std::string> v;

public:
	Oraciones(int n){}

	//constructor por copia
	Oraciones(const Oraciones &other){
		this->v = other.v;
	}

	//constructor por asignacion
	Oraciones(Oraciones && other){
		this->v = other.v;
		std::vector<std::string> empty_v;
		other.v = empty_v;
	}


	void agregar(std::string linea){ // esto puede recibir un string o  un "literal" o un char[] (se hace la conversion automatica)
		v.push_back(linea);
	}


	void eliminar(std::string linea){
		std::vector<std::string>::iterator iter = v.begin();
		while(iter != v.end()){
			if(linea.compare(*iter) ==0 ){
				iter = v.erase(iter);
			}else{
				iter++;
			}
			
		}
	}

	void eliminar(const char * linea){
		std::vector<std::string>::iterator iter = v.begin();
		while(iter != v.end()){
			const char * l = (*iter).c_str();
			if(strncmp(l,linea,strlen(l)) ==0 ){
				iter = v.erase(iter);
			}else{
				iter++;
			}
			
		}
	}

	void eliminar(int i){
		v.erase(v.begin() +i);
	}

	std::vector<std::string> get_lineas() const{
		return this->v;
	}



	bool operator == (const Oraciones & other) const{

		std::vector<std::string> other_v = other.get_lineas();

		if(v.size() != other_v.size()){
			return false;
		}
		for(int i = 0; i < this->v.size(); i++){
			if(this->v[i].compare(other_v[i]) != 0){
				return false;
			}

		}
		return true;
	}

	Oraciones& operator = (const Oraciones &other){
		if(this == &other){
			return *this;
		}
		this->v = other.v;
		return (*this);
	}

	Oraciones& operator = (Oraciones &&other){
		 if (this == &other) {
            return *this; // other is myself!
        }
		this->v = other.v;
		std::vector<std::string> empty_v;
		other.v = empty_v;
		return (*this);
	}

	Oraciones operator + (const Oraciones &other) {
		Oraciones nuevas(1);
		for(auto linea : this->v){
			nuevas.agregar(linea);
		}

		for(auto linea : other.get_lineas()){
			nuevas.agregar(linea);
		}

		return nuevas;

	}

	Oraciones operator + (const std::string linea) {
		this->agregar(linea);
		return (*this);
	}

	Oraciones operator - (const std::string linea) {
		this->eliminar(linea);
		return (*this);
	}

	Oraciones operator - (const Oraciones &other) {
		Oraciones nuevas(1);
		for(auto linea : this->v){
			nuevas.agregar(linea);
		}

		for(auto linea : other.get_lineas()){
			nuevas.eliminar(linea);
		}

		return nuevas;

	}
	
};

std::ostream & operator <<(std::ostream & out, const Oraciones & oraciones){
	for(auto linea : oraciones.get_lineas()){
		cout << linea << endl;
	}
	return out;
}

void procesar(Oraciones texto, Oraciones parrafo){

	if(parrafo == texto){
		cout << "son iguales" << endl;
	}else{
		cout << "son distintos" << endl;
	}

}

int main(int argc, char * argv[]){
	Oraciones texto(1);

	char jaja[] = "jaja";

	texto.agregar("hola!");
	texto.agregar("como estas?");
	texto.agregar(jaja);
	texto.agregar("todo bien?");
	texto.agregar(jaja);
	texto.agregar("esta linea no deberia aparecer");
	texto.agregar("esta linea no deberia aparecer");
	texto.agregar("chau");
	cout << texto << "----------------" << endl;


	texto.eliminar(3);
	cout << texto << "----------------"<< endl;
	texto.eliminar("esta linea no deberia aparecer");
	cout << texto << "----------------"<< endl;

	texto.eliminar(jaja);
	cout << texto << "----------------"<< endl;

	Oraciones parrafo(1);

	parrafo.agregar("hola!");
	parrafo.agregar("como estas?");
	parrafo.agregar("chau");


	procesar(texto, parrafo);

	parrafo.agregar(jaja);

	procesar(texto, parrafo);

	cout <<  "----------------"<< endl;
	Oraciones suma = parrafo +texto;
	cout << suma << "----------------"<< endl;
	Oraciones resta = suma - texto;
	cout << resta << "----------------"<< endl;

	resta + "hola";
	resta + jaja;
	resta - jaja;
	cout << resta << "----------------"<< endl;





	
}