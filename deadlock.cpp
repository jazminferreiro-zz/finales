#include<thread>
#include<mutex>
#include<iostream>

using std::cout;
using std::endl;

std::mutex m1;
std::mutex m2;

void foo(int *n){

	printf("foo: pido el mutex 1\n");
	m1.lock();
	for(int i = 0; i < 100000; i++){
	}

	printf("foo: pido el mutex 2\n");

	m2.lock();
	
	(*n) = (*n)-1;
	
	m1.unlock();

	m2.unlock();


	
}
	
void boo(int *n){
	printf("boo: pido el mutex 2\n");
	m2.lock();
	
	printf("boo: pido el mutex 1\n");
	m1.lock();
	
	(*n) = (*n)+1;
	

	m2.unlock();

	m1.unlock();

	
}

int main(int argc, char * argv[]){
	int n = 0;
	cout << "se lanza el primer hilo"<< endl;

	std::thread t1(foo,&n);
	cout << "se lanza el segundo hilo"<< endl;
	std::thread t2(boo,&n);

	t1.join();
	t2.join();

	cout << "el numero es " << n << endl;

}