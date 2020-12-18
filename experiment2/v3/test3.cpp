#include "MOS.h"

using namespace std;

int main(){
    int n = 5;
    vector<Serialized> v;
    vector<Serialized> dv;
    for(int i = 0; i < n / 2; i++){
        A *a = new A(i);
        Serialized s;
        Serialized ds;
        s.type = 0;
        s.pObj = a;
        v.push_back(s);
        dv.push_back(ds);
    }

    for(int i = n / 2; i < n; i++){
        B *b = new B(i);
        Serialized s;
        Serialized ds;
        s.type = 1;
        s.pObj = b;
        v.push_back(s);
        dv.push_back(ds);
    }
    MultiObjectSerializer mos;
    mos.serialize("data", v);
    mos.deserialize("data", dv);
    for(int i = 0; i < n; i++){
        //printf("%d, %d\n", dv[i].type, *(int*)dv[i].pObj);
        printf("%c: %d\n", dv[i].type == 0 ? 'A' : 'B', *(int*)dv[i].pObj);
    }
    return 0;
}
