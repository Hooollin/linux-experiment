#include <unistd.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(){
    char buf[1024];
    FILE *f = fopen("data", "r");
    cout << read(fileno(f), buf, 1024) << endl;
    cout << buf << endl;
    return 0;
}
