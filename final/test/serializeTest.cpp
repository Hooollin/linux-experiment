#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

typedef struct c{
    int type;
    string con;
}Command;

int main(){
    Command *cmd = new Command();
    cmd->type = 1;
    cmd->con = "hello";
    ofstream ofs("test");
    ifstream ifs("test");
    ofs.write((char*)cmd, sizeof(Command));
    char buf[1000];
    ifs.read(buf, sizeof(Command));
    Command *ncmd = new Command(*(Command*)buf);
    cout << ncmd->type << " " << ncmd->con << endl;
    return 0;
}
