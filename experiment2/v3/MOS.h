#include "A.h"
#include "B.h"
#include <vector>

using namespace std;

class Serialized{
    // 0 -> A, 1 -> B
    public:
        int type;
        void* pObj;
        
        Serialized(){

        }
};

class MultiObjectSerializer{
    public:
        bool serialize(const char* p, vector<Serialized>& v){
            ofstream outfile(p);
            int n = v.size();
            for(int i = 0; i < n; i++){
                int len = sizeof(int);
                outfile.write((char*)&v[i].type, len);
                outfile.write((char*)v[i].pObj, len);
                //cout << v[i].type << " " << *(v[i].pObj) << endl;
            }           
            outfile.close();
            return true;
        }

        bool deserialize(const char* p, vector<Serialized>& v){
            ifstream infile(p);
            int n = v.size();
            char buf[1000];
            for(int i = 0; i < n; i++){
                int len = sizeof(int);
                infile.read(buf, len);
                v[i].type = *(int*)buf;
                infile.read(buf, len);
                v[i].pObj = new A(*(A*)buf);
            }
            return true;
        }

};
