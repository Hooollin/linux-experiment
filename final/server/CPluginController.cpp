#include <dlfcn.h>
#include "CPluginController.h"
#include "CPluginEnumerator.h"
#include "./plugin/EncryptionPlugin.h"
#include <iostream>

using namespace std;

CPluginController::CPluginController(void)
{
}

CPluginController::~CPluginController(void)
{
}

bool CPluginController::InitializeController(void)
{
    std::vector<std::string> vstrPluginNames;

    CPluginEnumerator enumerator;
    if(!enumerator.GetPluginNames(vstrPluginNames))
        return false;

    for(unsigned int i=0 ; i<vstrPluginNames.size(); i++)
    {

        typedef void (*PLUGIN_CREATE)(EncryptionPlugin**);

        EncryptionPlugin* pPlugin = NULL;

        void *hinstLib = dlopen(vstrPluginNames[i].c_str(), RTLD_LAZY);

        if(hinstLib != NULL) 
        { 
            m_vhForPlugin.push_back(hinstLib);
            PLUGIN_CREATE createProc = (PLUGIN_CREATE)dlsym(hinstLib, "createObj");
            if(NULL != createProc){
                createProc(&pPlugin);
                if(NULL != pPlugin){
                    m_vpPlugin.push_back(pPlugin);
                }
            }
        }
    }

    return true;
}

string CPluginController::ProcessRequest(int FunctionID, string content)
{
    for(unsigned int i = 0; i < m_vpPlugin.size(); i++)
    {
        if((m_vpPlugin[i])->getID() == FunctionID)
        {
            return m_vpPlugin[i]->work(content);
        }
    }
    return "";
}


std::string CPluginController::ProcessHelp(void)
{
    std::vector<std::string> vstrPluginNames;

    CPluginEnumerator enumerator;
    if(!enumerator.GetPluginNames(vstrPluginNames))
        return "";
    
    string rev;
    for(unsigned int i=0 ; i<vstrPluginNames.size(); i++)
    {
        typedef void (*PLUGIN_CREATE)(EncryptionPlugin**);
        PLUGIN_CREATE createProc;
        EncryptionPlugin *pPlugin = NULL;

        void *hinstLib = dlopen(vstrPluginNames[i].c_str(), RTLD_LAZY);
        if(hinstLib != NULL) 
        { 
            createProc = (PLUGIN_CREATE)dlsym(hinstLib, "createObj"); 
            if(NULL != createProc) 
            {
                (createProc)(&pPlugin);
                if(pPlugin != NULL){
                    rev += pPlugin->help();
                }
            }
            dlclose(hinstLib);
        }

    }
    return rev;
}

bool CPluginController::UninitializeController()
{
    for(unsigned int i = 0; i < m_vhForPlugin.size(); i++)
    {
        dlclose(m_vhForPlugin[i]);
    }

    return true;
}
