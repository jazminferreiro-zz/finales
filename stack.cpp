//Haciendo uso de un arreglo estático de 1000 posiciones, implemente una pila de enteros. 
//La librería debe contemplar su uso en ambientes multithreading. 
//Por consiguiente se espera que incorpore los recursos necesarios para garantizar la coherencia de la estructura en todo momento.

#include <thread>
#include <mutex>
#define SIZE 1000

class Lock{
private:
	std::mutex &m;
public:
	Lock(std::mutex &m): m(m){
		m.lock();
	}
	~Lock(){
		m.unlock();
	}
	Lock(const Lock&) = delete;
	Lock(Lock&&) = delete;
	Lock & operator = (const Lock&)= delete;
	Lock & operator = (Lock &&) = delete;
};


class Error{
	public:
	Error(std::string s){
		printf("%s\n",s.c_str() );

	}
};

class stack{

private:
	int max;
	int top;
	int data[SIZE];
	std::mutex m;

public:
	stack(int max){
		if(top >= SIZE ){
			throw Error("stack over\n");
		}
		this->max = max;
		this->top = 0;
	}
	int get_top(){
		Lock l(m);
		if(this->top < 0){
			throw Error("empty list\n");
		}
		return this->data[this->top];
	}


	int pop(){
		Lock l(m);
		if(this->top < 0){
			throw Error("empty list\n");
		}
		return this->data[--this->top];
	}

	
	void push(int n){
		Lock l(m);
		if(this->top >= max ){
			throw Error("stack over\n");
			return;
		}
		this->data[this->top++]  = n;
	}
	
};

void foo1(stack * s){
	(*s).push(1);

}
void foo2(stack * s){
	(*s).push(2);

}
void foo3(stack * s){
	(*s).push(3);

}

void print(stack * s, int n){
	for(int i = 0; i < n; i++){
		printf(" %i ", (*s).pop());

	}
	printf("\n");

}
int main(int argc, char * argv[]){
	stack s(10);
	std::thread t1(foo1, &s);
	std::thread t2(foo2, &s);
	std::thread t3(foo3, &s);
	t1.join();
	t2.join();;
	t3.join();

	print(&s, 3);
	return 0;



	

	
}



