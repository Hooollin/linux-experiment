#include "A.h"
#include "B.h"
#include "ILSerializer.h"

using namespace std;

int main(){
    string path;
    //input like this: ./a.out < config
    cin >> path;

    cout << "serializer for single object" << endl;
    ILSerializable *a = new A(1);
    a->serialize(path.c_str());
    ILSerializable *na = a->deserialize(path.c_str());
    ((A*)na)->f();
    ILSerializable *b = new B(8);
    b->serialize(path.c_str());
    ILSerializable *nb = b->deserialize(path.c_str());
    ((B*)nb)->f();

    cout << "serializer for multiple objects" << endl;
    ILSerializer vs;
    int n = 10;
    vector<ILSerializable*> v(n);
    vector<ILSerializable*> dv(n);
    for(int i = 0; i < n / 2; i++){
        v[i] = new A(i);
        dv[i] = new A(i);
    }
    for(int i = n / 2; i < n; i++){
        v[i] = new B(i);
        dv[i] = new B(i);
    }
    vs.serialize(path.c_str(), v);
    vs.serialize(path.c_str(), dv);
    for(int i = 0; i < n; i++){
        if(v[i]->getType()){
            ((B*)v[i])->f();
        }else{
            ((A*)v[i])->f();
        }
    }
    return 0;
}

