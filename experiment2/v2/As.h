#include "A.h"
#include <vector>

class SerializerForAs{

    public:

        bool serialize(const char *p, vector<A*> &v){
            ofstream outfile(p);
            int n = v.size();
            for(int i = 0; i < n; i++){
                outfile.write((char*)v[i], sizeof(*v[i]));
            }
            return true;
        }

        bool deserialize(const char *p, vector<A*> &v){
            int n = v.size();
            ifstream infile(p);
            char buf[1000];
            for(int i = 0; i < n; i++){
                infile.read(buf, sizeof(*v[i]));
                A *a = new A(*(A*)buf);
                v[i] = a;
            }
            infile.close();
            return true;
        }

};
