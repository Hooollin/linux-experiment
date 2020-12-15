#include <dlfcn.h>
#include "CPluginController.h"
#include "CPluginEnumerator.h"
#include "./plugins/IPrintPlugin.h"

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

        typedef void (*PLUGIN_CREATE)(IPrintPlugin**);

        IPrintPlugin *pPlugin = NULL;

		void *hinstLib = dlopen(vstrPluginNames[i].c_str(), RTLD_LAZY);

		if(hinstLib != NULL) 
		{ 
			m_vhForPlugin.push_back(hinstLib);
            PLUGIN_CREATE createProc = (PLUGIN_CREATE)dlsym(hinstLib, "CreateObj");
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

bool CPluginController::ProcessRequest(int FunctionID)
{
	for(unsigned int i = 0; i < m_vpPlugin.size(); i++)
	{
		if((m_vpPlugin[i])->GetID() == FunctionID)
		{
            m_vpPlugin[i]->Print();
			break;
		}
	}

	return true;
}


bool CPluginController::ProcessHelp(void)
{
	std::vector<std::string> vstrPluginNames;

	CPluginEnumerator enumerator;
	if(!enumerator.GetPluginNames(vstrPluginNames))
		return false;
	for(unsigned int i=0 ; i<vstrPluginNames.size(); i++)
	{
        typedef void (*PLUGIN_CREATE)(IPrintPlugin**);
        PLUGIN_CREATE createProc;
        IPrintPlugin *pPlugin = NULL;

		void *hinstLib = dlopen(vstrPluginNames[i].c_str(), RTLD_LAZY);

		if(hinstLib != NULL) 
		{ 
			createProc = (PLUGIN_CREATE)dlsym(hinstLib, "CreateObj"); 
			if(NULL != createProc) 
			{
				(createProc)(&pPlugin);
                if(pPlugin != NULL){
                    pPlugin->Help();
                }
			}
			dlclose(hinstLib);
		}
	}

	return true;
}

bool CPluginController::UninitializeController()
{
	for(unsigned int i = 0; i < m_vhForPlugin.size(); i++)
	{
		dlclose(m_vhForPlugin[i]);
	}

	return true;
}
