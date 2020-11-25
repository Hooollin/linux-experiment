#pragma once
#include <fstream>
#include <iostream>
#include "ILSerializable.h"

using namespace std;


class A : public ILSerializable{

    public:
        bool serialize(const char *p) override {
            ofstream outfile(p);
            //整个结构体写入文件中
            outfile.write((char*)this, sizeof(*this));
            outfile.close();
            return true;
        }

        ILSerializable* deserialize(const char *p) override {
            ifstream infile(p);
            char buf[1000];
            //f读出整个结构体
            unsigned int len = sizeof(*this);
            infile.read(buf, len);
            A *a = new A(*(A*)buf);
            infile.close();
            return a;
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
