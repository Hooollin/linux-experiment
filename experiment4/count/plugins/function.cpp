#include <iostream>
#include "CountPlugin.h"
#include <fstream>
#include <string>

using namespace std;

const int FUNC_ID = 1;

class CharacterCounterPlugin : public CountPlugin{

public:
    CharacterCounterPlugin(){}

    virtual ~CharacterCounterPlugin(){}

    virtual void Count(){
        string path;
        cout << "input a relative path:" << endl;
        cin >> path;
        ifstream ifs(path.c_str());
        int ans = 0;
        string line;
        while(getline(ifs, line)){
            for(char ch : line){
                ans += 1;
            }
        }
        cout << "# of characters in " << path << " are " << ans << endl;
    }

    virtual void Help(){
        cout << "Function ID " << FUNC_ID << " : This function will count # of characters." << endl;
    }

    virtual int GetID()
    {
        return FUNC_ID;
    }
};


extern "C" void CreateObj(CountPlugin** ppPlugin){
    static CharacterCounterPlugin plugin;
    *ppPlugin = &plugin;
}
