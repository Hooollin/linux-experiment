#ifndef CPLUGINCONTROLLER_H
#define CPLUGINCONTROLLER_H

#include <vector>

class CountPlugin;

class CPluginController
{
public:
	CPluginController(void);
	virtual ~CPluginController(void);
	
	bool InitializeController(void);
	bool UninitializeController(void);

	bool ProcessHelp(void);
	bool ProcessRequest(int FunctionID);

private:
	std::vector<void *> m_vhForPlugin;
    std::vector<CountPlugin*> m_vpPlugin;
};

#endif
