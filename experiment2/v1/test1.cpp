#include "A.h"

int main(){
    A a(100);
    a.serialize("data");
    A b = a.deserialize("data");
    b.f();
    return 0;
}
