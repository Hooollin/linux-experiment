#include <iostream>
#include <fstream>
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
        bool Serialize(const char* pFilePath);
        A  Deserialize(const char* pFilePath);
        void print();
    private:
        int i;
};


bool A::Serialize(const char* p){
    ofstream of(p);
    of.write((char*)this, sizeof(this));
    return true;
}

A A::Deserialize(const char* p){
    ifstream inf(p);
    char* a;
    inf >> a;
    return *(A*)a;
}

void A::print(){
    cout << "i : ";
    cout << this->i << endl;
}
