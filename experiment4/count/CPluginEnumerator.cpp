#include "CPluginEnumerator.h"
#include <dirent.h>
#include <string.h>
#include <iostream>

CPluginEnumerator::CPluginEnumerator()
{
}

CPluginEnumerator::~CPluginEnumerator()
{
}

bool isSoFile(const char *filename){
    int len = strlen(filename);
    return len >= 3 && filename[len - 3] == '.' && filename[len - 2] == 's' && filename[len - 1] == 'o';
}

bool CPluginEnumerator::GetPluginNames(vector<string>& vstrPluginNames)
{
    DIR *dir = opendir("./plugins");
    if(dir == 0)
	return false;

    for(;;)
    {
	struct dirent *pentry = readdir(dir);
	if(pentry == 0)
	    break;

	if(strcmp(pentry->d_name, ".") == 0)
	    continue;

	if(strcmp(pentry->d_name, "..") == 0)
	    continue;
    if(!isSoFile(pentry->d_name))
        continue;
	string str = "./plugins/";
	str += pentry->d_name;
	vstrPluginNames.push_back(str);
    }

    closedir(dir);

    return true;
}
