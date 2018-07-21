//Escriba una clase template llamada Sumador que reciba por constructor un vector de elementos genericos. 
//La clase Sumador debe incluir un metodo llamado sumar que acumule los valores del tipo recibido
//y retorne un nuevo objeto del tipo generico.
//Que restricciones se le piden al tipo generico en la definicion de Sumador?
#include<stdio.h>
#include<string.h>
#include<vector>
#include<iostream>


using std::endl;
using std::cout;

template <class T>
class sumador {
  std::vector<T> elementos;
  public:
    sumador(std::vector<T> elementos): elementos(elementos){}
    T sumar(){
    	T s = 0;
    	for(int i = 0; i < this->elementos.size(); i++ ){
    		s = s + this->elementos[i];
    	}
    	return s;
    }
    T primero();
};

template <class T>
T sumador<T>::primero(){
  return this->elementos[0];
}

int main(int argc, char * argv[]){
	std::vector<int> v;
	v.push_back(1.6);
	v.push_back(0.2);
	v.push_back(9);
	
	sumador<int> ints(v);
	cout << ints.sumar() << endl;
	cout << ints.primero() << endl;

	std::vector<float> v2;
	v2.push_back(1.6);
	v2.push_back(0.2);
	v2.push_back(9);
	sumador<float> floats(v2);
	cout << floats.sumar() << endl;
	cout << floats.primero() << endl;
	return 0;
}