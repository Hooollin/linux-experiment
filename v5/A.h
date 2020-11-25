#include <fstream>
#include <iostream>
#include "ILSerializable.h"

using namespace std;


class A : public ILSerializable{

    public:
        bool serialize(const char *p) override {
            ofstream outfile(p);
            outfile.write((char*)this, sizeof(*this));
            outfile.close();
            return true;
        }

        ILSerializable* deserialize(const char *p) override {
            ifstream infile(p);
            char buf[1000];
            unsigned int len = sizeof(*this);
            infile.read(buf, len);
            ILSerializable *ils = new A(*(A*)buf);
            infile.close();
            return ils;
        }


        int getType() override {
            return type;
        }

        A(){
            i = 0;
        }
        A(int j){
            i = j;
        }

        void f(){
            cout << "type = " << type << ", i = " << this->i << endl;
        }

    private:
        int i;
        int type = 0;
};
