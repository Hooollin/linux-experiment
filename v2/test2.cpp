#include "As.h"


int main(){
    int n = 10;
    vector<A*> v;
    vector<A*> dv;
    for(int i = 0; i < n; i++){
        v.push_back(new A(i));
        dv.push_back(new A());
    }
    SerializerForAs sfas;

    sfas.serialize("data", v);

    sfas.deserialize("data", dv);

    for(int i = 0; i < n; i++){
        (*dv[i]).f();
    }
    return 0;
}
