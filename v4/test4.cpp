#include "A.h"
#include "B.h"

using namespace std;

int main(){
    ILSerializable *a = new A(5);
    ILSerializable *b = new B(4);
    (*(A*)a).f();
    (*(B*)b).f();
    return 0;
}

