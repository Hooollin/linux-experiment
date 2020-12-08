#include "a.h"
#include <dlfcn.h>
#include <iostream>

using namespace std;


int main(){
    void *handle = dlopen("./libtest.so", RTLD_LAZY);

    if(NULL == handle){
        cout << "dlopen error" << endl;
        return -1;
    }

    typedef void (*func)();

    func f = (func)dlsym(handle, "f");
    if(NULL == f){
        cout << "f1 error" << endl;
        char *str = dlerror();
        cout << str << endl;
        return -1;
    }
    (*f)();
    dlclose(handle);
    return 0;
}
