#include <iostream>
#include <fstream>
#include "ILSerializable.h"

using namespace std;


class B : public ILSerializable{

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
            int len = sizeof(int);
            infile.read(buf, len);
            ILSerializable *ils = new B(*(B*)buf);
            return ils;
        }


        int getType() override {
            return type;
        }

        B(){
            i = 0;
        }
        B(int j){
            i = j;
        }

        void f(){
            cout << "type = " << type << ", i = " << this->i << endl;
        }

    private:
        int i;
        int type = 1;
};
