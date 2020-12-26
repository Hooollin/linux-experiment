#ifndef CPLUGINENUMERATOR_H
#define CPLUGINENUMERATOR_H

#include <string>
#include <vector>

using namespace std;

class CPluginEnumerator {
    public:
        CPluginEnumerator();
        virtual ~CPluginEnumerator();

        bool GetPluginNames(vector<string> &vstrPluginNames);
};

#endif
