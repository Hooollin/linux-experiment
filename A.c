#include "A.h"


int main(){
    A a(25);
    a.Serialize("data");
    A b = a.Deserialize("data");
    b.print();
    return 0;
}
