#include "SerializerForAs.h"


int main(){
    vector<A*> v;
    for(int i = 0; i < 10; i++){
        v.push_back(new A(i));
        v[i]->print();
    }

    SerializerForAs sfas;

    sfas.Serialize("data-multi", v);
    
    vector<A*> res = sfas.Deserialize("data-multi");
    
    for(int i = 0; i < res.size(); i++){
        res[i]->print();
    }
    return 0;
}
