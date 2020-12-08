#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <cstring>
#include <vector>

using namespace std;

vector<string> plugins;
char *err = NULL;

typedef void (*func)();


bool isdotso(string& filename){
    int size = filename.size();
    return (size >= 3 && filename[size - 1] == 'o' && filename[size - 2] == 's' && filename[size - 3] == '.');
}

void readsofile(){
    DIR* dir = opendir("plugin");
    dirent *ptr;
    while((ptr = readdir(dir)) != NULL){
        string filename = ptr->d_name;
        if(!isdotso(filename)){
            continue;
        }
        string path = "plugin/" + filename;
        plugins.push_back(path);
    }
    closedir(dir);
}

int read(char *str){
    int now = 0;
    while(*str){
        if(*str < '0' || *str > '9'){
            return -1;
        }
        now = now * 10 + *str - '0';
        str += 1;
    }
    return now;
}

int main(int argc, char **argv){
    readsofile();
    if(argc != 2){
        cout << "invalid arguments" << endl;
        return -1;
    }
    char *command = argv[1];
    if(0 == strcmp(command, "help")){
        for(int i = 0; i < plugins.size(); i++){
            cout << plugins[i] << ": " << i << endl;
        }
        return 0;
    }else{
        int funcidx = read(command);
        if(funcidx < 0 || funcidx > plugins.size()){
            err = strdup("invalid plugin choice");
        }
        if(err){
            cout << err << endl;
            return -1;
        }
        void *handle = dlopen(plugins[funcidx].c_str(), RTLD_LAZY);
        if(NULL == handle){
            err = dlerror();
            cout << err << endl;
        }
        func print = (func)dlsym(handle, "print");
        (*print)();
    }
    return 0;
}
