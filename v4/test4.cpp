#include "A.h"
#include "B.h"

using namespace std;

int main(){
    ILSerializable *a = new A(1);
    ILSerializable *b = new B(8);
    a->serialize("data");
    b->serialize("data");
    ILSerializable *na = a->deserialize("data");
    ILSerializable *nb = b->deserialize("data");
    (*(A*)a).f();
    (*(B*)b).f();
    return 0;
}

