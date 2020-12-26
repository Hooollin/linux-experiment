#ifndef CPLUGINCONTROLLER_H
#define CPLUGINCONTROLLER_H

#include <string>
#include <vector>

class EncryptionPlugin;

class CPluginController {
    public:
        CPluginController(void);
        virtual ~CPluginController(void);

        bool InitializeController(void);
        bool UninitializeController(void);

        std::string ProcessHelp(void);
        std::string ProcessRequest(int FunctionID, std::string content);

    private:
        std::vector<void *> m_vhForPlugin;
        std::vector<EncryptionPlugin *> m_vpPlugin;
};

#endif
