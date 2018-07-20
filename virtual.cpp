//Indicar la salida del siguiente programa:

//para mi va a devolver
// Derivada.f1
// Derivada.f2
// Derivada.f1
// Derivada.f1 // NOOOO ESTA DEVUELVE Base.f1 porque es estatica
// Derivada.f2
// Derivada.f1

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
class Base {

public:

    static void f1() { cout << "Base.f1" << endl; }

    virtual void f2() { cout << "Base.f2" << endl; f1(); }

    virtual void f3() { cout << "Base.f3" << endl; f2(); f1(); }

};

class Derivada : public Base {

public:
    static void f1() { cout << "Derivada.f1" << endl; }

            void f2() { cout << "Derivada.f2" << endl; f1(); }

            void f3() { cout << "Derivada.f3" << endl; f2(); f1(); }

};

int  main() {

   Derivada D;

   Base*  pB = &D;

   Derivada*  pD = &D;

    pD->f1();

    pD->f2();

    printf("--------------\n");

    pB->f1();

    pB->f2();

    return 0;

}