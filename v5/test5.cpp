#include "A.h"
#include "B.h"
#include <fstream>
#include <string>

using namespace std;

int main(){
    string path;
    // input like: ./a.out < config
    cin >> path;
    
    ILSerializable *a = new A(1);
    ILSerializable *b = new B(8);
    a->serialize(path.c_str());
    b->serialize(path.c_str());
    ILSerializable *na = a->deserialize(path.c_str());
    ILSerializable *nb = b->deserialize(path.c_str());
    (*(A*)a).f();
    (*(B*)b).f();
    return 0;
}

