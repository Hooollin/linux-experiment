#include <fstream>
#include <iostream>
#include <string>

using namespace std;


class B{
    public:
        B(){
            i = 0;
        }
        B(int j){
            i = j;
        }

        bool serialize(const char *p){
            ofstream outfile(p);
            outfile.write((char*)this, sizeof(*this));
            return true;
        }

        B deserialize(const char *p){
            ifstream infile(p);
            char buf[1000];
            infile.read(buf, 1000);
            return *(B*)buf;
        }

        void f(){
            cout << "i = " << this->i << endl;
        }

    private:
        int i;
};
