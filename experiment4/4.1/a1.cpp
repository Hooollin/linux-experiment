#include "a.h"
#include <iostream>

using namespace std;

extern "C" void f(){
    cout << "f()" << endl;
}