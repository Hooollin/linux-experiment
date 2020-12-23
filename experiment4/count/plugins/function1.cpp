#include <iostream>
#include "CountPlugin.h"
#include <fstream>
#include <string>

using namespace std;

const int FUNC_ID = 2;

class LineCounterPlugin: public CountPlugin{
public:
    LineCounterPlugin(){
    }

    virtual ~LineCounterPlugin(){
    }

    virtual void Count()
    {
        string path;
        cout << "input a relative path:" << endl;
        cin >> path;
        ifstream ifs(path.c_str());

        string line;
        int ans = 0;
        while(getline(ifs, line)){
            ans += 1;
        }
        cout << "The # of lines in " << path << " are " << ans << endl;
    }

    virtual void Help()
    {
        cout << "Function ID " << FUNC_ID << " : This function will count # of lines." << endl;
    }

    virtual int GetID()
    {
        return FUNC_ID;
    }
};

extern "C" void CreateObj(CountPlugin** ppPlugin){
    static LineCounterPlugin plugin;
    *ppPlugin = &plugin;
}

