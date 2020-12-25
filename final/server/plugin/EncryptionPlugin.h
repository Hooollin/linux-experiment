#pragma once
#include <string>

class EncryptionPlugin{
    public:
        EncryptionPlugin();
        virtual ~EncryptionPlugin();

        virtual std::string work(std::string input) = 0;
        virtual int         getID() = 0;
        virtual std::string help()  = 0;
};
