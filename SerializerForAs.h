#include "A.h" 
#include <vector>
#include <cstdlib>

class SerializerForAs{
    public:
        bool Serialize(const char* p, vector<A*>& v){
            ofstream of(p);
            int n = v.size();
            for(int i = 0; i < n; i++){
                of << v[i];
            }
            return true;
        }

        vector<A*> Deserialize(const char* p){
            ifstream inf(p);
            vector<A*> ans;
            char buf[8];
            while(inf >> buf){
                ans.push_back((A*)buf);
            }
            return ans;
        }
};
