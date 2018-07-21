//Haciendo uso de listas STL,
// declare una matriz genérica de tipo T. 
//Escriba una nota donde aclare qué operadores asume que existirán en T.

#include <stdio.h>
#include <iostream>
#include<list>
using std::list;

template<class T>

class Matrix{
	std::list<std::list<T>> m;
public:
	Matrix(int n){
	}

	void add_row(std::list<T> r){
		m.push_back(r);

	}
};

int main(int argc, char * argv[]){

	Matrix<int> m(1);
	std::list<int> r;
	r.push_back(1);
	m.add_row(r);
	
}