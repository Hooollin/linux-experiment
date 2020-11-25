#include <fstream>
#include <iostream>
#include <string>

using namespace std;


class A{
    public:
        A(){
            i = 0;
        }
        A(int j){
            i = j;
        }

        bool serialize(const char *p){
            ofstream outfile(p);
            outfile.write((char*)this, sizeof(*this));
            return true;
        }

        A deserialize(const char *p){
            ifstream infile(p);
            char buf[1000];
            infile.read(buf, 1000);
            return *(A*)buf;
        }

        void f(){
            cout << "i = " << this->i << endl;
        }

    private:
        int i;
};
