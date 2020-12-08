#include <iostream>
#include <dlfcn.h>

using namespace std;

int main(){
    void *handle = dlopen("./print.so", RTLD_LAZY);
    if(NULL == handle){
        char *err = dlerror();
        cout << err;
        return -1;
    }
    typedef void (*func)();
    func print = (func)dlsym(handle, "print");
    if(NULL == print){
        char *err = dlerror();
        cout << err;
        return -1;
    }
    (*print)();
    return 0;
}