#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <cstring>

using namespace std;

typedef void (*func)();

bool isdotso(string& filename){
    int size = filename.size();
    return (size >= 3 && filename[size - 1] == 'o' && filename[size - 2] == 's' && filename[size - 3] == '.');
}

int main(){
    char *err;
    DIR* dir = opendir("plugin");
    dirent *ptr;
    while((ptr = readdir(dir)) != NULL){
        string filename = ptr->d_name;
        if(!isdotso(filename)){
            continue;
        }
        string path = "plugin/" + filename;
        void *handle = dlopen(path.c_str(), RTLD_LAZY);
        if(handle == NULL){
            err = dlerror();
            cout << err << endl;
        }
        func f = (func)dlsym(handle, "print");
        (*f)();
    }
    closedir(dir);
    return 0;
}