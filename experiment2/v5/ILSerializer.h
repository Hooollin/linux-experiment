#include "A.h"
#include "B.h"
#include <vector>

using namespace std;

class ILSerializer{
    public:
        bool serialize(const char* p, vector<ILSerializable*>& v){
            ofstream outfile(p);
            int n = v.size();
            for(int i = 0; i < n; i++){
                int len = sizeof(*v[i]);
                outfile.write((char*)v[i], len);
            }           
            outfile.close();
            return true;
        }

        bool deserialize(const char* p, vector<ILSerializable*>& v){
            ifstream infile(p);
            int n = v.size();
            char buf[1000];
            for(int i = 0; i < n; i++){
                int len = sizeof(*v[i]);
                infile.read(buf, len);
                
                if(v[i]->getType() == 0){
                    A *a = new A(*(A*)buf);
                    v[i] = a;
                }else{
                    B *b = new B(*(B*)buf);
                    v[i] = b;
                }
            }
            return true;
        }

};
